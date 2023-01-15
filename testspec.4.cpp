#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main()
{
    /* Allocate swap-backed page from the arena */
    char *filename = (char *) vm_map(nullptr, 0);
    cout << "swap sucessfully initialized\n";

    /* Write the name of the file that will be mapped */
    strcpy(filename, "shakespeare.txt");
    cout << "file name successfully writtedn\n";

    /* Map a page from the specified file */
    char *p = (char *) vm_map (filename, 0);
    cout << "file name sucessfully loaded\n";

    /* Print the first speech from the file */
    for (unsigned int i=0; i<100; i++) {
	    cout << p[i];
    }
    cout << "All speech printed\n";
    return 0;
}
