#include <stdio.h>
#include "libs/util/fontStyles.h"
#include "libs/util/keySets.h"
#include "libs/database/database.h"
#include "modules/setup.h"
#include "modules/auth.h"
#include "modules/home.h"
int main(){
    system("cls");
    DataCell setupState = get(DB_APP_STATE, KEY_SETUP);
    if(strcmp(setupState.value, PREFIX_DONE) == 0){
        //Setup done, continue to auth
        if(1){ //auth(1)
            printColoredBold(ANSI_COLOR_GREEN, "\nLogged in successfully!");
            sleep(1);
            home();
        }
        else {
            printColoredBold(ANSI_COLOR_RED, "Login failed! Exiting...");
            sleep(1);
            exit(0);
        }
    }
    else {
        //Need to setup first
        if(setup()){
            printBold("Setup done!");
            put(DB_APP_STATE, prepareInsert(KEY_SETUP, PREFIX_DONE));
        }
        else {
            printColoredBold(ANSI_COLOR_RED, "Setup failed!");
        }
        sleep(1);
        main();
    }
    return 0;
}