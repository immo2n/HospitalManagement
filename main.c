#include <stdio.h>
#include "libs/util/fontStyles.h"
#include "libs/util/keySets.h"
#include "libs/database/database.h"
#include "modules/setup.h"
#include "modules/auth.h"
#include "modules/home.h"

#define MAIN_OPTIONS 5

void renderMain(int selected)
{
    system("cls");
    printColoredBold(ANSI_COLOR_GREEN, "\t\t\t\tWELCOME TO HOSPITAL MANAGEMENT\n\n");
    printColored(ANSI_COLOR_CYAN, "\t\t\t\t Select an option to continue\n\n\n");
    printf("\t\t\t         *** Patient's Options ***\n");
    (selected == 1) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t            => View doctors\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t            -> View doctors\n");
    (selected == 2) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t            => Search your record\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t            -> Search your record\n");
    printf("\t\t\t         *** Doctor's Options ***\n");
    (selected == 3) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t            => View appointments\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t            -> View appointments\n");
    printf("\t\t\t         *** Admin Options ***\n");
    (selected == 4) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t            => Login as Admin\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t            -> Login as Admin\n");
    (selected == 5) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t            => Exit App\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t            -> Exit App\n");
}

int main()
{
    DataCell setupState = get(DB_APP_STATE, KEY_SETUP);
    if (strcmp(setupState.value, PREFIX_DONE) == 0)
    {
        int selected = 1;
        int mainLooper = 1;
        char input;
        do
        {
            renderMain(selected);
            input = getch();
            switch (input)
            {
            case 'W':
            case 'w':
            case 72: // Up
                if (selected > 1)
                    selected--;
                else
                    selected = MAIN_OPTIONS;
                break;
            case 'S':
            case 's':
            case 80: // Down
                if (selected < MAIN_OPTIONS)
                    selected++;
                else
                    selected = 1;
                break;
            case 32:
            case '\r': // Enter key
                switch (selected)
                {
                case 1:
                    // View doctors
                    viewPatients(NULL);
                    break;
                case 2:
                    // Search patient with id
                    printColoredBold(ANSI_COLOR_GREEN, "Enter any details to search: ");
                    char key[100];
                    scanf("%s", key);
                    viewPatients(key);
                    break;
                case 3:
                    // Search patient with doctor
                    printColoredBold(ANSI_COLOR_GREEN, "Enter a doctor's name: ");
                    scanf("%s", key);
                    viewPatients(key);
                    break;
                case 4:
                    if (auth(1))
                    {
                        printColoredBold(ANSI_COLOR_GREEN, "\nLogged in successfully!");
                        sleep(1);
                        home();
                    }
                    else
                    {
                        printColoredBold(ANSI_COLOR_RED, "Login failed! Exiting...");
                        sleep(1);
                        renderMain(1);
                    }
                    break;
                case 5:
                    printColoredBold(ANSI_COLOR_GREEN, "Exiting...");
                    sleep(1);
                    system("cls");
                    mainLooper = 0;
                    break;
                }
            }
        } while (mainLooper);
    }
    else
    {
        // Need to setup first
        if (setup())
        {
            printBold("Setup done!");
            put(DB_APP_STATE, prepareInsert(KEY_SETUP, PREFIX_DONE));
        }
        else
        {
            printColoredBold(ANSI_COLOR_RED, "Setup failed!");
        }
        sleep(1);
        main();
    }
    return 0;
}