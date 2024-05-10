#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char adminName[50], adminPassword[100];

int setup(Database *stateDatabase){
    system("cls");
    printColoredBold(ANSI_COLOR_GREEN, "\t\t\t\tWELCOME HOSPITAL MANAGEMENT\n\n");
    printColored(ANSI_COLOR_CYAN, "\t\t\t\t Let's setup admin account\n\n\n");
    printColored(ANSI_COLOR_BLUE, "Set admin username(e.g Admin): ");
    scanf("%s", adminName);
    if(strlen(adminName) < 5){
        printColored(ANSI_COLOR_RED, "Invalid name for admin!");
        sleep(1);
        setup(stateDatabase);
    }
    printColored(ANSI_COLOR_BLUE, "Set admin password(must be 4 or more characters): ");
    scanf("%s", adminPassword);
    if(strlen(adminPassword) < 4){
        printColored(ANSI_COLOR_RED, "Invalid password for admin!");
        sleep(1);
        setup(stateDatabase);
    }
    insert(stateDatabase, prepareInsert("admin_username", adminName));
    insert(stateDatabase, prepareInsert("admin_password", adminPassword));
    return 1;
}