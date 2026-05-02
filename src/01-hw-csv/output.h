#pragma once
#include "dynamicTable.h"

// Prints the table to the specified output stream in a formatted manner
void outputTable(FILE*, Table*, size_t, const size_t*);

// Calculates the maximum width of each column based on the content of the table
size_t* calculateColumnWidths(Table* table, size_t colCount);
