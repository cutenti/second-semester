#pragma once

#include <stdio.h>

typedef struct Node Node;

typedef struct AVLTree {
    Node* root;
    int number;
} AVLTree;

// Returns empty AVL tree
AVLTree* newTree(void);

// Inserts airport into tree. Returns 0 on success, 1 on failure
int insertNode(char* name, AVLTree* tree);

// Deletes airport from tree. Does nothing if airport is not in tree
void deleteNode(char* name, AVLTree* tree);

// Finds airport in tree. Returns pointer to name if found, NULL otherwise
const char* find(const char* code, AVLTree* tree);

// Saves tree to file. Returns 0 on success, 1 on failure
int save(FILE* file, AVLTree* tree);
