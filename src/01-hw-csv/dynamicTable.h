#pragma once
#include <stdio.h>

typedef struct {
    char** lines;
    size_t lineCount;
    size_t capacity;
} Table;

Table* tableInit(void);

int addLine(Table*, const char*);

void tableFree(Table*);
