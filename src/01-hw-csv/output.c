#include "output.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printSeparator(FILE* out, size_t colCount, const size_t* widths, char symbol)
{
    for (size_t i = 0; i < colCount; i++) {
        fputc('+', out);
        for (size_t j = 0; j < widths[i] + 2; j++) {
            fputc(symbol, out);
        }
    }
    fprintf(out, "+\n");
}

static void printCell(FILE* out, const char* token, size_t width, int isHeader)
{
    if (!token) {
        fprintf(out, " %*s |", (int)width, "");
        return;
    }

    char* endPtr;
    strtod(token, &endPtr);
    int isNumeric = (token[0] != '\0' && (*endPtr == '\0' || *endPtr == '\n' || *endPtr == '\r'));

    if (isHeader || !isNumeric) {
        fprintf(out, " %-*s |", (int)width, token);
    } else {
        fprintf(out, " %*s |", (int)width, token);
    }
}

void outputTable(FILE* out, Table* table, size_t colCount, const size_t* widths)
{
    size_t rowCount = tableGetLineCount(table);

    for (size_t i = 0; i < rowCount; i++) {
        char* lineCopy = strdup(tableGetLine(table, i));

        char separateChar = (i == 0 || i == 1) ? '=' : '-';
        printSeparator(out, colCount, widths, separateChar);

        fputc('|', out);
        char* token = strtok(lineCopy, ",\n\r");
        for (size_t j = 0; j < colCount; j++) {
            printCell(out, token, widths[j], i == 0);
            token = strtok(NULL, ",\n\r");
        }
        fputc('\n', out);

        if (i == rowCount - 1) {
            printSeparator(out, colCount, widths, '-');
        }
        free(lineCopy);
    }
}

size_t* calculateColumnWidths(Table* table, size_t colCount)
{
    size_t* widths = calloc(colCount, sizeof(size_t));
    size_t rowCount = tableGetLineCount(table);

    for (size_t i = 0; i < rowCount; i++) {
        char* lineCopy = strdup(tableGetLine(table, i));
        char* token = strtok(lineCopy, ",\n\r");
        for (size_t j = 0; j < colCount && token; j++) {
            size_t len = strlen(token);
            if (len > widths[j])
                widths[j] = len;
            token = strtok(NULL, ",\n\r");
        }
        free(lineCopy);
    }
    return widths;
}
