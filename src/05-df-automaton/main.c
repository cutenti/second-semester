#include "dfa.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    DFA* dfa = dfaCreate();
    if (!dfa) {
        perror("Failed to create DFA");
        return 1;
    }

    char input[128];
    printf("Введите проверяемую строку:\n");

    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';

        if (dfaCheck(dfa, input)) {
            printf("Это число!\n");
        } else {
            printf("Это не число :(\n");
        }
    }

    dfaDestroy(dfa);
    return 0;
}
