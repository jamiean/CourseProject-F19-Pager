#include "vm_pager.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <unordered_set>
#include <queue>
#include <string>
#include <typeinfo>
#include <string.h>
#include <cstdlib>
using namespace std;

// Global variables
// vitural entry global struct
struct virtual_entry {
    // Swap file Or File storage location
    long block = -1;
    char* file_name = nullptr;

    // declare a bit for dirty & ref & resident bit
    unsigned int dirty = 0;
    unsigned int ref = 0;
    unsigned int res = 0;
    unsigned int zero_filled = 0;

    // Point back to owner virtual page
    unordered_set<page_table_entry_t*> owners; 

    // optional field
    long option = -1;
};

// process information, state, arena
struct process_state {
    process_state() {
        vir_list.resize(VM_ARENA_SIZE/VM_PAGESIZE, nullptr);
    };
    page_table_t* page_table;
    void * next_avail = VM_ARENA_BASEADDR;
    unsigned int used_virtual = 0;
    vector<virtual_entry*> vir_list;
};

unsigned int mem_pages = 0; // memory_pages
unsigned int num_swap = 0;  // swap_blocks
unsigned int cur_process = 0; // current process
unsigned int occupied_phy_page = 0; // occupied physical page
queue<unsigned int> avail_phy_page; // available physical page 
queue<unsigned int> avail_swap_blocks; // available swap blocks
unsigned int swap_count = 0; // existing swap back virtual pages

// mapping from pid_t to process struct
unordered_map<pid_t, process_state*> page_table_map;

// The first block in physical memory is reserved for pinning
static const unsigned int PINNING_PAGE = 0;

// Evict clock for eviction
queue<virtual_entry*> clock_queue;

// Exisiting file/block and virtual table match
unordered_map<string, virtual_entry*> file_map;

// Global translate function
char * trans_phys(unsigned int ppage, unsigned int offset = 0) {
    // return the begining of the page
    return (char *)vm_physmem + ppage * VM_PAGESIZE + offset;
}

// update ppage, read_bit, write_bit
void set_pte(page_table_t* pt, unsigned int idx, unsigned int ppage, unsigned int read_bit, unsigned int write_bit) {
    pt->ptes[idx].ppage = ppage;
    pt->ptes[idx].read_enable = read_bit;
    pt->ptes[idx].write_enable = write_bit;
}

// updated phy_page based on ppage number
void add_avail_phy_page(unsigned int ppage) {
    --occupied_phy_page;
    avail_phy_page.push(ppage);
}

// update phy_page based on virtual table entry
void add_avail_phy_page(virtual_entry* target) {
    auto& owners = target->owners;
    
    assert(!owners.empty());
    // find ppage
    unsigned int ppage; 
    bool found = false;
    // check if all of the owners have same ppage and 
    for (auto pte_t : owners) {
        if (found)  assert(ppage == pte_t->ppage);
        ppage = pte_t->ppage;
        found = true;
        assert(!pte_t->read_enable);
        assert(!pte_t->write_enable);
    }  
    // update physical memory
    add_avail_phy_page(ppage);
}

// write back and update owner info
void write_back(virtual_entry* target) {
    // given a target virtual entry, find the corrisponding physical page and write to the file
    auto& owners = target->owners;

    // find ppage
    unsigned int ppage; 
    bool found = false;
    if (target->option != -1) {
        assert(target->owners.empty());
        ppage = target->option;
    } else {
        assert(!target->owners.empty());
        // check if all of the owners have same ppage and 
        for (auto pte_t : owners) {
            if (found)  assert(ppage == pte_t->ppage);
            ppage = pte_t->ppage;
            found = true;
            assert(!pte_t->read_enable);
            assert(!pte_t->write_enable);
        }
    }
    
    void * buf = (void*) trans_phys(ppage);
        
    file_write(target->file_name, target->block, buf);

    // update physical memory
    add_avail_phy_page(ppage);
}

// helper to update owner info
void change_owners_bits(virtual_entry* cur, unsigned int read, unsigned int write) {
    for (auto it : cur->owners) {
        it->read_enable = read;
        it->write_enable = write;
    }
}

// return true if success, return false if no avaliable disk page
bool evict() {
    // invariant: current occupied_phy_page.size() == mem_pages
    // when to push into clock queue: whenever a virtual page is made resident
    assert(occupied_phy_page == mem_pages);

    // find the target page to evict
    virtual_entry* target = nullptr;
    while(!clock_queue.empty()) {
        virtual_entry* cur = clock_queue.front();
        clock_queue.pop();
        
        // if an exited swap back page 
        if(!cur->res) {
            assert(!cur->owners.empty());
            delete cur;
            continue;
        }

        if (!cur->ref) {
            // if reference bit is 0
            target = cur;
            break;
        } else {
            // set ref to 0 and enqueue
            cur->ref = 0;
            change_owners_bits(cur, 0, 0);
            clock_queue.push(cur);
        }
    }
    assert(target != nullptr);
    auto& owners = target->owners;

    // if the front is unreferenced-dirty
    assert(target->res && !target->zero_filled && !target->ref);
    
    // 1. change virtual page state
    if (target->file_name == nullptr) {
        // swap page
        if (target->block == -1) { 
            // if (!avail_swap_blocks.size())  return false;
            unsigned int target_block = avail_swap_blocks.front();
            avail_swap_blocks.pop();

            // update virtual entry
            target->block = target_block;
        }

        if (target->dirty)  write_back(target);
        else add_avail_phy_page(target);
    } else {
        // file page
        if (!owners.empty()) {
            // No need to assign new blocks on file, only write back
            if (target->dirty) {
                write_back(target);
                assert(target->file_name != nullptr);
            } else {
                add_avail_phy_page(target);
            }
        } else {
            // if doesn't have owner
            // remove file mapping
            string file_name(target->file_name);
            long block = target->block;
            assert(block != -1);
            string hash_key = file_name + "/" + to_string(block); 
            assert(file_map.count(hash_key));
            assert(file_map[hash_key]);
            file_map.erase(hash_key);            

            if (target->dirty) {
                assert(target->option != -1);
                write_back(target);
            } else {
                assert(target->option != -1);
                add_avail_phy_page(target->option);
            }
            // remove entry
            delete target;
            return true;
        }

    }

    // update state
    target->res = 0;
    target->dirty = 0;
    return true;
}

// Helper function that will decide whether to evict and return assigned ppage
int assign_physical(virtual_entry* cur_entry, unsigned int& assigned_page) {
    if(occupied_phy_page == mem_pages) {
        // if no free physical page, evict
        if (!evict()) return 0;
    }
    // if there are pages available, just assign
    assert(avail_phy_page.size());
    assigned_page = avail_phy_page.front();
    ++occupied_phy_page;
    avail_phy_page.pop();
    return 1;
}