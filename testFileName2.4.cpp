#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main()
{
    char *p0 = (char *)vm_map(nullptr, 0);

    int offset = 4094;
    char* filename = p0 + offset;
    while(offset < 4096){
        p0[offset++] = 'w';
    }
    
    /* Map a page from the specified file */
    char *p = (char *) vm_map (filename, 0);
    if(p == nullptr) {
        cout << "file name sucessfully loaded\n";
    } else {
        cout << "not sucessfully loaded\n";
    }
}
