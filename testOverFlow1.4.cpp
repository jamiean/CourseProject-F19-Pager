// test swap block overflow
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>
#include "vm_app.h"

using std::cout;

int main()
{
    if (!fork()) {
        std::vector<char *> s(1024, nullptr);
        for (unsigned int i = 0; i < s.size(); ++i) {
            s[i] = (char *) vm_map(nullptr, 0); // init
            strcpy(s[i], "test_1"); // Evict to swap block when physical memory full
        }
        cout << "Will reach here\n";

        char *addi = (char *) vm_map(nullptr, 0); // init
        strcpy(addi, "buff");
    } else {
        std::vector<char *> s(1024, nullptr);
        for (unsigned int i = 0; i < s.size(); ++i) {
            s[i] = (char *) vm_map(nullptr, 0); // init
            strcpy(s[i], "shakespeare.txt"); // Evict to swap block when physical memory full
        }
        strcpy(s[1022], "data2.bin");
        strcpy(s[1023], "data1.bin");
        cout << "Will reach here\n";

        char *addi = (char *) vm_map(s[0], 0);
        char *addi2 = (char *) vm_map(s[1023], 0);
        char *addi3 = (char *) vm_map(s[1023], 1);
        char *addi4 = (char *) vm_map(s[1022], 1);
        char *addi5 = (char *) vm_map(s[1022], 0);

        for (int i = 0; i < 20; ++i) {
            cout << addi[i];
        }

        for (int i = 0; i < 20; ++i) {
            cout << addi2[i];
        }
        for (int i = 0; i < 20; ++i) {
            cout << addi3[i];
        }
        for (int i = 0; i < 20; ++i) {
            cout << addi5[i];
        }
        for (int i = 0; i < 20; ++i) {
            cout << addi4[i];
        }

        strcpy(addi, "Naive!");
        strcpy(addi3, "I'm angry!");

        for (int i = 0; i < 5; ++i) {
            cout << addi[i];
        }

        for (int i = 0; i < 5; ++i) {
            cout << addi3[i];
        }

        char *addi6 = (char *) vm_map(nullptr, 0); // init
        strcpy(addi, "Hong Kong Journalist");
    }
}
