#include "dynamicTable.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void testTableInit(void)
{
    Table* t = tableInit();

    assert(t != NULL);
    assert(tableGetLineCount(t) == 0);

    tableFree(t);
}

void testAddSingleLine(void)
{
    Table* t = tableInit();
    const char* testStr = "header1,header2";

    int res = addLine(t, testStr);
    assert(res == 0);
    assert(tableGetLineCount(t) == 1);
    assert(strcmp(tableGetLine(t, 0), testStr) == 0);

    tableFree(t);
}

void testTableReallocation(void)
{
    Table* t = tableInit();

    for (int i = 0; i < 20; i++) {
        assert(addLine(t, "data") == 0);
    }
    assert(tableGetLineCount(t) == 20);

    tableFree(t);
}

void testAddEmptyLine(void)
{
    Table* t = tableInit();

    assert(addLine(t, "") == 0);
    assert(tableGetLineCount(t) == 1);
    assert(strlen(tableGetLine(t, 0)) == 0);

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
