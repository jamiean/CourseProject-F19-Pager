#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"
// This test will find out if reading if available

using std::cout;

int main()
{
    /* Allocate swap-backed page from the arena */
    char *filename = (char *) vm_map(nullptr, 0);

    cout << "\n Success\n";

    // write once: state change
    strcpy(filename, "Hello world");

    // test read function
    for (int i = 0; i < 15; ++i) {
        cout << (int)filename[i];
    }

    cout << "\n Success\n";

    return 0;
}
