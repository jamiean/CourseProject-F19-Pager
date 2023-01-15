#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"
// FILE BACK
// Special Test For Resident-Clean

using std::cout;

int main()
{
    if (fork() == 0) {
        // child process
        // make sure parent runs before child
        vm_yield();
        cout << "child run\n";
        char *test_1 = (char *) vm_map(nullptr, 0); // init
        strcpy(test_1, "data4.bin"); // allocate physical page, parent test_1 evicted
        char *f1 = (char *) vm_map(test_1, 0); // link filename, reuse parent entry
        for (int i = 0; i < 10; ++i) {
            cout << f1[i];
        } // read file from memory, will not require loading
        cout << "\n";

        char *test_2 = (char *) vm_map(nullptr, 0); // init
        strcpy(test_2, "data3.bin"); // allocate physical page, reuse entry
        
        //switch back to parents
        vm_yield();
        vm_yield();
        cout << "child run\n";
        char *f2 = (char *) vm_map(test_2, 0); // link filename, no entry to reuse, create one
        for (int i = 0; i < 10; ++i) {
            cout << f2[i];
        } // read file from memory, will require loading
        cout << "\n";

        char *test_4 = (char *) vm_map(nullptr, 0); // init
        strcpy(test_4, "data1.bin"); 
        char *f4 = (char *) vm_map(test_4, 0); // still in clock queue, reues entry
        for (int i = 0; i < 10; ++i) {
            cout << f4[i];
        } // read file, physical occupied: 4
        cout << "\n";

    } else {
        // parent process
        // physical occupied: 0
        cout << "parent run\n";
        char *test_1 = (char *) vm_map(nullptr, 0); // init
        char *test_2 = (char *) vm_map(nullptr, 0); // init

        strcpy(test_1, "data4.bin"); // allocate physical page, physical occupied: 2
        strcpy(test_2, "data3.bin"); // allocate physical page, physical occupied: 3
        char *f2 = (char *) vm_map(test_2, 0); // link filename, create entry
        char *f1 = (char *) vm_map(test_1, 0); // link filename, create entry
        for (int i = 0; i < 10; ++i) {
            cout << f1[i];
        } // read file, physical occupied: 4
        cout << "\n";

        // make sure child runs
        vm_yield();
        vm_yield();
        cout << "parent run\n";
        for (int i = 0; i < 10; ++i) {
            cout << f2[i];
        } // read file, load from memory
        cout << "\n";

        char *test_4 = (char *) vm_map(nullptr, 0); // init
        strcpy(test_4, "data1.bin"); 
        char *test_5 = (char *) vm_map(nullptr, 0); // init
        strcpy(test_5, "noise buffer"); 
        char *f4 = (char *) vm_map(test_4, 0); // link filename, create entry
        for (int i = 0; i < 10; ++i) {
            cout << f4[i];
        } // read file, physical occupied: 4
        cout << "\n";

        // f2 entry destroyed
    }
    return 0;
}