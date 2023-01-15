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
    char *test_5 = (char *) vm_map(nullptr, 0); // init
    char *test_6 = (char *) vm_map(nullptr, 0); // init
    strcpy(test_4, "test_4"); // test_1 : Res-dirty -> Evicted; test_2/3: Res-dirty -> Unref-dirty; test_4: init -> res-dirty Q: 2, 3, 4
    cout << test_1; // test_1: Evicted -> Resident-clean; test_2: res-dirty -> evicted; test_3: Unref-dirty; test_4: res-dirty Q: 3, 4, 1
    cout << test_3; // test_1: Resident-clean; test_2: evicted; test_3: Res-dirty; test_4: res-dirty Q: 3, 4, 1
    strcpy(test_5, "test_5"); // test_1: unref-clean; test_2: evicted; test_3: evicted; test_4: unref-dirty; test_5: res-dirty Q: 4, 1, 5
    cout << test_1; // test_1: resident-clean; test_2: evicted; test_3: evicted; test_4: unref-dirty; test_5: res-dirty Q: 4, 1, 5
    cout << test_1;
    strcpy(test_1, "test_1_new");
    cout << test_4;  // test_1: resident-clean; test_2: evicted; test_3: evicted; test_4: res-dirty; test_5: res-dirty Q: 4, 1, 5
    strcpy(test_6, "test_6"); // test_1: unref-clean; test_2: evicted; test_3: evicted; test_4: evicted; test_5: unref-dirty; test_6: Res-dirty Q: 1, 5, 6
    strcpy(test_1, "test_1_new"); // test_1: res-dirty; test_2: evicted; test_3: evicted; test_4: evicted; test_5: unref-dirty; test_6: Res-dirty Q: 1, 5, 6
    cout << test_2;
    cout << test_3;
    cout << test_4;
    cout << test_5;
    cout << test_1;
    return 0;
}
