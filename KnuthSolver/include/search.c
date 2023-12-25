//
// Created by arxon on 03/09/23.
//

#include "search.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

FrontierNode* frontier_head = NULL;
FrontierNode* frontier_tail = NULL;

clock_t start_time;
clock_t end_time;

int depth = 0;
int total_steps = 0;

int isInteger(double n)
{
    double difference = n - (int) n;
    return (difference <= ACCEPT_INT);
}

TreeNode* search(double input_num, char* algorithm)
{
    start_time = clock();

    clock_t t;
    TreeNode* root = (TreeNode*) malloc(sizeof(TreeNode));
    initializeRoot(root);

    if (isSolution(*root, input_num))
        return root;

    TreeNode* current_node;
    FrontierNode* temp_frontier_node;

    if (strcmp(algorithm, "bfs") == 0)
    {
        while (!isFrontierEmpty())
        {
            t = clock();
            checkForTimeOut(t, start_time);

            current_node = frontier_head->leaf;

            if (isSolution(*current_node, input_num))
                return current_node;

            temp_frontier_node = frontier_head;
            frontier_head = frontier_head->next;
            free(temp_frontier_node);

            if (frontier_head == NULL)
                frontier_tail = NULL;

            expandSearchTree(current_node, algorithm, input_num);
        }
    }
    else if (strcmp(algorithm, "ids") == 0)
    {
        while (1)
        {
            if (isFrontierEmpty())
            {
                TreeNode* root = (TreeNode*) malloc(sizeof(TreeNode));
                initializeRoot(root);
            }

            while (!isFrontierEmpty())
            {
                checkForTimeOut(t, start_time);

                current_node = frontier_head->leaf;

                if (isSolution(*current_node, input_num))
                    return current_node;

                temp_frontier_node = frontier_head;
                frontier_head = frontier_head->next;
                free(temp_frontier_node);

                if (frontier_head == NULL)
                    frontier_tail = NULL;

                if (!isCycle(*current_node))
                    expandSearchTree(current_node, algorithm, input_num);
            }

            ++depth;
        }
    }

    return NULL;
}

int add_frontier_back(TreeNode* node)
{
    FrontierNode* new_frontier_node = (FrontierNode*) malloc(sizeof(FrontierNode));
    if (new_frontier_node == NULL)
        return -1;

    new_frontier_node->leaf = node;
    new_frontier_node->next = NULL;
    new_frontier_node->previous = frontier_tail;

    if (frontier_tail == NULL)
    {
        frontier_head = new_frontier_node;
        frontier_tail = new_frontier_node;
    }
    else
    {
        frontier_tail->next = new_frontier_node;
        frontier_tail = new_frontier_node;
    }

    return 0;
}

int add_frontier_front(TreeNode* node)
{
    FrontierNode* new_frontier_node = (FrontierNode*) malloc(sizeof(FrontierNode));
    if (new_frontier_node == NULL)
        return -1;

    new_frontier_node->leaf = node;
    new_frontier_node->previous = NULL;
    new_frontier_node->next = frontier_head;

    if (frontier_head == NULL)
    {
        frontier_head = new_frontier_node;
        frontier_tail = new_frontier_node;
    }
    else
    {
        frontier_head->previous = new_frontier_node;
        frontier_head = new_frontier_node;
    }

    return 0;
}

void initializeRoot(TreeNode* root)
{
    root->num = N;
    root->parent = NULL;
    root->overflow_raised = 0;
    strcpy(root->operation, ""); // No operation

    add_frontier_front(root);
}

