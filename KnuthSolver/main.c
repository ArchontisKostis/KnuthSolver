// main.c
#include "include/search.h"
#include "include/io.h"

int main(int argc, char* argv[])
{
    char algorithm[30];

    double inputNumber = getValidInputNumber();
    getValidAlgorithm(algorithm);

    // Begin searching based on the algorithm chosen
    TreeNode* solution = search(inputNumber, algorithm);

    get_solution(solution);

    return 0;
}

