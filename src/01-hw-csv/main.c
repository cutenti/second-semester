#include "dynamicTable.h"
#include "output.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
        return printf("Usage: %s <file.csv>\n", argv[0]), 1;

    FILE* f = fopen(argv[1], "r");
    if (!f)
        return perror("File error"), 1;

    Table* table = tableInit();
    char* line = NULL;
    size_t len = 0;
    size_t colCount = 0;

    while (getline(&line, &len, f) != -1) {
        if (colCount == 0)
            colCount = tableCountColumns(line); // Считаем один раз по первой строке
        addLine(table, line);
    }

    size_t* widths = calculateColumnWidths(table, colCount);

    FILE* out = fopen("output.txt", "w");
    if (out) {
        outputTable(out, table, colCount, widths);
        fclose(out);
    }

    free(widths);
    free(line);
    tableFree(table);
    fclose(f);
    return 0;
}
