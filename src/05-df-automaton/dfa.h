#pragma once

#include <stdbool.h>

typedef struct DFA DFA;

// Creates a DFA that recognizes valid number formats
DFA* dfaCreate(void);

// Checks if the given string is accepted by the DFA
bool dfaCheck(const DFA* dfa, const char* string);

// Destroys a DFA and frees memory
void dfaDestroy(DFA* dfa);
