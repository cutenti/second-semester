#include "dynamicTable.h"
#include "output.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Incorrect call, check count of arguments\n");
        return 1;
    }
    char* csvName = argv[1];
    FILE* csvFile = fopen(csvName, "r");
    if (!csvFile) {
        printf("File not found\n");
        return 1;
    }

    char* line = NULL;
    size_t lenLine = 0;
    int columnCount = 1;

    if (getline(&line, &lenLine, csvFile) == -1) {
        fclose(csvFile);
        free(line);
        return 1;
    }
    fseek(csvFile, 0, SEEK_SET);

    for (size_t i = 0; i < strlen(line); i++) {
        if (line[i] == ',') {
            columnCount += 1;
        }
    }

    size_t maxLenColumns[columnCount];
    memset(maxLenColumns, 0, sizeof(maxLenColumns));
    Table* table = tableInit();

    while (getline(&line, &lenLine, csvFile) != -1) {
        if (addLine(table, line)) {
            free(line);
            tableFree(table);
            fclose(csvFile);
            return 1;
        }

        char* token = strtok(line, ",\n");
        for (int i = 0; i < columnCount; i++) {
            if (token) {
                size_t lenToken = strlen(token);
                maxLenColumns[i] = lenToken >= maxLenColumns[i] ? lenToken : maxLenColumns[i];
                token = strtok(NULL, ",\n");
            }
        }
    }

    FILE* outputFile = fopen("output.txt", "w");

    outputTable(outputFile, table, (size_t)columnCount, maxLenColumns);

    free(line);
    tableFree(table);
    fclose(csvFile);
    return 0;
}
