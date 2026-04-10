#include "dfa.h"
#include "ctype.h"

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
