#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char adminName[50], adminPassword[100];

int auth(Database *stateDatabase){
    system("cls");
    printColoredBold(ANSI_COLOR_GREEN, "\t\t\t\tWELCOME HOSPITAL MANAGEMENT\n\n");
    printColored(ANSI_COLOR_CYAN, "\t\t\t\t    Login to the system\n\n\n");
    printColored(ANSI_COLOR_BLUE, "Enter admin username: ");
    scanf("%s", adminName);
    if(strlen(adminName) < 5){
        printColored(ANSI_COLOR_RED, "Invalid name for admin!");
        sleep(1);
        auth(stateDatabase);
    }
    printColored(ANSI_COLOR_BLUE, "Enter admin password: ");
    scanf("%s", adminPassword);
    if(strlen(adminPassword) < 4){
        printColored(ANSI_COLOR_RED, "Invalid password for admin!");
        sleep(1);
        auth(stateDatabase);
    }
    
    char *username = fetch(stateDatabase, "admin_username").value;
    char *password = fetch(stateDatabase, "admin_password").value;

    if(strcmp(username, adminName) == 0 && strcmp(password, adminPassword) == 0){
        return 1;
    }
    else {
        printColored(ANSI_COLOR_RED, "Invalid credentials!");
        sleep(1);
        auth(stateDatabase);
    }
}