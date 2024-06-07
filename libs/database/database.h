/*
* Written by: Md. Monoarul Islam Moon
* Created on: 11-5-2024
* Its just a prove of concept, not a real database system.
* It's a simple key-value store system based on FILE
* Use at your own risk!
* And an advice: "NEVER WRITE YOUR OWN DATABASE SYSTEM FOR PRODUCTION USE!"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../util/filePaths.h"

#define MAX_DB_FILENAME_BYTES 512
#define MAX_KEY_LENGTH 256  // 256B
#define MAX_VALUE_LENGTH 1024 * 5 //5MB
#define LOG_STATUS_MAX_SIZE 50
#define LOG_MESSAGE_MAX_SIZE 100

typedef struct {
    char *name;
    char *status;
    char *message;
    FILE *file;
} Database;

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} DataCell;

typedef struct OpenedDocs {
    char *documentPath;
    FILE *file;
    struct OpenedDocs *previous;
} OpenedDocs;

char *manualDatabaseName = "manual";
Database manualDatabase;

/*Opening multiple documents is not recommended but,
if the user dose it, still store them to close later */

OpenedDocs *openedDoc = NULL;
int openedDocCount = 0;

DataCell prepareInsert(char *key, char *value) {
    DataCell dataCell;
    strncpy(dataCell.key, key, MAX_KEY_LENGTH - 1);
    dataCell.key[MAX_KEY_LENGTH - 1] = '\0';
    strncpy(dataCell.value, value, MAX_VALUE_LENGTH - 1);
    dataCell.value[MAX_VALUE_LENGTH - 1] = '\0';
    return dataCell;
}

void cacheDocument(FILE *file, Database *database, char *filepath){
    OpenedDocs *newDoc = malloc(sizeof(OpenedDocs));
    if (newDoc == NULL) {
        fclose(file);
        strcpy(database->status, "MEMORY_ALLOCATION_ERROR");
        strcpy(database->message, "Memory allocation error for document");
        database->file = NULL;
        return;
    }

    newDoc->documentPath = malloc(strlen(filepath) + 1);
    if (newDoc->documentPath == NULL) {
        fclose(file);
        free(newDoc);
        strcpy(database->status, "MEMORY_ALLOCATION_ERROR");
        strcpy(database->message, "Memory allocation error for document");
        database->file = NULL;
        return;
    }

    strcpy(newDoc->documentPath, filepath);
    newDoc->file = file;
    newDoc->previous = openedDoc;
    openedDoc = newDoc;
}

DataCell fetch(Database *database, char *key){
    DataCell dataCell;
    strcpy(dataCell.key, key);
    strcpy(dataCell.value, PREFIX_NULL_STRING);
    /* Here we are doing Linear Search, not efficient at all...
    we must do something about it in future! */
    //Prepare line for key, value, = (delimeter) and \n
    char line[MAX_KEY_LENGTH + MAX_VALUE_LENGTH + 2];
    char *stored_key, *stored_value;
    while (fgets(line, sizeof(line), database->file) != NULL) {
        //***Line scan***//
        //Looking the delimeter ending with = (first one)
        stored_key = strtok(line, "=");
        if (stored_key == NULL) {
            continue; //Invalid line, skip
        }
        //Looking the value ending with \n (first one)
        stored_value = strtok(NULL, "\n");
        if (stored_value == NULL) {
            continue; //Invalid line, skip
        }
        // Remove newline from value - only for store manner
        stored_value[strcspn(stored_value, "\n")] = '\0';
        if (strcmp(key, stored_key) == 0) { //check for key match
            strcpy(dataCell.value, stored_value);
            return dataCell;
        }
    }
    return dataCell;
}

DataCell *fetchAll(Database *database, int maxEntries){
    if(database->file == NULL) return NULL;
    DataCell *dataCells = malloc(sizeof(DataCell) * maxEntries);
    if(dataCells == NULL) return NULL;
    int i = 0;
    char line[MAX_KEY_LENGTH + MAX_VALUE_LENGTH + 2];
    char *stored_key, *stored_value;
    while (fgets(line, sizeof(line), database->file) != NULL) {
        stored_key = strtok(line, "=");
        if (stored_key == NULL) {
            continue; //Invalid line, skip
        }
        stored_value = strtok(NULL, "\n");
        if (stored_value == NULL) {
            continue; //Invalid line, skip
        }
        strcpy(dataCells[i].key, stored_key);
        strcpy(dataCells[i].value, stored_value);
        i++;
        if(i >= maxEntries) break;
    }
    return dataCells;
}

int delete(Database *database, char *key) {
    if (database->file == NULL) return -1;

    char tempFilename[MAX_DB_FILENAME_BYTES];
    snprintf(tempFilename, sizeof(tempFilename), "%s/%s_temp.db", getDataDir(), database->name);

    FILE *tempFile = fopen(tempFilename, "w+");
    if (tempFile == NULL) {
        return -1;
    }

    rewind(database->file);

    char line[MAX_KEY_LENGTH + MAX_VALUE_LENGTH + 2];
    char *stored_key, *stored_value;

    while (fgets(line, sizeof(line), database->file) != NULL) {
        stored_key = strtok(line, "=");
        if (stored_key == NULL) {
            continue;
        }

        stored_value = strtok(NULL, "\n");
        if (stored_value == NULL) {
            continue;
        }

        // If the key is not the one to be deleted, write it to the temporary file
        if (strcmp(key, stored_key) != 0) {
            fprintf(tempFile, "%s=%s\n", stored_key, stored_value);
        }
    }

    fclose(database->file);
    fclose(tempFile);

    char databasePath[MAX_DB_FILENAME_BYTES];
    snprintf(databasePath, sizeof(databasePath), "%s/%s.db", getDataDir(), database->name);
    
    if (unlink(databasePath) != 0) {
        return -1;
    }
    
    if (rename(tempFilename, databasePath) != 0) {
        return -1;
    }

    FILE *file = fopen(databasePath, "a+");
    database->file = file;

    cacheDocument(file, database, databasePath);

    if (database->file == NULL) {
        return -1;
    }

    return 1;
}

