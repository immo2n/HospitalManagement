#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/filePaths.h"
#include "helper.h"

#define MAX_DB_FILENAME_BYTES 512

struct OpenedDocs
{
    char *documentPath;
    FILE *file;
    struct OpenedDocs *previous;
};

char *fileName_manual = "/manual.db";
FILE *file_manual;
struct OpenedDocs *openedDoc;

void insert(FILE *db, char *data){
    if(!inDb(db, data)) fprintf(db, "%s\n", data);
}

int openConnection()
{
    file_manual = fopen(strcat(getDataDir(), fileName_manual), "a+");
    return NULL != file_manual;
}

int closeConnection()
{
    fclose(file_manual);
    while(openedDoc != NULL){
        fclose(openedDoc->file);
        struct OpenedDocs *temp = openedDoc;
        openedDoc = openedDoc->previous;
        free(temp->documentPath);
        free(temp);
    }
    return 0;
}

FILE *isOpened(char *docPath){
    struct OpenedDocs *check = openedDoc;
    while(check != NULL){
        if(strcmp(check->documentPath, docPath) == 0) return check->file;
        check = check->previous;
    }
    return NULL;
}

FILE *openDocument(char *documentName) {
    char filepath[MAX_DB_FILENAME_BYTES];
    snprintf(filepath, sizeof(filepath), "%s/%s.db", getDataDir(), documentName);
    //Caching - harmless if skipped
    FILE *file = isOpened(filepath);
    if(NULL != file) {
        return file;
    }
    //Not in cache, so open as new
    file = fopen(filepath, "a+");
    if (file == NULL) {
        printf("Error opening file for document: %s", documentName);
        return NULL;
    }
    //Allocate memory for cache linked list
    struct OpenedDocs *newDoc = (struct OpenedDocs *)malloc(sizeof(struct OpenedDocs));
    if (newDoc == NULL) {
        printf("Memory allocation error for document: %s", documentName);
        fclose(file);
        return NULL;
    }
    //Allocate memory for the path
    newDoc->documentPath = malloc(strlen(filepath) + 1);
    if (newDoc->documentPath == NULL) {
        printf("Memory allocation error for document path: %s", documentName);
        fclose(file);
        free(newDoc);
        return NULL;
    }
    strcpy(newDoc->documentPath, filepath);
    newDoc->file = file;
    newDoc->previous = openedDoc;
    openedDoc = newDoc;
    //Insert path to manual
    insert(file_manual, filepath);
    return file;
}