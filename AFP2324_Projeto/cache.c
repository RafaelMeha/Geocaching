#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

#define MAX_CODES 2000  
#define MAX_LINE_LENGTH 1024  


void freeGeocache(Cache *gc) {
    free(gc->code);
    free(gc->name);
    free(gc->state);
    free(gc->owner);
    free(gc->kind);
    free(gc->size);
    free(gc->status);
    free(gc->hidden_date);
}


void clearGeocaches(Cache **geocaches, int *geocacheCount) {
    for (int i = 0; i < *geocacheCount; i++) {
        freeGeocache(&(*geocaches)[i]);
    }
    free(*geocaches);
    *geocaches = NULL;
    *geocacheCount = 0;
    printf("\n\033[1;32mGeocaches cleared.\n\033[0m");
}

void getGeocaches(char *file, Cache **geocaches, int *geocacheCount) {
    
    FILE *f = fopen(file, "r");
    if (!f) {
        printf("\n\033[1;31mFile not found.\n\033[0m");
        return;
    }

    *geocaches = malloc(MAX_CODES * sizeof(Cache));
    *geocacheCount = 0;

    char line[MAX_LINE_LENGTH];
    const char delimiter[] = ";";
    char *token;

    fgets(line, sizeof(line), f);

    while (fgets(line, sizeof(line), f) && *geocacheCount < MAX_CODES) {
        Cache gc = {0};

        token = strtok(line, delimiter);
        char *code = token ? strdup(token) : NULL;

        int exists = 0;
        for (int i = 0; i < *geocacheCount; i++) {
            if (strcmp((*geocaches)[i].code, code) == 0) {
                exists = 1;
                break;
            }
        }

        if (exists) {
            free(code); 
            continue; 
        }

        gc.code = code;

        token = strtok(NULL, delimiter);
        gc.name = token ? strdup(token) : NULL;

        token = strtok(NULL, delimiter);
        gc.state = token ? strdup(token) : NULL;

        token = strtok(NULL, delimiter);
        gc.owner = token ? strdup(token) : NULL;

        token = strtok(NULL, delimiter);
        if (token) {
            gc.altitude = atoi(token);
            char *newline = strchr(token, '\n'); 
            if (newline) *newline = '\0';
        } else {
            gc.altitude = 0;
        }

        token = strtok(NULL, delimiter);
        gc.longitude = token ? atof(token) : 0.0;

        token = strtok(NULL, delimiter);
        gc.kind = token ? strdup(token) : NULL;

        token = strtok(NULL, delimiter);
        gc.size = token ? strdup(token) : NULL;

        token = strtok(NULL, delimiter);
        gc.difficulty = token ? atoi(token) : 0;

        token = strtok(NULL, delimiter);
        gc.terrain = token ? atof(token) : 0.0;

        token = strtok(NULL, delimiter);
        gc.status = token ? strdup(token) : NULL;

        token = strtok(NULL, delimiter);
        gc.hidden_date = token ? strdup(token) : NULL;

        token = strtok(NULL, delimiter);
        gc.founds = token ? atoi(token) : 0;

        token = strtok(NULL, delimiter);
        gc.not_found = token ? atoi(token) : 0;

        token = strtok(NULL, delimiter);
        gc.favourites = token ? atoi(token) : 0;

        token = strtok(NULL, delimiter);
        if (token) {
            gc.altitude = atoi(token);
            char *newline = strchr(token, '\n');
            if (newline) *newline = '\0';
        } else {
            gc.altitude = 0;
        }

        (*geocaches)[*geocacheCount] = gc;
        (*geocacheCount)++;
    } 
    fclose(f);
    printf("\n\033[1;32m%d Geocaches loaded.\n\033[0m", *geocacheCount);
    
}

