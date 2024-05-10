#include <stdio.h>
#include "libs/util/fontStyles.h"
#include "libs/database/database.h"
#include "modules/setup.h"
#include "modules/auth.h"

int main(){
    system("cls");
    if(!openConnection()){
        printf("FATAL ERROR: Could not open database!\n");
        return 0;
    }
    //Databases initiate
    Database appState = openDocument("AppState");
    char *state = fetch(&appState, "setup").value;

    
    //char *username = fetch(&appState, "admin_username").value;
    //char *password = fetch(&appState, "admin_password").value;

    if(strcmp(state, "done") == 0){
        //Auth module
        int done = auth(&appState);
        if(done){
            printColoredBold(ANSI_COLOR_GREEN, "Login successfully!");
            printBold("Main homepage will be here!");
        }
    }
    else {
        int done = setup(&appState);
        if(done){
            printBold("Setup done!");
            insert(&appState, prepareInsert("setup", "done"));
        }
        else {
            printColoredBold(ANSI_COLOR_RED, "Setup failed!");
        }
        //Restart page
        sleep(1);
        closeConnection();
        main();
    }
    closeConnection();
    return 0;
}