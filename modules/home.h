#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

#define MAIN_MENU_OPTIONS 6

void renderOptions(int selected){
    system("cls");
    printColoredBold(ANSI_COLOR_GREEN, "\t\t\t\tWELCOME TO HOSPITAL MANAGEMENT\n\n");
    printColored(ANSI_COLOR_CYAN, "\t\t\t\t\t  Main Menu\n\n\n");

    (selected == 1) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => Add Patient\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> Add Patient\n");
    (selected == 2) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => View Patients\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> View Patients\n");
    (selected == 3) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => Search Patient\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> Search Patient\n");
    (selected == 4) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => Update Patient\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> Update Patient\n");
    (selected == 5) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => Delete Patient\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> Delete Patient\n");
    (selected == 6) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => Logout\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> Logout\n");
}

void home(){
    int selected = 1;
    int mainLooper = 1;
    char input;
    do {
        renderOptions(selected);
        input = getch();
        switch (input) {
            case 72: //Up
                if (selected > 1) selected--;
                else selected = 6;
                break;
            case 80: //Down
                if (selected < MAIN_MENU_OPTIONS) selected++;
                else selected = 1;
                break;
            case '\r': //Enter key
                switch (selected) {
                    case 6:
                    //Exit
                    printColoredBold(ANSI_COLOR_RED, "\nLogged out!");
                    sleep(1);
                    system("cls");
                    mainLooper = 0;
                    break;
                }
        }
    }
    while(mainLooper);
}