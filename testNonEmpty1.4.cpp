#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"
#include <vector>
// FILE BACK
// Special Test For Resident-Clean

using std::cout;

int main()
{
    std::vector<char *> s(1027, nullptr);
    for(unsigned int i = 0; i < s.size(); ++i) {
        s[i] = (char *) vm_map(nullptr, 0); // init
        strcpy(s[i], "test_1"); // Evict to swap block when physical memory full
    }
    cout << "will reach here";
    if (fork() == 0) {
        // child process
        // make sure parent runs before child
        vm_yield();
        cout << "no over flow at this point\n";
        strcpy(s[0], "child attempting to write\n");
        cout << "overflow now\n, you should not see this";
    } else {
        // parent process
    }
    return 0;
}