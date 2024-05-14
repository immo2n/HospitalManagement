#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FORM_OPTIONS 9

char name[50];
char age[5];
char phone[18];
char address[150];
char illness[200];
char doctorName[50];
char date[50];

void renderForm(int position)
{
    system("cls");
    printColoredBold(ANSI_COLOR_GREEN, "\t\t\t\tWELCOME TO HOSPITAL MANAGEMENT\n\n");
    printColored(ANSI_COLOR_CYAN, "\t\t\t\t        Add Patient\n\n\n");

    printColoredBold(ANSI_COLOR_YELLOW, "1. PATIENT NAME: ");
    if (position == 1)
        printf("[PRESS ENTER TO EDIT]\n");
    else
        printf("%s\n", name);

    printColoredBold(ANSI_COLOR_YELLOW, "2. PATIENT AGE: ");
    if (position == 2)
        printf("[PRESS ENTER TO EDIT]\n");
    else
        printf("%s\n", age);

    printColoredBold(ANSI_COLOR_YELLOW, "3. PHONE NUMBER: ");
    if (position == 3)
        printf("[PRESS ENTER TO EDIT]\n");
    else
        printf("%s\n", phone);

    printColoredBold(ANSI_COLOR_YELLOW, "4. ADDRESS: ");
    if (position == 4)
        printf("[PRESS ENTER TO EDIT]\n");
    else
        printf("%s\n", address);

    printColoredBold(ANSI_COLOR_YELLOW, "5. ILLNESS: ");
    if (position == 5)
        printf("[PRESS ENTER TO EDIT]\n");
    else
        printf("%s\n", illness);

    printColoredBold(ANSI_COLOR_YELLOW, "6. DOCTOR NAME: ");
    if (position == 6)
        printf("[PRESS ENTER TO EDIT]\n");
    else
        printf("%s\n", doctorName);

    printColoredBold(ANSI_COLOR_YELLOW, "7. DATE: ");
    if (position == 7)
        printf("[PRESS ENTER TO EDIT]\n");
    else
        printf("%s\n", date);

    if(position ==  8)
        printColoredBold(ANSI_COLOR_GREEN, "\n[SUBMIT FORM] [PRESS ENTER]");
    else
        printColored(ANSI_COLOR_GREEN, "\n[SUBMIT FORM]");

    if(position ==  FORM_OPTIONS)
        printColoredBold(ANSI_COLOR_RED, "\n[CANCEL] [PRESS ENTER]\n");
    else
        printColored(ANSI_COLOR_RED, "\n[CANCEL]\n");
}

void addPatient()
{
    system("cls");
    int position = 1;
    int mainLooper = 1;
    char input;
    do
    {
        renderForm(position);
        input = getch();
        switch (input)
        {
        case 'W':
        case 'w':
        case 72: // Up
            if (position > 1)
                position--;
            else
                position = FORM_OPTIONS;
            break;
        case 'S':
        case 's':
        case 80: // Down
            if (position < FORM_OPTIONS)
                position++;
            else
                position = 1;
            break;
        case 32:
        case '\r': // Enter key
            if (position == FORM_OPTIONS)
            {
                //Cancel button
                mainLooper = 0;
                return;
            }
            else if(position == FORM_OPTIONS - 1){
                //Submit button
            }
            else
            {
                if(position < FORM_OPTIONS){
                    printColored(ANSI_COLOR_MAGENTA, "\n\nEnter new value: ");
                }
                switch (position){
                    case 1:
                        scanf("%s", name);
                        break;
                    case 2:
                        scanf("%s", age);
                        break;
                    case 3:
                        scanf("%s", phone);
                        break;
                    case 4:
                        scanf("%s", address);
                        break;
                    case 5:
                        scanf("%s", illness);
                        break;
                    case 6:
                        scanf("%s", doctorName);
                        break;
                    case 7:
                        scanf("%s", date);
                        break;
                    default:
                        break;
                }
                // Just go to the next one to bottom only
                if (position < FORM_OPTIONS)
                {
                    position++;
                    renderForm(position);
                }
            }
        }
    } while (mainLooper);
}