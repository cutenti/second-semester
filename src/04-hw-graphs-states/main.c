#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Road {
    int cityTo;
    int length;
    struct Road* next;
} Road;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Error. The input file is not given.\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Error. Fail to open %s\n", argv[1]);
        return 1;
    }

    int cityCount, roadCount;
    fscanf(input, "%d %d", &cityCount, &roadCount);

    Road** adjacencyList = calloc(cityCount + 1, sizeof(Road*));

    for (int i = 0; i < roadCount; i++) {
        int from, to, length;
        fscanf(input, "%d %d %d", &from, &to, &length);

        Road* newRoad1 = malloc(sizeof(Road));
        newRoad1->cityTo = to;
        newRoad1->length = length;
        newRoad1->next = adjacencyList[from];
        adjacencyList[from] = newRoad1;

        Road* newRoad2 = malloc(sizeof(Road));
        newRoad2->cityTo = from;
        newRoad2->length = length;
        newRoad2->next = adjacencyList[to];
        adjacencyList[to] = newRoad2;
    }

    int stateCount;
    fscanf(input, "%d", &stateCount);
    int* capitals = malloc(stateCount * sizeof(int));
    for (int i = 0; i < stateCount; i++) {
        fscanf(input, "%d", &capitals[i]);
    }

    int* ownerState = calloc(cityCount + 1, sizeof(int));
    for (int i = 0; i < stateCount; i++) {
        ownerState[capitals[i]] = i + 1;
    }

    int occupiedCount = stateCount;

    while (occupiedCount < cityCount) {
        for (int state = 1; state <= stateCount; state++) {
            int closestCity = -1;
            int closestDistance = INT_MAX;

            for (int city = 1; city <= cityCount; city++) {
                if (ownerState[city] != state)
                    continue;

                Road* currentRoad = adjacencyList[city];
                while (currentRoad) {
                    int neighbor = currentRoad->cityTo;
                    int distance = currentRoad->length;

                    if (ownerState[neighbor] == 0) {
                        if (distance < closestDistance || (distance == closestDistance && (closestCity == -1 || neighbor < closestCity))) {
                            closestDistance = distance;
                            closestCity = neighbor;
                        }
                    }
                    currentRoad = currentRoad->next;
                }
            }

            if (closestCity != -1) {
                ownerState[closestCity] = state;
                occupiedCount++;

                if (occupiedCount == cityCount)
                    break;
            }
        }
    }

    for (int state = 1; state <= stateCount; state++) {
        printf("Государство %d: ", state);
        for (int city = 1; city <= cityCount; city++) {
            if (ownerState[city] == state)
                printf("%d ", city);
        }
        printf("\n");
    }

    fclose(input);

    for (int i = 1; i <= cityCount; i++) {
        Road* currentRoad = adjacencyList[i];
        while (currentRoad) {
            Road* temp = currentRoad;
            currentRoad = currentRoad->next;
            free(temp);
        }
    }
    free(adjacencyList);
    free(capitals);
    free(ownerState);

    return 0;
}
