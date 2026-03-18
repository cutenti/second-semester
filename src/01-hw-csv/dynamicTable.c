#include "dynamicTable.h"

#include <stdlib.h>
#include <string.h>

Table* tableInit(void)
{
    Table* table = calloc(1, sizeof(Table));
    return table;
}

int addLine(Table* table, const char* line)
{
    if (!table || !line)
        return 1;

    size_t lineLength = strlen(line);
    size_t needSize = table->lineCount + 1;

    if (needSize > table->capacity) {
        size_t newCapacity = table->lineCount * 2 < needSize ? needSize : table->lineCount * 2;

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

void tableFree(Table* table)
{
    for (size_t i = 0; i < table->lineCount; i++) {
        free(table->lines[i]);
    }
    free(table->lines);
    free(table);
}
