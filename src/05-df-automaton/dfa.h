#pragma once

#include <stdbool.h>

typedef struct Transition {
    int from;
    char symbol;
    int to;
} Transition;

// Initializes the DFA with the given transitions, accepting states, and start state
void dfaInit(int n, Transition* trans, int m, int* accepting, int start);

// Checks if the given string is accepted by the DFA
bool dfaCheck(const char* string);