void listGeocaches(Cache *geocaches, int geocacheCount) {
    
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;31mNo geocaches loaded.\n\033[0m");
        return;
    }

    printf("\nListing all geocaches:\n");
    printf("=======================================================================================================================================================================================================\n");
    printf("| CACHE | CODE |        NAME        |      OWNER      | LATITUDE | LONGITUDE |      KIND      |     SIZE     |   DIFFICULTY   |     TERRAIN     |  STATUS  | HIDDEN DATE | FOUNDS | NOT FOUNDS | FAVOURITES | ALTITUDE |\n");
    for (int i = 0; i < geocacheCount; i++) {
        printf("\n| %d | %s | %s | %s | %s | %.6f | %.6f | %s | %s | %.1f | %.1f | %s | %s | %d | %d | %d | %d |\n", 
       i + 1, 
       geocaches[i].code, 
       geocaches[i].name, 
       geocaches[i].state, 
       geocaches[i].owner, 
       geocaches[i].latitude, 
       geocaches[i].longitude, 
       geocaches[i].kind, 
       geocaches[i].size, 
       geocaches[i].difficulty, 
       geocaches[i].terrain, 
       geocaches[i].status, 
       geocaches[i].hidden_date, 
       geocaches[i].founds, 
       geocaches[i].not_found, 
       geocaches[i].favourites, 
       geocaches[i].altitude);
    }
    printf("\n================================================================================================================================================================================================\n");
}

float calculatePercent(float nFounds, float nNotFounds){
    float res = 0;
    res = ((nFounds) / (nFounds + nNotFounds)) * 100;

    return res;

}


void foundPercentage(Cache *geocaches, int geocacheCount) {
    
    float percent = 0;
    int nFounds, nNotFounds;
    nFounds = 0;
    nNotFounds = 0;

    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;31mNo geocaches loaded.\n\033[0m");
        return;
    }

    printf("\nListing all geocaches:\n");
    printf("==================================================================================================================================================================================================================================\n");
    printf("| CACHE %%| CACHE | CODE |        NAME        |      OWNER      | LATITUDE | LONGITUDE |      KIND      |     SIZE     |   DIFFICULTY   |     TERRAIN     |  STATUS  | HIDDEN DATE | FOUNDS | NOT FOUNDS | FAVOURITES | ALTITUDE |\n");
    for (int i = 0; i < geocacheCount; i++) {

        nNotFounds = geocaches[i].not_found;
        nFounds = geocaches[i].founds;

        percent = calculatePercent(nFounds, nNotFounds);

        printf("\n| %.0f%% | %d | %s | %s | %s | %s | %.6f | %.6f | %s | %s | %.1f | %.1f | %s | %s | %d | %d | %d | %d |\n", 
       percent,
       i + 1, 
       geocaches[i].code, 
       geocaches[i].name, 
       geocaches[i].state, 
       geocaches[i].owner, 
       geocaches[i].latitude, 
       geocaches[i].longitude, 
       geocaches[i].kind, 
       geocaches[i].size, 
       geocaches[i].difficulty, 
       geocaches[i].terrain, 
       geocaches[i].status, 
       geocaches[i].hidden_date, 
       geocaches[i].founds, 
       geocaches[i].not_found, 
       geocaches[i].favourites, 
       geocaches[i].altitude);
    }
    printf("\n================================================================================================================================================================================================\n");
}


void searchGeocacheByCode(Cache *geocaches, int geocacheCount, char *searchCode) {
    int found = 0;

    for (int i = 0; i < geocacheCount; i++) {
        if (strcmp(geocaches[i].code, searchCode) == 0) {
            printf("\nGeocache found:\n");
            printf("\n| %d | %s | %s | %s | %s | %.6f | %.6f | %s | %s | %.1f | %.1f | %s | %s | %d | %d | %d | %d |\n", 
    i + 1, 
    geocaches[i].code, 
    geocaches[i].name, 
    geocaches[i].state, 
    geocaches[i].owner, 
    geocaches[i].latitude, 
    geocaches[i].longitude, 
    geocaches[i].kind, 
    geocaches[i].size, 
    geocaches[i].difficulty, 
    geocaches[i].terrain, 
    geocaches[i].status, 
    geocaches[i].hidden_date, 
    geocaches[i].founds, 
    geocaches[i].not_found, 
    geocaches[i].favourites, 
    geocaches[i].altitude);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Geocache with code %s not found.\n", searchCode);
    }
}
