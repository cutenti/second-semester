#include "dynamicTable.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void testTableInit(void)
{
    Table* t = tableInit();

    assert(t != NULL);
    assert(t->lineCount == 0);
    assert(t->capacity == 0);
    tableFree(t);
}

void testAddSingleLine(void)
{
    Table* t = tableInit();
    const char* testStr = "header1,header2";

    int res = addLine(t, testStr);
    assert(res == 0);
    assert(t->lineCount == 1);
    assert(strcmp(t->lines[0], testStr) == 0);

    tableFree(t);
}

void testTableReallocation(void)
{
    Table* t = tableInit();

    for (int i = 0; i < 20; i++) {
        assert(addLine(t, "data") == 0);
    }
    assert(t->lineCount == 20);
    assert(t->capacity >= 20);

    tableFree(t);
}

void testAddEmptyLine(void)
{
    Table* t = tableInit();

    assert(addLine(t, "") == 0);
    assert(t->lineCount == 1);
    assert(strlen(t->lines[0]) == 0);

    tableFree(t);
}

int main(void)
{
    testTableInit();
    printf("Test Init: PASSED\n");

    testAddSingleLine();
    printf("Test Add Line: PASSED\n");

    testTableReallocation();
    printf("Test Reallocation: PASSED\n");

    testAddEmptyLine();
    printf("Test Empty Line: PASSED\n");

    printf("\nAll unit tests passed!\n");
    return 0;
}
