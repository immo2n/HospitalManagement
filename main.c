#include <stdio.h>
#include "libs/util/fontStyles.h"
#include "libs/database/database.h"
#include "libs/util/keySets.h"
#include "modules/setup.h"
#include "modules/auth.h"

int main(){
    system("cls");
    DataCell setupState = get(DB_APP_STATE, KEY_SETUP);
    if(strcmp(setupState.value, PREFIX_DONE) == 0){
        //Setup done, continue to auth
        if(auth()){
            printColoredBold(ANSI_COLOR_GREEN, "Logged in successfully!");
            sleep(1);
        }
        else {
            printColoredBold(ANSI_COLOR_RED, "Login failed!");
            sleep(1);
            main();
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