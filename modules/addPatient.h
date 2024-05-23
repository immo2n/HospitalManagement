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
        printColoredBold(ANSI_COLOR_RED, "\n[CANCEL] [PRESS ENTER]\n\n");
    else
        printColored(ANSI_COLOR_RED, "\n[CANCEL]\n\n");
}

void resetForm()
{
    strcpy(name, "");
    strcpy(age, "");
    strcpy(phone, "");
    strcpy(address, "");
    strcpy(illness, "");
    strcpy(doctorName, "");
    strcpy(date, "");
}

void addPatient()
{
    //Reset form values
    resetForm();
    int position = 1;
    int mainLooper = 1;
    char input;
    system("cls");
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
        case '\r': // Enter key
            if (position == FORM_OPTIONS)
            {
                //Cancel button
                mainLooper = 0;
                return;
            }
            else if(position == FORM_OPTIONS - 1){
                //Submit button
                DataCell totalPatients = get(DB_PATIENTS, KEY_TOTAL_PATIENTS);
                int total = 0;
                if(NULL != totalPatients.value){
                    total = atoi(totalPatients.value);
                }
                total++; // Increment the total patients
                sprintf(totalPatients.value, "%d", total); // just to reuse the char array
                char *patientData = (char *)malloc(500);
                sprintf(patientData, "%s·%s·%s·%s·%s·%s·%s", name, age, phone, address, illness, doctorName, date);
                put(DB_PATIENTS, prepareInsert(totalPatients.value, patientData));
                put(DB_PATIENTS, prepareInsert(KEY_TOTAL_PATIENTS, totalPatients.value));
                mainLooper = 0;
                printColoredBold(ANSI_COLOR_GREEN, "Patient added successfully!\n");
                sleep(1);
                return;
            }
            else
            {
                printColored(ANSI_COLOR_MAGENTA, "Enter new value: ");
                switch (position){
                    case 1:
                        gets(name);
                        break;
                    case 2:
                        gets(age);
                        break;
                    case 3:
                        gets(phone);
                        break;
                    case 4:
                        gets(address);
                        break;
                    case 5:
                        gets(illness);
                        break;
                    case 6:
                        gets(doctorName);
                        break;
                    case 7:
                        gets(date);
                        break;
                }
                position++;
                renderForm(position);
            }
        }
    } while (mainLooper);
}