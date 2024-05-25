#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

#include "addPatient.h"
#include "viewPatients.h"

#define MAIN_MENU_OPTIONS 6

void renderOptions(int selected)
{
    system("cls");
    printColoredBold(ANSI_COLOR_GREEN, "\t\t\t\tWELCOME TO HOSPITAL MANAGEMENT\n\n");
    printColored(ANSI_COLOR_CYAN, "\t\t\t\t      Main Menu (Employee)\n\n\n");

    (selected == 1) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => Add Patient\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> Add Patient\n");
    (selected == 2) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => View Patients\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> View Patients\n");
    (selected == 3) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => Search Patient\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> Search Patient\n");
    (selected == 4) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => Update Patient\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> Update Patient\n");
    (selected == 5) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => Delete Patient\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> Delete Patient\n");
    (selected == 6) ? printColoredBold(ANSI_COLOR_YELLOW, "\t\t\t             => Logout\n") : printColored(ANSI_COLOR_MAGENTA, "\t\t\t             -> Logout\n");
}

void home()
{
    int selected = 1;
    int mainLooper = 1;
    char input;
    do
    {
        renderOptions(selected);
        input = getch();
        switch (input)
        {
        case 'W':
        case 'w':
        case 72: // Up
            if (selected > 1)
                selected--;
            else
                selected = MAIN_MENU_OPTIONS;
            break;
        case 'S':
        case 's':
        case 80: // Down
            if (selected < MAIN_MENU_OPTIONS)
                selected++;
            else
                selected = 1;
            break;
        case 32:
        case '\r': // Enter key
            switch (selected)
            {
            case 1:
                // Add patient
                addPatient(NULL);
                break;
            case 2:
                viewPatients(NULL);
                break;
            case 3:
                printColoredBold(ANSI_COLOR_GREEN, "Enter any details to search: ");
                char key[100];
                scanf("%s", key);
                viewPatients(key);
                break;
            case 4:
                printColoredBold(ANSI_COLOR_GREEN, "Enter patient ID to update: ");
                char id[11];
                scanf("%s", id);
                // Get the patient details
                DataCell patient = get(DB_PATIENTS, id);
                if (strcmp(patient.value, PREFIX_NULL_STRING) == 0)
                {
                    printColoredBold(ANSI_COLOR_RED, "Patient not found!");
                    sleep(1);
                    renderOptions(selected);
                }
                else
                {
                    addPatient(&patient);
                }
                break;
            case 5:
                printColoredBold(ANSI_COLOR_GREEN, "Enter patient ID to delete: ");
                char idToDelete[11];
                scanf("%s", idToDelete);
                // Get the patient details
                DataCell patientToDelete = get(DB_PATIENTS, idToDelete);
                if (strcmp(patientToDelete.value, PREFIX_NULL_STRING) == 0)
                {
                    printColoredBold(ANSI_COLOR_RED, "Patient not found!");
                    sleep(1);
                    renderOptions(selected);
                }
                else
                {
                    if (!pop(DB_PATIENTS, idToDelete))
                    {
                        printColoredBold(ANSI_COLOR_RED, "Failed to delete patient!");
                        sleep(1);
                    }
                    else
                    {
                        printColoredBold(ANSI_COLOR_GREEN, "Patient deleted successfully!");
                        DataCell totalPatients = get(DB_PATIENTS, KEY_TOTAL_PATIENTS);
                        int total = 0;
                        if (NULL != totalPatients.value)
                        {
                            total = atoi(totalPatients.value);
                        }
                        total--;
                        sprintf(totalPatients.value, "%d", total);
                        put(DB_PATIENTS, prepareInsert(KEY_TOTAL_PATIENTS, totalPatients.value));
                        sleep(1);
                    }
                    renderOptions(selected);
                }
                break;
            case 6:
                // Exit
                printColoredBold(ANSI_COLOR_RED, "\nLogged out!");
                sleep(1);
                system("cls");
                mainLooper = 0;
                break;
            }
        }
    } while (mainLooper);
}