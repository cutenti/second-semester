#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void consolWork(const char* filename, AVLTree* tree);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s <airports.txt>\n", argv[0]);
        return 1;
    }

    AVLTree* tree = newTree();
    if (tree == NULL) {
        perror("calloc in newTree");
        return 1;
    }

    FILE* airports = fopen(argv[1], "r");
    if (airports == NULL) {
        perror("fopen");
        free(tree);
        return 1;
    }

    char* line = NULL;
    size_t lineSize = 0;

    while (getline(&line, &lineSize, airports) != -1) {
        line[strcspn(line, "\n")] = '\0';

        if (insertNode(line, tree)) {
            perror("insertNode");
            free(line);
            fclose(airports);
            free(tree);
            return 1;
        }
    }

    if (ferror(airports)) {
        perror("getline");
        free(line);
        fclose(airports);
        free(tree);
        return 1;
    }
    free(line);
    fclose(airports);

    consolWork(argv[1], tree);

    free(tree);
    return 0;
}

void consolWork(const char* filename, AVLTree* tree)
{
    char line[200];
    printf("Загружено %d аэропортов. Система готова к работе.\n", tree->number);

    while (1) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin))
            break;

        line[strcspn(line, "\n")] = '\0';

        char* command = strtok(line, " ");

        if (strcmp(command, "quit") == 0) {
            break;
        } else if (strcmp(command, "find") == 0) {
            char* code = strtok(NULL, " ");
            if (!code) {
                printf("Usage: find <IATA>\n");
                continue;
            }
            const char* name = find(code, tree);
            if (name) {
                printf("%s → %s\n", code, name);
            } else {
                printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
            }
        } else if (strcmp(command, "add") == 0) {
            char* arg = strtok(NULL, "");
            if (!arg || !strchr(arg, ':')) {
                printf("Usage: add <IATA>:<Name>\n");
                continue;
            }

            char code[4] = { 0 };
            strncpy(code, arg, 3);
            code[3] = '\0';

            if (find(code, tree)) {
                printf("Аэропорт с кодом '%s' уже существует.\n", code);
                continue;
            }
            if (insertNode(arg, tree) == 0) {
                printf("Аэропорт '%s' добавлен в базу.\n", code);
            } else {
                printf("Ошибка при добавлении аэропорта '%s'.\n", code);
            }
        } else if (strcmp(command, "delete") == 0) {
            char* code = strtok(NULL, " ");
            if (!code) {
                printf("Usage: delete <IATA>\n");
                continue;
            }
            if (!find(code, tree)) {
                printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
                continue;
            }
            deleteNode(code, tree);
            printf("Аэропорт '%s' удалён из базы.\n", code);
        } else if (strcmp(command, "save") == 0) {
            FILE* out = fopen(filename, "w");
            if (!out) {
                perror("save fopen");
                continue;
            }
            if (save(out, tree) == 0) {
                printf("База сохранена: %d аэропортов.\n", tree->number);
            } else {
                printf("Ошибка сохранения.\n");
            }
            fclose(out);
        } else {
            printf("Неизвестная команда: %s\n", command);
        }
    }
}
