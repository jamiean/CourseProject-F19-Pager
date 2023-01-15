#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"
// FILE BACK
// Special Test For Resident-Clean

using std::cout;

int main()
{
    if (!fork()) {
        char *filename_1 = (char *) vm_map(nullptr, 0);
        strcpy(filename_1, "data4.bin");

        // Map to and print
        char *f1 = (char *) vm_map(filename_1, 0);
        char *f2 = (char *) vm_map(filename_1, 0);
        for (int i = 0; i < 10; ++i) {
            cout << f2[i];
        }
        cout << "\n";

        for (int i = 0; i < 10; ++i) {
            cout << f1[i];
        }
        strcpy(f2, "a");
        cout << "\n";

        // Assign filename to data1.bin
        char *filename_2 = (char *) vm_map(nullptr, 0);
        char *filename_3 = (char *) vm_map(nullptr, 0);
        char *filename_4 = (char *) vm_map(nullptr, 0);
        strcpy(filename_2, "2");
        strcpy(filename_3, "3");
        strcpy(filename_4, "4");

        char *f3 = (char *) vm_map(filename_1, 0);
        for (int i = 0; i < 10; ++i) {
            cout << f3[i];
        }
        cout << "\n";

        strcpy(f2, "a");
        strcpy(filename_2, "2");
        strcpy(filename_3, "3");
        strcpy(filename_4, "4");

        return 0;
    } else {
        char *filename_1 = (char *) vm_map(nullptr, 0);
        strcpy(filename_1, "data4.bin");

        // Map to and print
        char *f1 = (char *) vm_map(filename_1, 0);
        char *f2 = (char *) vm_map(filename_1, 0);
        for (int i = 0; i < 10; ++i) {
            cout << f2[i];
        }
        cout << "\n";

        for (int i = 0; i < 10; ++i) {
            cout << f1[i];
        }
        strcpy(f2, "a");
        cout << "\n";

        // Assign filename to data1.bin
        char *filename_2 = (char *) vm_map(nullptr, 0);
        char *filename_3 = (char *) vm_map(nullptr, 0);
        char *filename_4 = (char *) vm_map(nullptr, 0);
        strcpy(filename_2, "2");
        strcpy(filename_3, "3");
        strcpy(filename_4, "4");

        char *f3 = (char *) vm_map(filename_1, 0);
        for (int i = 0; i < 10; ++i) {
            cout << f3[i];
        }
        cout << "\n";

        strcpy(f2, "a");
        strcpy(filename_2, "2");
        strcpy(filename_3, "3");
        strcpy(filename_4, "4");

        return 0;
    }
    return 0;
}