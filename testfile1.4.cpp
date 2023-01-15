#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"
// This test will find out if reading if available

using std::cout;

int main()
{
    /* Allocate swap-backed page from the arena */
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
}