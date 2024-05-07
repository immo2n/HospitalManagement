#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getWorkingDir()
{
    char cwd[100];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        char *workingDir = malloc(sizeof(cwd));
        if (workingDir == NULL) {
            printf("FETAL ERROR: Error allocating memory for working directory\n");
            return NULL;
        }
        strcpy(workingDir, cwd);
        return workingDir;
    }
    else {
        printf("FETAL ERROR: Error getting working directory\n");
        return NULL;
    }
}

char *getDataDir()
{
    char *workingDir = getWorkingDir();
    int workingDirLen = strlen(workingDir);
    char *dataDir = malloc(workingDirLen + 6);
    if (dataDir == NULL)
    {
        printf("FETAL ERROR: Error allocating memory for data directory\n");
        return NULL;
    }
    strcpy(dataDir, workingDir);
    strcat(dataDir, "/data");
    return dataDir;
}