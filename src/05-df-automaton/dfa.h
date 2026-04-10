#pragma once

#include <stdbool.h>

// structure representing a transition in the DFA
typedef struct Transition {
    int from;
    char symbol;
    int to;
} Transition;

typedef struct DFA {
    int numTransitions; // number of transitions
    const Transition* transitions; // array of transitions
    int numAccepting; // number of accepting states
    const int* acceptingStates; // array of accepting states
    int startState; // start state
} DFA;

// Checks if the given string is accepted by the DFA
bool dfaCheck(const DFA* dfa, const char* string);
