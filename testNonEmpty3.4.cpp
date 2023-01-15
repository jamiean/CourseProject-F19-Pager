#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"
// FILE BACK
// Special Test For Resident-Clean

using std::cout;

int main()
{
    char *s1 = (char *) vm_map(nullptr, 0);
    char *s2 = (char *) vm_map(nullptr, 0);
    strcpy(s1, "data1.bin");
    strcpy(s2, "data2.bin"); // parent occupied two physcial
    if (fork() == 0) {
        vm_yield();
        // child own the physical memory
        cout << s1 << "\n";
        cout << s2 << "\n";
        strcpy(s1, "data3.bin");
        strcpy(s2, "data4.bin");
        cout << s1 << "\n";
        cout << s2 << "\n"; // should not reallocate physical pages
    } else {
        // parent process
        // parent runs first
        cout << s1 << "\n";
        cout << s2 << "\n";
        // parent exits, the ownership of virtual entry transferred to child
    }
    return 0;
}