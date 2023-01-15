#include "util.h"

// variables and helper functions are declared in util.h

using namespace std;

void vm_init(unsigned int memory_pages, unsigned int swap_blocks)  {
    mem_pages = memory_pages;
    num_swap =  swap_blocks;

    // allocate pinning memory
    for(unsigned int i = 0; i < VM_PAGESIZE; ++i) {
        ((char *)vm_physmem)[i] = 0;
    }
    ++occupied_phy_page;
    // allocate available physical page
    for(unsigned int i = 1; i < mem_pages; ++i) {
        avail_phy_page.push(i);
    }
    // allocate available swap page
    for(unsigned int i = 0; i < num_swap; ++i) {
        avail_swap_blocks.push(i);
    }
};

int vm_create(pid_t parent_pid, pid_t child_pid) {
    int return_val = 0;

    //4 credit version, treat parent arena as empty
    process_state* new_process = new process_state;
    page_table_map[child_pid] = new_process;
    new_process->page_table = new page_table_t;
    for(unsigned int i = 0; i < VM_ARENA_SIZE/VM_PAGESIZE; ++i) {
        set_pte(new_process->page_table, i, 0, 0, 0);
    }

    return return_val;
};

void vm_switch(pid_t pid) {
    page_table_base_register = page_table_map[pid]->page_table;
    cur_process = pid;
}

int vm_fault(const void* addr, bool write_flag) {

    // Get current entry based on the addr
    unsigned int vir_page_num = ((uintptr_t)addr - uintptr_t(VM_ARENA_BASEADDR)) / VM_PAGESIZE;
    
    virtual_entry* cur_entry = page_table_map[cur_process]->vir_list[vir_page_num];

    page_table_entry_t* cur_page_table = &page_table_map[cur_process]->page_table->ptes[vir_page_num];

    // FSM State 1 -- Zero-Filled get changed
    if(cur_entry->zero_filled) {
        assert(write_flag);
        unsigned int cur_phys = 0;
        if(!assign_physical(cur_entry,cur_phys)) {
            return -1;
        }
        
        // Change all the status bits
        cur_entry->dirty = 1;
        cur_entry->ref = 1;
        cur_entry->res = 1;
        cur_entry->zero_filled = 0;

        // push into clock queue
        clock_queue.push(cur_entry);

        // copy zero page
        unsigned int offset = cur_phys*VM_PAGESIZE;

        for(unsigned int i = 0; i < VM_PAGESIZE; ++i) {
            ((char *)vm_physmem)[i + offset] = 0;
        }

        // update physical page number and enable write
        assert(cur_page_table->read_enable);
        assert(cur_entry->owners.size() == 1);
        cur_page_table->write_enable = 1;
        cur_page_table->ppage = cur_phys;

        return 0;
    }

    // Check zero_filled = 0 at this point
    assert(!cur_entry->zero_filled);
    
    // Read_Enable = 0 and Write_Enable = 0
    if(!cur_page_table->read_enable && !cur_page_table->write_enable) {
        if(cur_entry->res) {
            if(cur_entry->dirty) {
                // Resident = 1 and Dirty = 1
                cur_entry->ref = 1;
                assert(cur_entry->res);
                assert(cur_entry->dirty);

                // update read and write bits
                for (page_table_entry_t* ppage_entry: cur_entry->owners) {
                    ppage_entry->write_enable = 1;
                    ppage_entry->read_enable = 1;
                }

                return 0;

            } else {
                // Resident = 1 and Dirty = 0 
                if(write_flag) {
                    // write operation
                    cur_entry->ref = 1;
                    cur_entry->dirty = 1;
                    assert(cur_entry->res);

                    // update read and write bits
                    for (page_table_entry_t* ppage_entry: cur_entry->owners) {
                        ppage_entry->write_enable = 1;
                        ppage_entry->read_enable = 1;
                    }

                    return 0;

                } else {
                    // read operation
                    cur_entry->ref = 1;
                    assert(cur_entry->res);
                    assert(!cur_entry->dirty);


                    // update read and write bits
                    for (page_table_entry_t* ppage_entry: cur_entry->owners) {
                        ppage_entry->read_enable = 1;
                        assert(!ppage_entry->write_enable);
                    }
                    return 0;
                }
            }
        }
        // Evicted: Resident = 0 and Dirty = 0
        else {
            // non-resident
            unsigned int cur_phys = 0;
            if(!assign_physical(cur_entry,cur_phys)) {
                return -1;
            }

            // update ppage for all owners
            for (page_table_entry_t* ppage_entry: cur_entry->owners) {
                ppage_entry->ppage = cur_phys;
            }

            // load from swap block or file
            if (file_read(cur_entry->file_name, cur_entry->block, trans_phys(cur_phys)) == -1) {
                // Release physical page
                add_avail_phy_page(cur_phys);

                return -1;
            }
            // push into clock queue
            clock_queue.push(cur_entry);

            // Read operation
            if (!write_flag) {
                cur_entry->ref = 1;
                cur_entry->res = 1;
                assert(!cur_entry->dirty);

                // update physical page number and enable write
                for (page_table_entry_t* ppage_entry: cur_entry->owners) {
                    ppage_entry->read_enable = 1;
                    assert(!ppage_entry->write_enable);
                }
                return 0;
            }
            else {
                // write operation
                cur_entry->dirty = 1;
                cur_entry->ref = 1;
                cur_entry->res = 1;

                // update physical page number and enable write
                for (page_table_entry_t* ppage_entry: cur_entry->owners) {
                    ppage_entry->read_enable = 1;
                    ppage_entry->write_enable = 1;
                }
                return 0;
            }
        }
    }

    // Resident - clean
    assert(cur_page_table->read_enable && !cur_page_table->write_enable);
    
    // last state is read enabled but write disabled
    // resident and referenced 
    cur_entry->dirty = 1;
    for (page_table_entry_t* ppage_entry: cur_entry->owners) {
        ppage_entry->write_enable = 1;
    }
    
    return 0;
};

