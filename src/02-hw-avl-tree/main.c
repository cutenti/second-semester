#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeRepl(const char* filename, Dictionary* tree);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s <airports.txt>\n", argv[0]);
        return 1;
    }

    Dictionary* tree = newDictionary();
    if (tree == NULL) {
        perror("calloc in newDictionary");
        return 1;
    }

    FILE* airports = fopen(argv[1], "r");
    if (airports == NULL) {
        perror("fopen");
        deleteDictionary(tree);
        return 1;
    }

    char* line = NULL;
    size_t lineSize = 0;

    while (getline(&line, &lineSize, airports) != -1) {
        line[strcspn(line, "\n")] = '\0';
        char* colon = strchr(line, ':');
        if (!colon)
            continue;
        *colon = '\0';
        const char* code = line;
        const char* name = colon + 1;

        if (addAirport(code, name, tree)) {
            perror("addAirport");
            free(line);
            fclose(airports);
            deleteDictionary(tree);
            return 1;
        }
    }

    if (ferror(airports)) {
        perror("getline");
        free(line);
        fclose(airports);
        deleteDictionary(tree);
        return 1;
    }
    free(line);
    fclose(airports);

    executeRepl(argv[1], tree);

    deleteDictionary(tree);
    return 0;
}

void executeRepl(const char* filename, Dictionary* tree)
{
    char line[200];
    printf("Загружено %d аэропортов. Система готова к работе.\n", getDictionarySize(tree));

    while (true) {
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
            if (!arg) {
                printf("Usage: add <IATA>:<Name>\n");
                continue;
            }

            char* colon = strchr(arg, ':');
            if (!colon) {
                printf("Format: IATA:Name\n");
                continue;
            }

            *colon = '\0';
            char* code = arg;
            const char* name = colon + 1;

            if (find(code, tree)) {
                printf("Аэропорт с кодом '%s' уже существует.\n", code);
                continue;
            }
            if (addAirport(code, name, tree) == 0) {
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
            removeAirport(code, tree);
            printf("Аэропорт '%s' удалён из базы.\n", code);
        } else if (strcmp(command, "save") == 0) {
            FILE* out = fopen(filename, "w");
            if (!out) {
                perror("save fopen");
                continue;
            }
            if (save(out, tree) == 0) {
                printf("База сохранена: %d аэропортов.\n", getDictionarySize(tree));
            } else {
                printf("Ошибка сохранения.\n");
            }
            fclose(out);
        } else {
            printf("Неизвестная команда: %s\n", command);
        }
    }
}
