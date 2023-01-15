#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main()
{
    char *p0 = (char *)vm_map(nullptr, 0);
    char *p1 = (char *)vm_map(nullptr, 0);
    char *p2 = (char *)vm_map(nullptr, 0);
    char *p3 = (char *)vm_map(nullptr, 0);
    char *p4 = (char *)vm_map(nullptr, 0);

    char* filename = p0 + 4094;
    strcpy(filename, "shakespeare.txt");
    cout << "the corrent filename is " << filename << "\n";
    cout << "the part written to p1 is " << p1 << "\n";
    strcpy(p2, "wrong.txt");
    strcpy(p3, "wrong1.txt");
    strcpy(p4, "wrong2.txt");
    strcpy(p0, "start");

    /* Map a page from the specified file */
    char *p = (char *) vm_map (filename, 0);
    /* Print the first speech from the file */
    for (unsigned int i=0; i<100; i++) {
	    cout << p[i];
    }
    cout << "\n first output complete \n";

    char *p5 = (char*)vm_map(nullptr, 0);
    char* filename2 = p5 + 2;
    strcpy(filename2, "data1.bin");
    char *f2 = (char *) vm_map (filename2, 1);
    for (unsigned int i=0; i<100; i++) {
	    cout << f2[i];
    }
    cout << "\n second output complete \n";
    return 0;
}
