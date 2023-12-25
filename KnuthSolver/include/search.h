//
// Created by arxon on 03/09/23.
//

#ifndef KNUTHSOLVER_SEARCH_H
#define KNUTHSOLVER_SEARCH_H

#include <stdio.h>

#define N 4
#define NUMBER_OF_CHILDREN 3
#define ACCEPT_INT 0.00000001
#define TIMEOUT 90  // Timeout in seconds

typedef struct TreeNode {
    double num;
    struct TreeNode* parent;
    int overflow_raised;
    char operation[20];
    struct TreeNode* children[NUMBER_OF_CHILDREN];
} TreeNode;

typedef struct FrontierNode {
    TreeNode* leaf;
    struct FrontierNode* next;
    struct FrontierNode* previous;
} FrontierNode;

int isInteger(double n);
TreeNode* search(double input_num, char* algorithm);
void expandSearchTree(TreeNode* parent_node, char* algorithm, int input_num);
void initializeRoot(TreeNode* root);
int add_frontier_back(TreeNode* node);
int add_frontier_front(TreeNode* node);
int isSolution(TreeNode node, double input_num);
int isFrontierEmpty();
double factorial(double num);
int node_depth(TreeNode node);
int isCycle(TreeNode node);
void get_solution(TreeNode* solution);

#endif //KNUTHSOLVER_SEARCH_H
