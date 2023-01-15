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
        // child process
        cout << s1 << "\n";
        cout << s2 << "\n";
        cout << "read is enabled";
        strcpy(s1, "data3.bin"); // a new physical page is created

        // make sure parent run
        vm_yield();
        vm_yield();
        cout << s1 << "\n"; // child p1 not evicted
        cout << s2 << "\n";

    } else {
        // parent process
        // make sure child runs before parent
        vm_yield();
        cout << s1 << "\n"; // should print "data1.bin"

        char *s3 = (char *) vm_map(nullptr, 0);
        strcpy(s3, "evict"); // parent s1 evicted
        cout << s2 << "\n";
        strcpy(s2, "data4.bin");  // allocate new physical page, child s2 stays
        cout << s2 << "\n";

        // give back to child
        vm_yield();
        vm_yield();
    }
    return 0;
}