void expandSearchTree(TreeNode* parent_node, char* algorithm, int input_num)
{
    ++total_steps;
    double fact;

    if (strcmp(algorithm, "ids") == 0)
    {
        if (node_depth(*parent_node) > depth)
            return;
    }

    if (isInteger(parent_node->num) && ((int) parent_node->num == N) && (parent_node->parent != NULL))
        return;

    if (input_num != 1 && input_num != 2)
    {
        if ((int) parent_node->num == 1)
            return;

        if ((int) parent_node->num == 2)
            return;
    }

    for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
    {
        parent_node->children[i] = (TreeNode*) malloc(sizeof(TreeNode));
        parent_node->children[i]->parent = parent_node;
    }

    parent_node->children[2]->num = sqrt(parent_node->num);
    parent_node->children[2]->overflow_raised = 0;
    strcpy(parent_node->children[2]->operation, "root");

    if (!isInteger(parent_node->num) || parent_node->overflow_raised)
    {
        parent_node->children[1]->num = floor(parent_node->num);
        parent_node->children[1]->overflow_raised = 0;
        strcpy(parent_node->children[1]->operation, "floor");

        free(parent_node->children[0]);
        parent_node->children[0] = NULL;
    }
    else if (strcmp(parent_node->operation, "floor") == 0 || isInteger(parent_node->num))
    {
        fact = factorial(parent_node->num);
        parent_node->children[0]->overflow_raised = (fact == -1);

        if (!parent_node->children[0]->overflow_raised)
        {
            parent_node->children[0]->num = fact;
            strcpy(parent_node->children[0]->operation, "factorial");
        }
        else
        {
            free(parent_node->children[0]);
            parent_node->children[0] = NULL;
        }

        free(parent_node->children[1]);
        parent_node->children[1] = NULL;
    }
    else
    {
        parent_node->children[1]->num = floor(parent_node->num);
        parent_node->children[1]->overflow_raised = 0;
        strcpy(parent_node->children[1]->operation, "floor");

        fact = factorial(parent_node->num);
        parent_node->children[0]->overflow_raised = (fact == -1);

        if (!parent_node->children[0]->overflow_raised)
        {
            parent_node->children[0]->num = fact;
            strcpy(parent_node->children[0]->operation, "factorial");
        }
        else
        {
            free(parent_node->children[0]);
            parent_node->children[0] = NULL;
        }
    }

    for (int i = 0; i < NUMBER_OF_CHILDREN; i++)
    {
        if (parent_node->children[i] != NULL)
        {
            if (strcmp(algorithm, "bfs") == 0)
            {
                add_frontier_back(parent_node->children[i]);
            }
            else if (strcmp(algorithm, "ids") == 0)
            {
                add_frontier_front(parent_node->children[i]);
            }
        }
    }
}

int isSolution(TreeNode node, double input_num)
{
    return (isInteger(node.num) && (int) node.num == (int) input_num);
}

int isFrontierEmpty()
{
    return (frontier_head == NULL);
}

int isCycle(TreeNode node)
{
    TreeNode* curr_node = node.parent;

    while (curr_node != NULL)
    {
        if (curr_node->num == node.num)
            return 1;

        curr_node = curr_node->parent;
    }

    return 0;
}

double factorial(double num)
{
    double fact = 1;

    for (int i = 2; i <= (int) num; i++)
    {
        fact *= i;
    }

    return fact;
}

int node_depth(TreeNode node)
{
    int d = 0;

    while (node.parent != NULL)
    {
        ++d;
        node = *node.parent;
    }

    return d;
}

void get_solution(TreeNode* solution)
{
    if (solution == NULL)
    {
        printf("No Solution was found");
        return;
    }

    printf("\n\nSolution:\n");
    TreeNode* curr_node = solution;

    int length = 12;
    int list_size = 1;
    char** steps = 0;

    while (curr_node != NULL)
    {
        steps = (char**) realloc(steps, list_size * (sizeof(char*)));
        steps[list_size - 1] = (char*) malloc(length * sizeof(char));

        strcpy(steps[list_size - 1], curr_node->operation);
        ++list_size;

        curr_node = curr_node->parent;
    }

    for (int i = list_size - 2; i >= 0; i--)
        printf("%s\n", steps[i]);

    end_time = clock();

    printf("\nTotal Steps: %d\n", total_steps);
    printf("Time Spent: %fs", ((float) end_time - start_time) / CLOCKS_PER_SEC);
}
