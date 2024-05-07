#include <stdio.h>
#include <string.h>

#define MAX_PATH_LENGTH 512

int inManual(char *str, char *manualName) {
    char filepath[MAX_PATH_LENGTH];
    snprintf(filepath, sizeof(filepath), "%s/%s", getDataDir(), manualName);
    FILE *file = fopen(filepath, "r");
    if (file == NULL) return 0;
    char line[256];
    size_t len = strlen(str);
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, str, len) == 0 && (line[len] == '\n' || line[len] == '\0')) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}