void vm_destroy() {
    // swap backed
    for (unsigned int i = 0; i < page_table_map[cur_process]->used_virtual; i ++) {
        virtual_entry* entry = page_table_map[cur_process]->vir_list[i];
        if (!entry->file_name) {
            --swap_count;
            assert(entry->owners.size() == 1);
            // only clean swap block when it has its swap block
            if (entry->block != -1) {
                avail_swap_blocks.push(entry->block);
            }


            // Clean up physical pages
            if (entry->res == 1) {
                add_avail_phy_page(page_table_map[cur_process]->page_table->ptes[i].ppage); 
                // make sure it won't be flashed to swap block
                entry->dirty = 0;

                // if swap back, mark as zero for clock queue
                entry->res = 0;
            } else {
                //  if not resident then no use
                delete entry;
            }
            
        }

        // File backed
        else {
            // No need to clean up file blocks0
            // Defer the clean of physical memory, only delete pte in owner set
            if(entry->owners.size() == 1) {
                entry->option = (*entry->owners.begin())->ppage;
            }
            entry->owners.erase(&page_table_map[cur_process]->page_table->ptes[i]);
            if(entry->owners.empty() && !entry->res){
                string file_name(entry->file_name);
                long block = entry->block;
                assert(block != -1);
                string hash_key = file_name + "/" + to_string(block); 
                assert(file_map.count(hash_key));
                assert(file_map[hash_key]);
                file_map.erase(hash_key);    
                delete entry;
            }
        }
    }

    // delete unused page table
    delete page_table_map[cur_process]->page_table;
    delete page_table_map[cur_process];
    page_table_map.erase(cur_process);
};