int exists(Database *database, char *key){
    if(NULL == database->file) return 0;
    char line[MAX_KEY_LENGTH + MAX_VALUE_LENGTH + 2];
    char *stored_key, *stored_value;
    while (fgets(line, sizeof(line), database->file) != NULL) {
        stored_key = strtok(line, "=");
        if (stored_key == NULL) {
            continue; //Invalid line, skip
        }
        if((strcmp(key, stored_key) == 0)) return 1;
    }
    return 0;
}

int insert(Database *database, DataCell dataCell){
    if(database->file != NULL){
        if(exists(database, dataCell.key)){
            //Update the data instead, delete the key
            delete(database, dataCell.key);
        };
        int writeResult = fprintf(database->file, "%s=%s\n", dataCell.key, dataCell.value);
        if (writeResult >= 0) {
            /*Flashing is needed for fprintf or, fwrite otherwise
            immediate insert request will be ignored by the OS(depends).
            So, we force flash the data to disk even if its small
            */
            fflush(database->file); //Flush the file
        }
        return writeResult;
    }
    return -1;
}

FILE *isOpened(char *docPath) {
    OpenedDocs *check = openedDoc;
    while (check != NULL) {
        if (strcmp(check->documentPath, docPath) == 0) return check->file;
        check = check->previous;
    }
    return NULL;
}

Database openDocument(char *documentName) {
    Database database;
    database.name = documentName;
    database.status = malloc(LOG_STATUS_MAX_SIZE * sizeof(char));
    database.message = malloc(LOG_MESSAGE_MAX_SIZE * sizeof(char));

    if (database.status == NULL || database.message == NULL) {
        strcpy(database.status, "MEMORY_ALLOCATION_ERROR");
        strcpy(database.message, "Memory allocation error for document");
        database.file = NULL;
        return database;
    }

    char filepath[MAX_DB_FILENAME_BYTES];
    snprintf(filepath, sizeof(filepath), "%s/%s.db", getDataDir(), documentName);

    FILE *file = isOpened(filepath);
    if (file != NULL) {
        database.file = file;
        strcpy(database.status, "CACHED");
        strcpy(database.message, "Loaded from old instance");
        return database;
    }

    file = fopen(filepath, "a+");
    if (file == NULL) {
        strcpy(database.status, "ERROR");
        strcpy(database.message, "Error opening file for document, tried cached first.");
        database.file = NULL;
        return database;
    }

    cacheDocument(file, &database, filepath);
    openedDocCount++;

    insert(&manualDatabase, prepareInsert(documentName, filepath));
    strcpy(database.message, "All okay while opening database document");
    strcpy(database.status, "OK");
    database.file = file;
    return database;
}

int openConnection() {
    manualDatabase = openDocument(manualDatabaseName);
    if (manualDatabase.file == NULL) {
        return 0;
    }
    return 1;
}

int closeConnection() {
    while (openedDoc != NULL) {
        OpenedDocs *temp = openedDoc;
        openedDoc = openedDoc->previous;
        fclose(temp->file);
        free(temp->documentPath);
        free(temp);
        openedDocCount--;
    }
    return 1;
}

DataCell get(char *documentName, char *key){
    DataCell dataCell;
    strcpy(dataCell.key, key);
    if(!openConnection()){
        printf("FATAL ERROR: Could not open database!\n");
        return dataCell;
    }
    Database db = openDocument(documentName);
    if(strcmp(db.status, "OK") == 0){
        dataCell = fetch(&db, key);
    }
    closeConnection();
    return dataCell;
}

DataCell *getAsLines(char *documentName, int maxEntries){
    if(!openConnection()){
        printf("FATAL ERROR: Could not open database!\n");
        return NULL;
    }
    DataCell *dataCells;
    Database db = openDocument(documentName);
    if(strcmp(db.status, "OK") == 0){
        dataCells = fetchAll(&db, maxEntries);
    }
    closeConnection();
    return dataCells;
}

int put(char *documentName, DataCell dataCell){
    if(!openConnection()){
        printf("FATAL ERROR: Could not open database!\n");
        return 0;
    }
    Database db = openDocument(documentName);
    if(strcmp(db.status, "OK") == 0){
        insert(&db, dataCell);
    }
    closeConnection();
    return 1;
}

int pop(char *documentName, char *key){
    if(!openConnection()){
        printf("FATAL ERROR: Could not open database!\n");
        return 0;
    }
    Database db = openDocument(documentName);
    if(strcmp(db.status, "OK") == 0){
        delete(&db, key);
    }
    closeConnection();
    return 1;
}