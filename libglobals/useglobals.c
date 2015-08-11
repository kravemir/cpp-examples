#include "common.h"

int main() {
    // set global
    shared_variable = 15;
    // shall print 15, and increment global
    printSharedVariable();


    // multiply global, shall be 16*2 = 32
    shared_variable *= 2;
    // shall print 32
    printSharedVariable();

    return 0;
}
