//
// Created by arxon on 03/09/23.
//

#include "io.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

double getValidInputNumber() {
    double inputNum;
    bool valid = false;

    do {
        printf("Enter the number you want to reach: ");

        if (scanf("%lf", &inputNum) == 1) {

            if (inputNum > 0 && (int)inputNum == inputNum) {
                valid = true;
            } else {
                printf("Only Integers and positive numbers allowed. \n\n");
            }

        } else {
            printf("Invalid input. Enter a valid number.\n");

            // Clear buffer
            while (getchar() != '\n');
        }

    } while (!valid);

    return inputNum;
}

void getValidAlgorithm(char* algorithm) {
    do {
        printf("\nPlease insert the algorithm you want to try [bfs/ids]: ");
        scanf("%s", algorithm);

    } while (strcmp(algorithm, "bfs") != 0 && strcmp(algorithm, "ids") != 0);
}

