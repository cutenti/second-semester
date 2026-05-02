#pragma once

#include <stdio.h>

typedef struct Dictionary Dictionary;

// Returns empty AVL tree
Dictionary* newDictionary(void);

// Returns number of airports in tree
int getDictionarySize(const Dictionary* tree);

// Inserts airport into tree. Returns 0 on success, 1 on failure
int addAirport(const char* code, const char* name, Dictionary* tree);

// Deletes airport from tree. Does nothing if airport is not in tree
void removeAirport(const char* code, Dictionary* tree);

// Finds airport in tree. Returns pointer to name if found, NULL otherwise
const char* find(const char* code, Dictionary* tree);

// Saves tree to file. Returns 0 on success, 1 on failure
int save(FILE* file, Dictionary* tree);

// Frees all memory used by tree
void deleteDictionary(Dictionary* tree);
