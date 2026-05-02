#include "dfa.h"
#include "ctype.h"
#include <stdlib.h>

typedef struct Transition {
    int from;
    char symbol;
    int to;
} Transition;

typedef struct DFA {
    int numTransitions;
    const Transition* transitions;
    int numAccepting;
    const int* acceptingStates;
    int startState;
} DFA;

DFA* dfaCreate(void)
{
    DFA* dfa = malloc(sizeof(DFA));
    if (!dfa) {
        return NULL;
    }

    static Transition transitions[] = {
        { 0, 'd', 2 }, { 0, '.', 3 }, { 0, '-', 1 },
        { 1, 'd', 2 }, { 1, '.', 3 },
        { 2, 'd', 2 }, { 2, '.', 3 }, { 2, 'E', 5 },
        { 3, 'd', 4 },
        { 4, 'd', 4 }, { 4, 'E', 5 },
        { 5, 'd', 7 }, { 5, '+', 6 }, { 5, '-', 6 },
        { 6, 'd', 7 },
        { 7, 'd', 7 }
    };

    static int accepting[] = { 2, 4, 7 };

    dfa->numTransitions = sizeof(transitions) / sizeof(transitions[0]);
    dfa->transitions = transitions;
    dfa->numAccepting = sizeof(accepting) / sizeof(accepting[0]);
    dfa->acceptingStates = accepting;
    dfa->startState = 0;

    return dfa;
}

bool dfaCheck(const DFA* dfa, const char* string)
{
    int state = dfa->startState;

    for (const char* p = string; *p; p++) {
        char symbol = *p;

        symbol = isdigit(symbol) ? 'd' : symbol;

        int nextState = -1;
        for (int i = 0; i < dfa->numTransitions; i++) {
            if (dfa->transitions[i].from == state && dfa->transitions[i].symbol == symbol) {
                nextState = dfa->transitions[i].to;
                break;
            }
        }

        if (nextState == -1) {
            return false;
        }
        state = nextState;
    }

    for (int i = 0; i < dfa->numAccepting; i++) {
        if (dfa->acceptingStates[i] == state)
            return true;
    }
    return false;
}

void dfaDestroy(DFA* dfa)
{
    free(dfa);
}
