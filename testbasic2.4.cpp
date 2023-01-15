// test arena overflow
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
    strcpy(test_1, "test_1"); // Res - dirty
    cout << test_1; // Res - dirty
    strcpy(test_2, "test_2"); // Res - dirty
    cout << test_2; // Res - dirty
    strcpy(test_3, "test_3"); // Res - dirty
    strcpy(test_4, "test_4"); // test 1 evicted

    cout << test_1; // Resident - clean, add to back of clock, test 2 evicted
    cout << test_1; 
    strcpy(test_1, "test_1 2"); // Res - dirty
    strcpy(test_3, "test_3 2"); // Res - dirty
    cout << test_3; // Res - dirty, clock: 

}
