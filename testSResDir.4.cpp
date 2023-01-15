// test Swap Back state of Resident-Dirty
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main()
{
    /* Allocate swap-backed page from the arena */
    char *test_1 = (char *) vm_map(nullptr, 0); // init
    char *test_2 = (char *) vm_map(nullptr, 0); // init
    char *test_3 = (char *) vm_map(nullptr, 0); // init
    char *test_4 = (char *) vm_map(nullptr, 0); // init
    char *test_5 = (char *) vm_map(nullptr, 0); // init
    strcpy(test_1, "test_1"); // Res - dirty
    strcpy(test_2, "test_2"); // Res - dirty
    strcpy(test_3, "test_3"); // Res - dirty, clock queue full
    cout << test_1 << "\n"; // Test read on Res - Dirty
    strcpy(test_1, "test_1 1"); // Test write on Res - Dirty
    cout << test_1 << "\n"; // Test read on Res - Dirty
    strcpy(test_4, "test_4"); // test 1 evicted, others clocked once

    cout << test_2 << "\n"; // Test read on Res - Dirty
    strcpy(test_5, "test_4"); // test 2 evicted

    return 0;
}