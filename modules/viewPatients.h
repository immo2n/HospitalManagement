#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER "┬╖"

void render()
{
    system("cls");
    printColoredBold(ANSI_COLOR_GREEN, "\t\t\t\tWELCOME TO HOSPITAL MANAGEMENT\n\n");
    printColored(ANSI_COLOR_CYAN, "\t\t\t\t        Patients List\n\n\n");

    // To show total patients
    DataCell totalPatients = get(DB_PATIENTS, KEY_TOTAL_PATIENTS);
    if (strcmp(totalPatients.value, PREFIX_NULL_STRING) == 0)
    {
        printColored(ANSI_COLOR_RED, "No patients found!");
    }
    else
    {
        printColored(ANSI_COLOR_YELLOW, "TOTAL PATIENTS: ");
        printColored(ANSI_COLOR_MAGENTA, totalPatients.value);
        printf("\n\n");
        DataCell *cells = getAsLines(DB_PATIENTS, atoi(totalPatients.value));
        printColoredBold(ANSI_COLOR_YELLOW, "Id\tName\tAge\tPhone Number\tAddress\tIllness\tDoctor\tDate\n");
        for (int i = 0; i < atoi(totalPatients.value); ++i) {
            char *line = strdup(cells[i].value);
            char *token;
            int column = 0;
            
            // Use strtok to split the line
            token = strtok(line, DELIMITER);
            while (token != NULL) {
                if (column > 0) {
                    printf("\t");
                }
                for(int j = 0; j < strlen(token); ++j) {
                    if (token[j] == DELIMITER) {
                        printf("\t");
                    } else {
                        printf("%c", token[j]);
                    }
                }
                token = strtok(NULL, DELIMITER);
                ++column;
            }
            printf("\n");
            free(line);
        }
    }
    printf("\n\n");
    // Go back button
    printColoredBold(ANSI_COLOR_RED, "\n[GO BACK] [PRESS ENTER]\n\n");
}

void viewPatients()
{
    system("cls");
    char input;
    do
    {
        render();
        input = getch();
        switch (input)
        {
        case '\r':
            return;
        }
    } while (1);
}