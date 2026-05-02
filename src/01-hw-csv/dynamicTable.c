#include "dynamicTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Table {
    char** lines;
    size_t lineCount;
    size_t capacity;
} Table;

Table* tableInit(void)
{
    return calloc(1, sizeof(Table));
}

int addLine(Table* table, const char* line)
{
    if (!table || !line)
        return 1;

    size_t lineLength = strlen(line);
    size_t neededSize = table->lineCount + 1;

    if (neededSize > table->capacity) {
        size_t newCapacity = table->lineCount * 2 < neededSize ? neededSize : table->lineCount * 2;

        char** newLines = realloc(table->lines, newCapacity * sizeof(char*));
        if (!newLines) {
            printf("Error of memory allocation\n");
            return 1;
        }
        table->lines = newLines;
        table->capacity = newCapacity;
    }

    table->lines[table->lineCount] = malloc(lineLength + 1);
    if (!table->lines[table->lineCount]) {
        printf("Error of memory allocation\n");
        return 1;
    }
    snprintf(table->lines[table->lineCount], lineLength + 1, "%s", line);
    table->lineCount++;
    return 0;
}

size_t tableCountColumns(const char* line)
{
    if (!line)
        return 0;
    size_t count = 1;
    for (size_t i = 0; line[i]; i++) {
        if (line[i] == ',')
            count++;
    }
    return count;
}

size_t tableGetLineCount(const Table* table)
{
    return table ? table->lineCount : 0;
}

const char* tableGetLine(const Table* table, size_t index)
{
    if (!table || index >= table->lineCount)
        return NULL;
    return table->lines[index];
}

void tableFree(Table* table)
{
    if (!table)
        return;

    for (size_t i = 0; i < table->lineCount; i++) {
        free(table->lines[i]);
    }
    free(table->lines);
    free(table);
}
