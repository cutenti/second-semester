#pragma once
#include <stdio.h>

// Dynamic table for storing lines of CSV file
typedef struct Table Table;

// Initializes the table and returns a pointer to it
Table* tableInit(void);

// Adds a line to the table. Returns 0 on success, 1 on failure
int addLine(Table* table, const char* line);

// Counts the number of columns in a line (based on commas)
size_t tableCountColumns(const char* line);

// Returns the number of lines in the table
size_t tableGetLineCount(const Table* table);

// Returns the line at the specified index, or NULL if index is out of bounds
const char* tableGetLine(const Table* table, size_t index);

// Frees the memory allocated for the table
void tableFree(Table*);
