#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"
// FILE BACK
// Special Test For Resident-Clean

using std::cout;

int main()
{
    /* Allocate swap-backed page from the arena */
    char *filename_1 = (char *) vm_map(nullptr, 0);
    strcpy(filename_1, "data4.bin");
    

    char *f1 = (char *) vm_map(filename_1, 0); // Evicted
     // Read -> [Resident-Clean]
    for (int i = 0; i < 10; ++i) {
        cout << f1[i];
    }
    cout << "\n";


    // Add Page to clock out our test page
    char *filename_2 = (char *) vm_map(nullptr, 0);
    char *filename_3 = (char *) vm_map(nullptr, 0);
    strcpy(filename_2, "2");
    strcpy(filename_3, "3"); // Clock our test page [Unref-Clean-No writeback]


    // Read -> [Resident-Clean]
    for (int i = 0; i < 10; ++i) {
        cout << f1[i];
    }
    cout << "\n";

    strcpy(f1, "wahahahahahahaha-testFResCLean"); // Write -> [Resident-Dirty]

    return 0;
}