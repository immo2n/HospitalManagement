#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER "·"

void printSeparator(int columnCount, int *columnWidths)
{
    printf("+");
    for (int i = 0; i < columnCount; ++i)
    {
        for (int j = 0; j < columnWidths[i] + 2; ++j)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}

void printRow(char **columns, int columnCount, int *columnWidths)
{
    printf("|");
    for (int i = 0; i < columnCount; ++i)
    {
        printf(" %-*s |", columnWidths[i], columns[i]);
    }
    printf("\n");
}

void render(char *searchKey)
{
    system("cls");
    printColoredBold(ANSI_COLOR_GREEN, "\t\t\t\tWELCOME TO HOSPITAL MANAGEMENT\n\n");

    if (searchKey == NULL)
        printColored(ANSI_COLOR_CYAN, "\t\t\t\t        Patients List\n\n\n");
    else
        printColored(ANSI_COLOR_CYAN, "\t\t\t\t        Search patients\n\n\n");

    // To show total patients
    DataCell totalPatients = get(DB_PATIENTS, KEY_TOTAL_PATIENTS);
    if (strcmp(totalPatients.value, PREFIX_NULL_STRING) == 0)
    {
        printColored(ANSI_COLOR_RED, "No patients data stored!");
    }
    else
    {
        printColored(ANSI_COLOR_YELLOW, "TOTAL PATIENTS: ");
        printColored(ANSI_COLOR_MAGENTA, totalPatients.value);
        if(searchKey != NULL){
            printColoredBold(ANSI_COLOR_YELLOW, "\nSEARCHING FOR: ");
            printColored(ANSI_COLOR_MAGENTA, searchKey);
        }
        printf("\n\n");
        
        DataCell *cells = getAsLines(DB_PATIENTS, atoi(totalPatients.value));

        char *headers[] = {"Id", "Name", "Age", "Phone Number", "Address", "Illness", "Doctor", "Date"};
        int columnCount = sizeof(headers) / sizeof(headers[0]);

        int columnWidths[columnCount];
        for (int i = 0; i < columnCount; ++i)
        {
            columnWidths[i] = strlen(headers[i]);
        }

        for (int i = 0; i < atoi(totalPatients.value); ++i)
        {
            char *line = strdup(cells[i].value);

            // For search mode
            if (searchKey != NULL && strstr(line, searchKey) == NULL){
                free(line);
                continue;
            }

            char *token;
            int column = 0;
            token = strtok(line, DELIMITER);
            while (token != NULL)
            {
                int tokenLength = strlen(token);
                if (tokenLength > columnWidths[column + 1])
                {
                    columnWidths[column + 1] = tokenLength;
                }
                token = strtok(NULL, DELIMITER);
                ++column;
            }
            free(line);
        }

        printSeparator(columnCount, columnWidths);
        printRow(headers, columnCount, columnWidths);
        printSeparator(columnCount, columnWidths);

        int counter = 0;

        for (int i = 0; i < atoi(totalPatients.value); ++i)
        {
            char *line = strdup(cells[i].value);

            // For search mode
            if (searchKey != NULL && strstr(line, searchKey) == NULL){
                free(line);
                continue;
            }

            char *token;
            int column = 0;

            char *columns[columnCount];
            columns[0] = cells[i].key;

            token = strtok(line, DELIMITER);
            while (token != NULL)
            {
                columns[column + 1] = token;
                token = strtok(NULL, DELIMITER);
                ++column;
            }
            printf("| ");
            printColored(ANSI_COLOR_GREEN, cells[i].key);
            printf(" ");
            for (int j = 1; j < columnCount; ++j)
            {
                printf("| %-*s ", columnWidths[j], columns[j]);
            }
            printf("|\n");

            free(line);
            ++counter;
        }

        if(counter == 0){
            printColored(ANSI_COLOR_RED, "No patients found!\n");
        }

        printSeparator(columnCount, columnWidths);
    }
    printf("\n\n");

    // Go back button
    printColoredBold(ANSI_COLOR_RED, "\n[GO BACK] [PRESS ENTER]\n\n");
}

void viewPatients(char *searchKey)
{
    system("cls");
    render(searchKey);
    char input;
    do
    {
        input = getch();
        switch (input)
        {
        case '\r':
            return;
        }
    } while (1);
}