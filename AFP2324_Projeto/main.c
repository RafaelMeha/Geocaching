#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

#define MAX_CODES 2000  
#define MAX_LINE_LENGTH 1024  

int main() {
    
    Cache *geocaches = NULL;
    int geocacheCount = 0;
    int option;
    char file[256];

    do {
        printf("\n\033[1;34m---- GEOCACHING ----\n\033[0m\n");
        printf("\033[1;36m1. Load\n2. Clear\n3. Quit\n4. List\n5. FoundP\n6. Search\033[0m\n\033[1;35m\nChoose an option: \033[0m");
        scanf("%d", &option);
        getchar();

        switch(option) {
            case 1 :

                if(geocacheCount > 0){
                    printf("\033[31mCache data exists. Please clear it first.\n");  
                } else {
                    printf("\n\033[1;33mEnter filename: \033[0m");
                    fgets(file, sizeof(file), stdin);
                    file[strcspn(file, "\n")] = 0; 
                    getGeocaches(file, &geocaches, &geocacheCount);
                }
                break;
            case 2:
                if(geocacheCount > 0){
                    printf("\n\033[1;33m CONFIRM?\n\033[0m");
                    printf("\n1. YES\n2. NO\n");
                    printf("\n\033[1;35mChoose an option: \033[0m");
                
                    scanf("%d", &option);

                    if (option == 1){
                        printf("\n\033[32mSTATUS: CONFIRMED\n");
                        clearGeocaches(&geocaches, &geocacheCount);
                        break;
                    } else if (option == 2){
                        printf("\033[32mSTATUS: DENIED");
                        break;
                    } else {
                        printf("\033[31mOK: INVALID");
                        break;
                    }
                } else {
                    printf("\n\033[31mCache is already clear.\n");
                
                }
                break;
            case 3:
                printf("\n\033[1;32mGoodbye! :(\n\033[0m");
                clearGeocaches(&geocaches, &geocacheCount); 
                return EXIT_SUCCESS;
            case 4:
                listGeocaches(geocaches, geocacheCount);
                break;
            case 5:
                foundPercentage(geocaches, geocacheCount);
                break;
            case 6:
                if (geocacheCount > 0) {
                    char searchCode[50];
                    printf("\n\033[1;33mEnter the code of the geocache to search: \033[0m");
                    fgets(searchCode, sizeof(searchCode), stdin);
                    searchCode[strcspn(searchCode, "\n")] = 0; // Remove newline character
                    searchGeocacheByCode(geocaches, geocacheCount, searchCode);
                } else {
                    printf("\n\033[1;31mNo geocaches loaded.\n\033[0m");
                }
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (1);

    return EXIT_SUCCESS;
}