void *vm_map(const char *filename, unsigned int block) {
    void * return_val = nullptr;
    // If cannot allocate, return
    if((uintptr_t)page_table_map[cur_process]->next_avail + VM_PAGESIZE > (uintptr_t)VM_ARENA_BASEADDR + (uintptr_t)VM_ARENA_SIZE) return nullptr;

    if(filename == nullptr) {
        // swap back
        // initialize virtual page entry
        if(swap_count == num_swap ) return nullptr;
        else ++swap_count;
        process_state* cur = page_table_map[cur_process];
        return_val = cur->next_avail;
        cur->next_avail =(void*)((unsigned long)cur->next_avail + VM_PAGESIZE);

        // map to zero page
        unsigned int cur_virtual = cur->used_virtual++;
        cur->page_table->ptes[cur_virtual].read_enable = 1;
        cur->page_table->ptes[cur_virtual].ppage = PINNING_PAGE;
        
        // update virtual entry
        virtual_entry* new_entry = new virtual_entry;
            
        // denote the page is zero filled
        new_entry->zero_filled = 1;
            
        // update owner
        new_entry->owners.insert(&cur->page_table->ptes[cur_virtual]);

        cur->vir_list[cur_virtual] = new_entry;  

    } else {
        // FILE BACK
        process_state* cur = page_table_map[cur_process];

        // Read file id
        char *cur_filename_char = (char *)filename;
        char cur_char;
        string file_name;

        do {
            // find ppage
            // get vir page num
            unsigned int vir_page_num = ((uintptr_t)cur_filename_char - uintptr_t(VM_ARENA_BASEADDR)) / VM_PAGESIZE;
            unsigned int offset = ((uintptr_t)cur_filename_char - uintptr_t(VM_ARENA_BASEADDR)) % VM_PAGESIZE;

            // Not in the valid portion of the arena
            if(vir_page_num < 0 || vir_page_num >= cur->used_virtual) return nullptr;

            // use vm_falut to prepare reading when reading bit is 0
            if(!page_table_map[cur_process]->page_table->ptes[vir_page_num].read_enable) {
                void * vir_addr = (void *)((unsigned long)cur_filename_char - offset);
                if(vm_fault(vir_addr, false) != 0) return nullptr;
            }

            unsigned int ppage = page_table_map[cur_process]->page_table->ptes[vir_page_num].ppage;
            char *phys_addr = trans_phys(ppage, offset);

            cur_char = *phys_addr;
            if (cur_char != '\0')   file_name.push_back(cur_char);
            cur_filename_char++;
        } while (cur_char != '\0');

        // Allocate virtual page entry
        return_val = cur->next_avail;
        cur->next_avail =(void*)((unsigned long)cur->next_avail + VM_PAGESIZE);
        

        // Link virtual page entry and Increment used virtual
        unsigned int cur_virtual = cur->used_virtual++;
        virtual_entry* cur_entry = nullptr;
        cur->page_table->ptes[cur_virtual].ppage = cur_virtual; 
        

        // Check if file name already matched to a virtual entry
        string hash_key = file_name + "/" + to_string(block); 
        if(file_map.count(hash_key)) {

            cur_entry = file_map[hash_key];
            assert(cur_entry->file_name != nullptr);
            if(cur_entry->owners.size()) {
                page_table_entry_t* temp = (*cur_entry->owners.begin());
                set_pte(cur->page_table, cur_virtual, temp->ppage, temp->read_enable, temp->write_enable);
            } else {
                assert(cur_entry->option != -1);
                cur->page_table->ptes[cur_virtual].ppage = cur_entry->option;
                cur_entry->option = -1;
                if(cur_entry->ref) {
                    if(cur_entry->dirty == 1) {
                        cur->page_table->ptes[cur_virtual].read_enable = 1;
                        cur->page_table->ptes[cur_virtual].write_enable = 1;
                    } else {
                        cur->page_table->ptes[cur_virtual].read_enable = 1;
                    }
                }
            }
        } else {
            // else, initiate new virtual entry
            cur_entry = new virtual_entry;
 
            cur_entry->file_name = (char *)malloc(file_name.length()+1);
            strcpy(cur_entry->file_name, file_name.c_str());
            cur_entry->block = block;

            // update filemap
            file_map[hash_key] = cur_entry;
        }
        // update owner and virtual page entry
        cur->vir_list[cur_virtual] = cur_entry;
        assert(cur_entry->file_name != nullptr);
        cur_entry->owners.insert(&cur->page_table->ptes[cur_virtual]);
    }
    return return_val;
};
