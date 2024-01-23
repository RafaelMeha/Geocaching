#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "time.h"
#include <limits.h> 

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

typedef struct {
    int year;
    int month;
} YearMonth;

YearMonth parseDate(const char* dateStr);
int monthDifference(YearMonth date1, YearMonth date2);

void showAge(Cache *geocaches, int geocacheCount) {
    if (geocacheCount == 0) {
        printf("\033[1;31m\nNo geocache data available.\033[0m\n");
        return;
    }

    YearMonth oldestDate = {INT_MAX, INT_MAX};
    YearMonth newestDate = {0, 0};
    Cache oldestCache, newestCache;

    for (int i = 0; i < geocacheCount; i++) {
        YearMonth date = parseDate(geocaches[i].hidden_date);

        if ((date.year < oldestDate.year) || (date.year == oldestDate.year && date.month < oldestDate.month)) {
            oldestDate = date;
            oldestCache = geocaches[i];
        }
        if ((date.year > newestDate.year) || (date.year == newestDate.year && date.month > newestDate.month)) {
            newestDate = date;
            newestCache = geocaches[i];
        }
    }

    int diff = monthDifference(oldestDate, newestDate);

    printf("\nOldest Cache: %s (Date: %s)\n", oldestCache.name, oldestCache.hidden_date);
    printf("Newest Cache: %s (Date: %s)\n", newestCache.name, newestCache.hidden_date);
    printf("\n\033[1;32mDifference in months: %d\033[0m\n", diff);
    }

    YearMonth parseDate(const char* dateStr) {
    YearMonth ym;
    sscanf(dateStr, "%d-%d", &ym.year, &ym.month);
    return ym;
    }

    int monthDifference(YearMonth date1, YearMonth date2) {
    int years = date2.year - date1.year;
    int months = date2.month - date1.month;
    return years * 12 + months;
}


int compareByAltitude(const void *a, const void *b) {
    Cache *cacheA = (Cache *)a;
    Cache *cacheB = (Cache *)b;
    return cacheB->altitude - cacheA->altitude; 
}

int compareByStateAndFounds(const void *a, const void *b) {
    Cache *cacheA = (Cache *)a;
    Cache *cacheB = (Cache *)b;
    int stateComparison = strcmp(cacheA->state, cacheB->state);
    if (stateComparison == 0) { 
        return cacheB->founds - cacheA->founds;
    }
    return stateComparison;
}

int compareByHiddenDate(const void *a, const void *b) {
    Cache *cacheA = (Cache *)a;
    Cache *cacheB = (Cache *)b;
    return strcmp(cacheB->hidden_date, cacheA->hidden_date); 
}


void sortGeocaches(Cache *geocaches, int geocacheCount) {
    int sortOption;
    printf("Choose sorting option:\n1 - By Altitude\n2 - By State\n3 - By Hidden Date\n");
    scanf("%d", &sortOption);

    switch (sortOption) {
        case 1:
            qsort(geocaches, geocacheCount, sizeof(Cache), compareByAltitude);
            break;
        case 2:
            qsort(geocaches, geocacheCount, sizeof(Cache), compareByStateAndFounds);
            break;
        case 3:
            qsort(geocaches, geocacheCount, sizeof(Cache), compareByHiddenDate);
            break;
        default:
            printf("Invalid sorting option.\n");
            return;
    }

    listGeocaches(geocaches, geocacheCount);
}


typedef struct {
    char *state;
    int availableCount;
    int inactiveCount;
} StateCount;


void updateStateCounts(StateCount *counts, int *countSize, Cache cache) {
    for (int i = 0; i < *countSize; i++) {
        if (strcmp(counts[i].state, cache.state) == 0) {
            if (strcmp(cache.status, "AVAILABLE") == 0) {
                counts[i].availableCount++;
            } else if (strcmp(cache.status, "INACTIVE") == 0) {
                counts[i].inactiveCount++;
            }
            return;
        }
    }

    StateCount newCount;
    newCount.state = strdup(cache.state);
    newCount.availableCount = (strcmp(cache.status, "AVAILABLE") == 0) ? 1 : 0;
    newCount.inactiveCount = (strcmp(cache.status, "INACTIVE") == 0) ? 1 : 0;

    counts[*countSize] = newCount;
    (*countSize)++;
}

void showStateCounts(Cache *geocaches, int geocacheCount) {
    if (geocacheCount == 0) {
        printf("No geocache data available.\n");
        return;
    }

    StateCount *stateCounts = malloc(MAX_CODES * sizeof(StateCount));
    int countSize = 0;

    for (int i = 0; i < geocacheCount; i++){
        updateStateCounts(stateCounts, &countSize, geocaches[i]);
    }

    printf("State Counts (Available/Inactive):\n");
    for (int i = 0; i < countSize; i++) {
        printf("%s - Available: %d, Inactive: %d\n", 
            stateCounts[i].state, 
            stateCounts[i].availableCount, 
            stateCounts[i].inactiveCount);
    }

    for (int i = 0; i < countSize; i++) {
        free(stateCounts[i].state);
    }
    free(stateCounts);
}