// test Swap Back state of Unreferenced dirty
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
    strcpy(test_4, "test_4"); // test 1 evicted, others clocked once, reached the state
    cout << test_2 << "\n"; // reference test_2  ref : 1
    strcpy(test_3, "test_3 2"); // write to test_3  ref : 1
    cout << test_3 << "\n"; // Test read on Res - Dirty
    strcpy(test_5, "test_5"); // test 4 evicted, because it is the only unreferenced
    strcpy(test_1, "test_1 3"); // stay at resident-dirty; // write a page at this state, return to resident-dirty
    cout << test_1 << "\n"; // stay at res-dirty
    cout << test_4 << "\n"; // test_4 go to resident_clean
    strcpy(test_4, "test_4 2"); // test_4 go to resident-dir
    cout << test_4 << "\n"; // stay at this state
    return 0;
}