//
// Created by arxon on 03/09/23.
//
#include <time.h>
#include <stdlib.h>
#include "search.h"

void checkForTimeOut(clock_t time, clock_t start_time) {
    if (time - start_time > CLOCKS_PER_SEC * TIMEOUT)
    {
        printf("\nCalculation takes too long!\n The program will stop now...");
        exit(1);
    }
}


