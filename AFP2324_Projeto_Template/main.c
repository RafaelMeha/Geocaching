#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODES 2000  // Define the maximum number of geocaches
#define MAX_LINE_LENGTH 1024  // Define the maximum length of a line in the file

// Define a structure to store information about a geocache
typedef struct {
    char *code; // Unique code of the geocache
    char *name; // Name of the geocache
    char *state; // State where the geocache is located
    char *owner; // Owner of the geocache
    double latitude; // Latitude coordinate
    double longitude; // Longitude coordinate
    char *kind; // Type of the geocache
    char *size; // Size of the geocache
    double difficulty; // Difficulty rating
    double terrain; // Terrain rating
    char *status; // Status of the geocache (active, inactive, etc.)
    char *hidden_date; // Date when the geocache was hidden
    int founds; // Number of times found
    int not_found; // Number of times not found
    int favourites; // Number of times marked as favourite
    int altitude; // Altitude of the location
} Cache;

// Function to free memory allocated for a geocache
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

// Function to clear all geocaches from memory
void clearGeocaches(Cache **geocaches, int *geocacheCount) {
    for (int i = 0; i < *geocacheCount; i++) {
        freeGeocache(&(*geocaches)[i]);
    }
    free(*geocaches);
    *geocaches = NULL;
    *geocacheCount = 0;
    printf("\n\033[1;32mGeocaches cleared.\n\033[0m");
}

// Function to load geocaches from a file
void getGeocaches(char *file, Cache **geocaches, int *geocacheCount) {
    // This function opens the file, reads each line, parses the data, 
    // and stores it in the geocaches array
    FILE *f = fopen(file, "r");
    if (!f) {
        printf("\n\033[1;31mFile could not be opened.\n\033[0m");
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
        gc.code = token ? strdup(token) : NULL;

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
    printf("\n\033[1;32m%d geocaches loaded.\n\033[0m", *geocacheCount);
    
}

// Function to list all geocaches
void listGeocaches(Cache *geocaches, int geocacheCount) {
    // This function iterates through the geocaches array and prints 
    // the details of each geocache
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;31mNo geocaches to display.\n\033[0m");
        return;
    }

    printf("\nListing all geocaches:\n");
    for (int i = 0; i < geocacheCount; i++) {
        printf("\nCache %d: \n Code: %s, Name: %s, State: %s, Owner: %s, Latitude: %.6f, Longitude: %.6f, Kind: %s, Size: %s, Difficulty: %.1f, Terrain: %.1f, Status: %s, Hidden date: %s, Founds: %d, Not founds: %d, Favourites: %d, Altitude: %d\n", 
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
}

// Main function
int main() {
    // This is the main function where the user can choose different options 
    // like loading geocaches, clearing them, listing them, etc.
    Cache *geocaches = NULL;
    int geocacheCount = 0;
    int option;
    char file[256];

    do {
        printf("\n\033[1;34m---- GEOCACHING ----\n\033[0m\n");
        printf("\033[1;36m1. Load\n2. Clear\n3. Quit\n4. List\n\033[0m\n\033[1;35mChoose an option: \033[0m");
        scanf("%d", &option);
        getchar();

        switch(option) {
            case 1:
                printf("\n\033[1;33mEnter filename: \033[0m");
                fgets(file, sizeof(file), stdin);
                file[strcspn(file, "\n")] = 0; 
                getGeocaches(file, &geocaches, &geocacheCount);
                break;
            case 2:
                clearGeocaches(&geocaches, &geocacheCount);
                break;
            case 3:
                printf("\n\033[1;32mGoodbye! :(\n\033[0m");
                clearGeocaches(&geocaches, &geocacheCount); 
                return EXIT_SUCCESS;
            case 4:
                listGeocaches(geocaches, geocacheCount);
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (1);

    return EXIT_SUCCESS;
}
