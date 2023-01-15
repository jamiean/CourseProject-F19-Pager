#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main()
{
    char *s1 = (char *) vm_map(nullptr, 0);
    char *s2 = (char *) vm_map(nullptr, 0);
    strcpy(s1, "data1.bin");
    strcpy(s2, "data2.bin"); // parent occupied two physcial
    char *f1 = (char *) vm_map(s1, 1);
    char *f2 = (char *) vm_map(s2, 1);

    if (fork() == 0) {
        // child process
        cout << s1 << "\n";
        cout << s2 << "\n";
        cout << "read is enabled";

        // test file name is readable without loading
        for (int i = 0; i < 10; ++i) {
            cout << f1[i];
        }
        // attempt to change require a reqular load
        strcpy(f1, "wtf");

        // make sure parent run
        vm_yield();
        vm_yield();
        cout << s1 << "\n"; 
        cout << s2 << "\n";
        for (int i = 0; i < 10; ++i) {
            cout << f2[i];
        }

        // separate virtual entry from parent, but point to same place
        char *s3 = (char *) vm_map(nullptr, 0);
        strcpy(s3, "data3.bin");
        char *f3 = (char *) vm_map(s3, 1);
        for (int i = 0; i < 10; ++i) {
            cout << f3[i];
        }
        strcpy(f3, "wtf");

    } else {
        // parent process
        // make sure child runs before parent
        vm_yield();

        // test file read changed
        for (int i = 0; i < 10; ++i) {
            cout << f1[i];
        }

        // attempt to change require a reqular load
        strcpy(f2, "wtf");

        char *s3 = (char *) vm_map(nullptr, 0);
        strcpy(s3, "data3.bin");
        char *f3 = (char *) vm_map(s3, 1);

        // give back to child
        vm_yield();
        vm_yield();
        char *s4 = (char *) vm_map(nullptr, 0);
        strcpy(s4, "data3.bin");
        char *f4 = (char *) vm_map(s4, 1);

        for (int i = 0; i < 10; ++i) {
            cout << f3[i];
        }
        strcpy(f3, "wtf");
        for (int i = 0; i < 10; ++i) {
            cout << f4[i];
        }
    }
    return 0;
}