// test swap block overflow
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>
#include "vm_app.h"

using std::cout;

int main()
{
    std::vector<char *> s(1024, nullptr);
    for(unsigned int i = 0; i < s.size(); ++i) {
        s[i] = (char *) vm_map(nullptr, 0); // init
        strcpy(s[i], "test_1"); // Evict to swap block when physical memory full
    }
    cout << "Will reach here\n";
    char *addi = (char *) vm_map(nullptr, 0); // init
    strcpy(addi, "buff");
    cout <<  "Overflow now, you shouldn't see this line \n";
}
