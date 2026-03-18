#include "output.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void outputTable(FILE* outputFile, Table* table, size_t columnCount, const size_t* lenColumns)
{
    size_t lineCount = table->lineCount;

    for (size_t iLine = 0; iLine < lineCount; iLine++) {
        char* line = table->lines[iLine];
        char* separatedLine[columnCount];
        for (size_t i = 0; i < columnCount; i++) {
            separatedLine[i] = NULL;
        }

        char* token = strtok(line, ",\n");
        for (size_t i = 0; i < columnCount; i++) {
            if (token)
                separatedLine[i] = token;
            token = strtok(NULL, ",\n");
        }

        for (size_t iToken = 0; iToken < columnCount; iToken++) {
            size_t lenColumn = lenColumns[iToken];
            fputc('+', outputFile);

            if (iLine == 0 || iLine == 1) {
                for (size_t i = 0; i < lenColumn + 2; i++)
                    fputc('=', outputFile);
            } else {
                for (size_t i = 0; i < lenColumn + 2; i++)
                    fputc('-', outputFile);
            }
        }
        fputc('+', outputFile);
        fputc('\n', outputFile);

        fputc('|', outputFile);
        for (size_t iToken = 0; iToken < columnCount; iToken++) {
            token = separatedLine[iToken];
            int lenColumn = (int)lenColumns[iToken];

            if (iLine == 0) {
                fprintf(outputFile, " %-*s |", lenColumn, token);
            } else {
                char* endValue = NULL;
                if (token) {
                    strtod(token, &endValue); // преобразование в число, указатель на конец считывания числа
                } else {
                    fprintf(outputFile, " %*s ", lenColumn, "");
                }
                if (*endValue == '\0') {
                    fprintf(outputFile, " %*s |", lenColumn, token);
                } else {
                    fprintf(outputFile, " %-*s |", lenColumn, token);
                }
            }
        }
        fputc('\n', outputFile);

        if (iLine == lineCount - 1) {
            for (size_t iToken = 0; iToken < columnCount; iToken++) {
                size_t lenColumn = lenColumns[iToken];
                fputc('+', outputFile);

                for (size_t i = 0; i < lenColumn + 2; i++) {
                    fputc('-', outputFile);
                }
            }
            fputc('+', outputFile);
        }
    }
}
