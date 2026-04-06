#include "dfa.h"
#include <stdio.h>
#include <string.h>

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
    int numTransitions = sizeof(transitions) / sizeof(transitions[0]);

    int accepting[] = { 2, 4, 7 };
    int numAccepting = sizeof(accepting) / sizeof(accepting[0]);

    int startState = 0;

    dfaInit(numTransitions, transitions, numAccepting, accepting, startState);

    char input[128];
    printf("Введите проверяемую строку:\n");
    fgets(input, sizeof(input), stdin);
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = '\0';

    if (dfaCheck(input)) {
        printf("Это число!\n");
    } else {
        printf("Это не число :(\n");
    }

    return 0;
}
