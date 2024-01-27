typedef struct {
    char *code; 
    char *name; 
    char *state; 
    char *owner; 
    double latitude; 
    double longitude; 
    char *kind; 
    char *size; 
    double difficulty; 
    double terrain;
    char *status; 
    char *hidden_date;
    int founds;
    int not_found; 
    int favourites; 
    int altitude; 
} Cache;

void freeGeocache(Cache *gc);

void foundPercentage( Cache *geocaches, int geocacheCount);

void clearGeocaches(Cache **geocaches, int *geocacheCount);

void getGeocaches(char *file, Cache **geocaches, int *geocacheCount);

void listGeocaches(Cache *geocaches, int geocacheCount);


void showAge(Cache *geocaches, int geocacheCount);

void sortGeocaches(Cache *geocaches, int geocacheCount);

void showStateCounts(Cache *geocaches, int geocacheCount);

void calculateMatrix81(Cache *geocaches, int geocacheCount);

