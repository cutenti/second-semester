#include "dictionary.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void testCreateAndSize(void)
{
    Dictionary* dict = newDictionary();
    assert(dict != NULL);
    assert(getDictionarySize(dict) == 0);
    deleteDictionary(dict);
    printf("Test Create and Size: PASSED\n");
}

void testInsertAndFind(void)
{
    Dictionary* dict = newDictionary();

    assert(addAirport("SVO", "Sheremetyevo", dict) == 0);
    assert(addAirport("DME", "Domodedovo", dict) == 0);
    assert(getDictionarySize(dict) == 2);

    const char* name = find("SVO", dict);
    assert(name != NULL);
    assert(strcmp(name, "Sheremetyevo") == 0);

    assert(find("JFK", dict) == NULL);

    deleteDictionary(dict);
    printf("Test Insert and Find: PASSED\n");
}

void testDuplicateInsert(void)
{
    Dictionary* dict = newDictionary();
    addAirport("SVO", "Sheremetyevo", dict);

    assert(addAirport("SVO", "New Name", dict) == 1);
    assert(getDictionarySize(dict) == 1);

    deleteDictionary(dict);
    printf("Test Duplicate Insert: PASSED\n");
}

void testDelete(void)
{
    Dictionary* dict = newDictionary();
    addAirport("SVO", "Sheremetyevo", dict);
    addAirport("DME", "Domodedovo", dict);

    removeAirport("SVO", dict);
    assert(getDictionarySize(dict) == 1);
    assert(find("SVO", dict) == NULL);
    assert(find("DME", dict) != NULL);

    deleteDictionary(dict);
    printf("Test Delete: PASSED\n");
}

int main(void)
{
    testCreateAndSize();
    printf("Test Create and Size: PASSED\n");

    testInsertAndFind();
    printf("Test Insert and Find: PASSED\n");

    testDuplicateInsert();
    printf("Test Duplicate Insert: PASSED\n");

    testDelete();
    printf("Test Delete: PASSED\n");

    printf("All tests passed successfully!\n");
    return 0;
}
