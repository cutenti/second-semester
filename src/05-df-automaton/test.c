#include "dfa.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    DFA* dfa = dfaCreate();
    if (!dfa) {
        perror("Failed to create DFA");
        return 1;
    }

    assert(dfaCheck(dfa, "5") == true);
    assert(dfaCheck(dfa, "123") == true);
    assert(dfaCheck(dfa, "-123") == true);
    assert(dfaCheck(dfa, ".5") == true);
    assert(dfaCheck(dfa, "123.") == false);
    assert(dfaCheck(dfa, "123E-5") == true);
    assert(dfaCheck(dfa, "E5") == false);
    assert(dfaCheck(dfa, "123E") == false);
    assert(dfaCheck(dfa, "abc") == false);
    assert(dfaCheck(dfa, "12.34E+56") == true);
    assert(dfaCheck(dfa, "-.5E-3") == true);

    printf("\nAll tests passed.\n");

    dfaDestroy(dfa);
    return 0;
}
