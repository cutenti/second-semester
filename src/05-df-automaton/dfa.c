#include "dfa.h"
#include "ctype.h"

static int numTransitions; // число возможных переходов
static Transition* transitions; // массив переходов
static int numAcceptingStates; // число допускающих состояний
static int* acceptingStates; // массив допускающих состояний
static int startState; // стартовое состояние

void dfaInit(int n, Transition* trans, int m, int* accepting, int start)
{
    numTransitions = n;
    transitions = trans;
    numAcceptingStates = m;
    acceptingStates = accepting;
    startState = start;
}

bool dfaCheck(const char* string)
{
    int state = startState;

    for (const char* p = string; *p; p++) {
        char symbol = *p;

        symbol = isdigit(symbol) ? 'd' : symbol;

        int nextState = -1;
        for (int i = 0; i < numTransitions; i++) {
            if (transitions[i].from == state && transitions[i].symbol == symbol) {
                nextState = transitions[i].to;
                break;
            }
        }

        if (nextState == -1) {
            return false;
        }
        state = nextState;
    }

    bool isAccepting = false;
    for (int i = 0; i < numAcceptingStates; i++) {
        if (acceptingStates[i] == state) {
            isAccepting = true;
            break;
        }
    }
    return isAccepting;
}
