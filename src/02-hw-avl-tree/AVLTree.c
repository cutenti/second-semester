#include "AVLTree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int balance;
    char name[150];
    Node* left;
    Node* right;
};

AVLTree* newTree(void)
{
    return calloc(1, sizeof(AVLTree));
}

static int height(Node* node)
{
    return node ? node->balance : 0;
}

static void updateBalance(Node* node)
{
    if (node) {
        int leftH = height(node->left);
        int rightH = height(node->right);
        node->balance = rightH - leftH;
    }
}

static Node* rotateLeft(Node* a)
{
    Node* b = a->right;
    a->right = b->left;
    b->left = a;
    updateBalance(a);
    updateBalance(b);
    return b;
}

static Node* rotateRight(Node* a)
{
    Node* b = a->left;
    a->left = b->right;
    b->right = a;
    updateBalance(a);
    updateBalance(b);
    return b;
}

static Node* balance(Node* node)
{
    updateBalance(node);
    if (node->balance == 2) {
        if (node->right->balance < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if (node->balance == -2) {
        if (node->left->balance > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

static Node* insertIn(Node* node, Node* newNode, bool* inserted)
{
    if (!node) {
        *inserted = true;
        return newNode;
    }
    int cmp = strncmp(node->name, newNode->name, 3);
    if (cmp == 0) {
        free(newNode);
        *inserted = false;
        return node;
    } else if (cmp > 0) {
        node->left = insertIn(node->left, newNode, inserted);
    } else {
        node->right = insertIn(node->right, newNode, inserted);
    }
    return balance(node);
}

int insertNode(char* name, AVLTree* tree)
{
    Node* airport = calloc(1, sizeof(Node));
    if (!airport)
        return 1;
    strncpy(airport->name, name, sizeof(airport->name) - 1);
    airport->name[sizeof(airport->name) - 1] = '\0';

    bool inserted = false;
    tree->root = insertIn(tree->root, airport, &inserted);
    if (inserted)
        tree->number++;
    return 0;
}

static const char* findInNode(const char* code, const Node* node)
{
    if (!node)
        return NULL;
    int cmp = strncmp(node->name, code, 3);
    if (cmp == 0) {
        // убедимся, что строка содержит ':'
        char* colon = strchr(node->name, ':');
        return colon ? colon + 1 : node->name + 3;
    } else if (cmp > 0) {
        return findInNode(code, node->left);
    } else {
        return findInNode(code, node->right);
    }
}

const char* find(const char* code, AVLTree* tree)
{
    return findInNode(code, tree->root);
}

static Node* findMin(Node* node)
{
    while (node->left)
        node = node->left;
    return node;
}

static Node* deleteIn(Node* node, char* name, bool* deleted)
{
    if (!node)
        return NULL;
    int cmp = strncmp(node->name, name, 3);
    if (cmp > 0) {
        node->left = deleteIn(node->left, name, deleted);
    } else if (cmp < 0) {
        node->right = deleteIn(node->right, name, deleted);
    } else {
        *deleted = true;
        if (!node->left || !node->right) {
            Node* child = node->left ? node->left : node->right;
            free(node);
            return child;
        } else {
            Node* successor = findMin(node->right);
            strncpy(node->name, successor->name, sizeof(node->name) - 1);
            node->name[sizeof(node->name) - 1] = '\0';
            node->right = deleteIn(node->right, successor->name, deleted);
        }
    }
    return balance(node);
}

void deleteNode(char* name, AVLTree* tree)
{
    bool deleted = false;
    tree->root = deleteIn(tree->root, name, &deleted);
    if (deleted)
        tree->number--;
}

static void saveNode(FILE* file, Node* node)
{
    if (!node)
        return;
    saveNode(file, node->left);
    fprintf(file, "%s\n", node->name);
    saveNode(file, node->right);
}

int save(FILE* file, AVLTree* tree)
{
    if (!file || !tree)
        return 1;
    saveNode(file, tree->root);
    return 0;
}
