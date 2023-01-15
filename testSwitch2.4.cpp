#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"
// FILE BACK
// Special Test For Resident-Clean

using std::cout;

int main()
{
    if (! fork()) {
        char *filename_1 = (char *) vm_map(nullptr, 0);
        strcpy(filename_1, "shakespeare.txt");

        // Map to and print
        char *f1 = (char *) vm_map(filename_1, 0);
        for (int i = 0; i < 10; ++i) {
            cout << f1[i];
        }
        cout << "\n";

        // Assign filename to data1.bin
        char *filename_2 = (char *) vm_map(nullptr, 0);
        strcpy(filename_2, "data1.bin");

        char *f2 = (char *) vm_map(filename_2, 0);
        for (int i = 0; i < 10; ++i) {
            cout << f2[i];
        }
        cout << "\n";


        char *f3 = (char *) vm_map(filename_1, 1);
        char *f4 = (char *) vm_map(filename_1, 0);

        for (int i = 0; i < 15; ++i) {
            cout << f3[i];
        }
        cout << "\n";

        for (int i = 0; i < 10; ++i) {
            cout << f4[i];
        }
        cout << "\n";


        return 0;
    } else {
        /* Allocate swap-backed page from the arena */
        char *filename_1 = (char *) vm_map(nullptr, 0);
        strcpy(filename_1, "data4.bin");


        char *f1 = (char *) vm_map(filename_1, 0); // Evicted
        strcpy(f1, "wahahahahahahaha-testFUnrefDirty"); // [Resident-Dirty]


        // Add Page to clock out our test page
        char *filename_2 = (char *) vm_map(nullptr, 0);
        char *filename_3 = (char *) vm_map(nullptr, 0);
        strcpy(filename_2, "2");
        strcpy(filename_3, "3"); // Clock our test page [Unref-Dirty]


        // Read -> [Resident-Dirty]
        for (int i = 0; i < 10; ++i) {
            cout << f1[i];
        }
        cout << "\n";

        strcpy(filename_1, "data4.bin"); // Clock our test page [Unref-Dirty]

        strcpy(f1, "wahahahahahahaha"); // Write -> [Resident-Dirty]

        strcpy(filename_1, "1");
        strcpy(filename_2, "2");
        strcpy(filename_3, "3");  // Evict


        return 0;
    }
    return 0;
}