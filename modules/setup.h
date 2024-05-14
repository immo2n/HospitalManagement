#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char adminName[50], adminPassword[100];

int setup(){
    //Reset values
    strcpy(adminName, "");
    strcpy(adminPassword, "");
    system("cls");
    printColoredBold(ANSI_COLOR_GREEN, "\t\t\t\tWELCOME TO HOSPITAL MANAGEMENT\n\n");
    printColored(ANSI_COLOR_CYAN, "\t\t\t\t Let's setup admin account\n\n\n");
    printColored(ANSI_COLOR_BLUE, "Set admin username(e.g Admin): ");
    scanf("%s", adminName);
    if(strlen(adminName) < 5){
        printColored(ANSI_COLOR_RED, "Invalid name for admin!");
        sleep(1);
        setup();
    }
    else {
        printColored(ANSI_COLOR_BLUE, "Set admin password(must be 4 or more characters): ");
        scanf("%s", adminPassword);
        if(strlen(adminPassword) < 4){
            printColored(ANSI_COLOR_RED, "Invalid password for admin!");
            sleep(1);
            setup();
        }
        else {
            put(DB_APP_STATE, prepareInsert(KEY_ADMIN_USERNAME, adminName));
            put(DB_APP_STATE, prepareInsert(KEY_ADMIN_PASSWORD, adminPassword));
            return 1;
        }
    }
}