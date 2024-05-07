#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../util/filePaths.h"
#include "helper.h"

#define MAX_DB_FILENAME_BYTES 512

struct OpenedDocs
{
    char *documentName;
    FILE *file;
    struct OpenedDocs *previous;
};

char *fileName_manual = "/manual.db";
FILE *file_manual;

struct OpenedDocs *openedDoc;

int openConnection()
{
    file_manual = fopen(strcat(getDataDir(), fileName_manual), "a");
    return NULL != file_manual;
}

int closeConnection()
{
    fclose(file_manual);
    while(openedDoc->file != NULL){
        fclose(openedDoc->file);
        openedDoc = openedDoc->previous;
    }
    free(openedDoc);
    return 0;
}

int openDocument(char *documentName) {
    char filepath[MAX_DB_FILENAME_BYTES];
    snprintf(filepath, sizeof(filepath), "%s/%s.db", getDataDir(), documentName);
    FILE *file = fopen(filepath, "a");
    if (file == NULL) {
        printf("Error opening file for document: %s", documentName);
        return 0;
    }
    struct OpenedDocs *newDoc = (struct OpenedDocs *)malloc(sizeof(struct OpenedDocs));
    if (newDoc == NULL) {
        printf("Memory allocation error for document: %s", documentName);
        fclose(file);
        return 0;
    }
    newDoc->documentName = documentName;
    newDoc->file = file;
    newDoc->previous = openedDoc;
    openedDoc = newDoc;
    if(!inManual(filepath, fileName_manual)) fprintf(file_manual, "%s\n", filepath);
    return 1;
}