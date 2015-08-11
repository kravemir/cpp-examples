#include <stdio.h>
#include "common.h"

int shared_variable;

void printSharedVariable() {
    printf("%d\n", shared_variable++);
}
