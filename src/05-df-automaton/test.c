#include "dfa.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    Transition transitions[] = {
        { 0, 'd', 2 },
        { 0, '.', 3 },
        { 0, '-', 1 },
        { 1, 'd', 2 },
        { 1, '.', 3 },
        { 2, 'd', 2 },
        { 2, '.', 3 },
        { 2, 'E', 5 },
        { 3, 'd', 4 },
        { 4, 'd', 4 },
        { 4, 'E', 5 },
        { 5, 'd', 7 },
        { 5, '+', 6 },
        { 5, '-', 6 },
        { 6, 'd', 7 },
        { 7, 'd', 7 }
    };

    int accepting[] = { 2, 4, 7 };

    DFA dfa = {
        .numTransitions = sizeof(transitions) / sizeof(transitions[0]),
        .transitions = transitions,
        .numAccepting = sizeof(accepting) / sizeof(accepting[0]),
        .acceptingStates = accepting,
        .startState = 0
    };

    assert(dfaCheck(&dfa, "5") == true);
    assert(dfaCheck(&dfa, "123") == true);
    assert(dfaCheck(&dfa, "-123") == true);
    assert(dfaCheck(&dfa, ".5") == true);
    assert(dfaCheck(&dfa, "123.") == false);
    assert(dfaCheck(&dfa, "123E-5") == true);
    assert(dfaCheck(&dfa, "E5") == false);
    assert(dfaCheck(&dfa, "123E") == false);
    assert(dfaCheck(&dfa, "abc") == false);
    assert(dfaCheck(&dfa, "12.34E+56") == true);
    assert(dfaCheck(&dfa, "-.5E-3") == true);

    printf("\nAll tests passed.\n");
    return 0;
}
