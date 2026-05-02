#include "dictionary.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int balance;
    char IATA[4];
    char* name;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Dictionary {
    Node* root;
    int number;
} Dictionary;

Dictionary* newDictionary(void)
{
    return calloc(1, sizeof(Dictionary));
}

int getDictionarySize(const Dictionary* tree)
{
    return tree ? tree->number : 0;
}

static int height(Node* node)
{
    if (!node)
        return 0;
    int left = height(node->left);
    int right = height(node->right);
    return (left > right ? left : right) + 1;
}

static void updateBalance(Node* node)
{
    if (!node)
        return;
    node->balance = height(node->right) - height(node->left);
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
    if (!node)
        return NULL;

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

static Node* createNode(const char* code, const char* name)
{
    Node* node = calloc(1, sizeof(Node));
    if (!node)
        return NULL;
    memcpy(node->IATA, code, 3);
    node->IATA[3] = '\0';
    node->name = strdup(name);
    if (!node->name) {
        free(node);
        return NULL;
    }
    node->balance = 0;
    return node;
}

static Node* insertIn(Node* node, const char* code, const char* name, bool* inserted)
{
    if (!node) {
        *inserted = true;
        return createNode(code, name);
    }

    int cmp = strncmp(node->IATA, code, 3);
    if (cmp == 0) {
        *inserted = false;
        return node;
    } else if (cmp > 0) {
        node->left = insertIn(node->left, code, name, inserted);
    } else {
        node->right = insertIn(node->right, code, name, inserted);
    }

    return balance(node);
}

int addAirport(const char* code, const char* name, Dictionary* tree)
{
    if (!tree)
        return 1;

    bool inserted = false;
    tree->root = insertIn(tree->root, code, name, &inserted);

    if (inserted) {
        tree->number++;
        return 0;
    }
    return 1;
}

static const char* findInNode(const char* code, const Node* node)
{
    if (!node)
        return NULL;
    int cmp = strncmp(node->IATA, code, 3);
    if (cmp == 0) {
        return node->name;
    } else if (cmp > 0) {
        return findInNode(code, node->left);
    }
    return findInNode(code, node->right);
}

const char* find(const char* code, Dictionary* tree)
{
    return findInNode(code, tree->root);
}

static Node* findMin(Node* node)
{
    while (node->left)
        node = node->left;
    return node;
}

static Node* deleteIn(Node* node, const char* code, bool* deleted)
{
    if (!node)
        return NULL;
    int cmp = strncmp(node->IATA, code, 3);
    if (cmp > 0) {
        node->left = deleteIn(node->left, code, deleted);
    } else if (cmp < 0) {
        node->right = deleteIn(node->right, code, deleted);
    } else {
        *deleted = true;
        if (!node->left || !node->right) {
            Node* child = node->left ? node->left : node->right;
            free(node->name);
            free(node);
            return child;
        } else {
            Node* successor = findMin(node->right);
            free(node->name);
            memcpy(node->IATA, successor->IATA, 4);
            node->name = strdup(successor->name);
            node->right = deleteIn(node->right, successor->IATA, deleted);
        }
    }

    return balance(node);
}

void removeAirport(const char* code, Dictionary* tree)
{
    if (!tree)
        return;
    bool deleted = false;
    tree->root = deleteIn(tree->root, code, &deleted);
    if (deleted)
        tree->number--;
}

static void saveNode(FILE* file, const Node* node)
{
    if (!node)
        return;
    saveNode(file, node->left);
    fprintf(file, "%s:%s\n", node->IATA, node->name);
    saveNode(file, node->right);
}

int save(FILE* file, Dictionary* tree)
{
    if (!file || !tree)
        return 1;
    saveNode(file, tree->root);
    return 0;
}

static void freeNodes(Node* node)
{
    if (!node)
        return;

    freeNodes(node->left);
    freeNodes(node->right);

    free(node->name);
    free(node);
}

void deleteDictionary(Dictionary* tree)
{
    if (!tree)
        return;
    freeNodes(tree->root);
    free(tree);
}
