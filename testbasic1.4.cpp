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
    strcpy(test_1, "test_1"); // Res - dirty
    strcpy(test_1, "test_1_1"); // Res - dirty
    strcpy(test_1, "test_1_2"); // Res - dirty
    cout << test_1; // Res - dirty
    strcpy(test_2, "test_2"); // Res - dirty
    cout << test_2; // Res - dirty
    strcpy(test_3, "test_3"); // Res - dirty
    char *test_4 = (char *) vm_map(nullptr, 0); 
    char *test_5 = (char *) vm_map(nullptr, 0);
    strcpy(test_4, "test_4"); // test_1 : Res-dirty -> Evicted; test_2/3: Res-dirty -> Unref-dirty; test_4: init -> res-dirty
    strcpy(test_5, "test_5"); // test_2 : Unref-dirty -> Evicted; test_5: init -> res-dirty
}
