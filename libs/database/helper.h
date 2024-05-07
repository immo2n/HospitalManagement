#include <stdio.h>
#include <string.h>

#define MAX_PATH_LENGTH 512

int inDb(FILE *db, char *str) {
    if (db == NULL) return -1;
    char line[256];
    size_t len = strlen(str);
    int lineNumber = 0;
    while (fgets(line, sizeof(line), db)) {
        lineNumber++;
        //We will check for new lines and also, null character
        if (strncmp(line, str, len) == 0 && (line[len] == '\n' || line[len] == '\0')) {
            return lineNumber;
        }
    }
    return 0;
}