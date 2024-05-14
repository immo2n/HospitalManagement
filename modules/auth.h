#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char adminName[50], adminPassword[100];
int tries = 0;
int maxTries = 3;

int auth(int newCall){
    //Reset values
    strcpy(adminName, "");
    strcpy(adminPassword, "");
    if(newCall) tries = 0;
    system("cls");
    if(maxTries == tries){
        printColored(ANSI_COLOR_YELLOW, "Invalid credentials! Maximum tries reached!\n");
        sleep(1);
        return 0;
    }
    printColoredBold(ANSI_COLOR_GREEN, "\t\t\t\tWELCOME TO HOSPITAL MANAGEMENT\n\n");
    printColored(ANSI_COLOR_CYAN, "\t\t\t\t      Login to the system\n\n\n");
    printColored(ANSI_COLOR_BLUE, "Enter admin username: ");
    scanf("%s", adminName);
    if(strlen(adminName) < 5){
        printColored(ANSI_COLOR_RED, "Invalid name for admin!");
        sleep(1);
        auth(0);
    }
    else {
        printColored(ANSI_COLOR_BLUE, "Enter admin password: ");
        scanf("%s", adminPassword);
        if(strlen(adminPassword) < 4){
            printColored(ANSI_COLOR_RED, "Invalid password for admin!");
            sleep(1);
            auth(0);
        }
        else {
            DataCell username = get(DB_APP_STATE, KEY_ADMIN_USERNAME);
            DataCell pass = get(DB_APP_STATE, KEY_ADMIN_PASSWORD);

            if(strcmp(username.value, adminName) == 0 && strcmp(pass.value, adminPassword) == 0){
                return 1;
            }
            else {
                printColored(ANSI_COLOR_RED, "Invalid credentials!\n");
                tries++;
                sleep(1);
                auth(0);
            }
        }
    }
}