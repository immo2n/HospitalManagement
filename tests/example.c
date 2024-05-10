#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

struct Patient
{
    int patientID;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
    char address[100];
    char ailment[100];
    char doctorAssigned[50];
    int bedNumber;
};

struct Patient patients[MAX_PATIENTS];
int numPatients = 0;

// Function prototypes
void addPatient();
void displayPatient(int index);
void searchPatient(int patientID);
void editPatient(int patientID);
void deletePatient(int patientID);
void displayAllPatients();
void savePatientsToFile();
void loadPatientsFromFile();
int findEmptySlot();

int main()
{
    int choice, patientID;

    printf("\nHospital Management System\n");

    // Load data from file on startup (optional)
    loadPatientsFromFile();

    while (1)
    {
        printf("\n1. Add Patient\n");
        printf("2. Display Patient Details\n");
        printf("3. Search Patient\n");
        printf("4. Edit Patient Details\n");
        printf("5. Delete Patient\n");
        printf("6. Display All Patients\n");
        printf("7. Save Data to File\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            printf("Enter Patient ID: ");
            scanf("%d", &patientID);
            searchPatient(patientID);
            break;
        case 3:
            printf("Enter Patient ID: ");
            scanf("%d", &patientID);
            searchPatient(patientID);
            break;
        case 4:
            printf("Enter Patient ID to edit: ");
            scanf("%d", &patientID);
            editPatient(patientID);
            break;
        case 5:
            printf("Enter Patient ID to delete: ");
            scanf("%d", &patientID);
            deletePatient(patientID);
            break;
        case 6:
            displayAllPatients();
            break;
        case 7:
            savePatientsToFile();
            break;
        case 8:
            printf("Exiting...\n");
            savePatientsToFile(); // Save data before exit (optional)
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

// Function to add a new patient
void addPatient()
{
    int slot = findEmptySlot();
    if (slot == -1)
    {
        printf("Hospital is full!\n");
        return;
    }

    printf("Enter Patient Details:\n");
    printf("Patient ID: ");
    scanf("%d", &patients[slot].patientID);
    printf("Name: ");
    scanf(" %[^\n]", patients[slot].name); // Read name with spaces
    printf("Age: ");
    scanf("%d", &patients[slot].age);
    printf("Gender (M/F): ");
    scanf(" %[^\n]", patients[slot].gender);
    printf("Phone Number: ");
    scanf(" %[^\n]", patients[slot].phone);
    printf("Address: ");
    scanf(" %[^\n]", patients[slot].address);
    printf("Ailment: ");
    scanf(" %[^\n]", patients[slot].ailment);
    printf("Doctor Assigned (if any): ");
    scanf(" %[^\n]", patients[slot].doctorAssigned);
    printf("Bed Number (if assigned): ");
    scanf("%d", &patients[slot].bedNumber);

    numPatients++;
    printf("Patient added successfully!\n");
}

// Function to display patient details
void displayPatient(int index)
{
    if (index < 0 || index >= numPatients)
    {
        printf("Invalid patient ID!\n");
        return;
    }

    printf("\nPatient Details:\n");
    printf("Patient ID: %d\n", patients[index].patientID);
    printf("Name: %s\n", patients[index].name);
    printf("Age: %d\n", patients[index].age);
    printf("Gender: %s\n", patients[index].gender);
    printf("Phone Number: %s\n", patients[index].phone);
    printf("Address: %s\n", patients[index].address);
    printf("Ailment: %s\n", patients[index].ailment);
    printf("Doctor Assigned: %s\n", patients[index].doctorAssigned);
    printf("Bed Number: %d\n", patients[index].bedNumber);
}

// Function to search for a patient by ID
void searchPatient(int patientID)
{
    int found = 0;
    for (int i = 0; i < numPatients; i++)
    {
        if (patients[i].patientID == patientID)
        {
            displayPatient(i);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Patient with ID %d not found!\n", patientID);
    }
}

// Function to edit patient details
void editPatient(int patientID)
{
    int index = -1;
    for (int i = 0; i < numPatients; i++)
    {
        if (patients[i].patientID == patientID)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Patient with ID %d not found!\n", patientID);
        return;
    }

    int choice;
    printf("\nEdit Patient Details:\n");
    printf("1. Edit Name\n");
    printf("2. Edit Age\n");
    printf("3. Edit Gender\n");
    printf("4. Edit Phone Number\n");
    printf("5. Edit Address\n");
    printf("6. Edit Ailment\n");
    printf("7. Edit Doctor Assigned\n");
    printf("8. Edit Bed Number\n");
    printf("9. Cancel\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("Enter new name: ");
        scanf(" %[^\n]", patients[index].name);
        break;
    case 2:
        printf("Enter new age: ");
        scanf("%d", &patients[index].age);
        break;
    case 3:
        printf("Enter new gender (M/F): ");
        scanf(" %[^\n]", patients[index].gender);
        break;
    case 4:
        printf("Enter new phone number: ");
        scanf(" %[^\n]", patients[index].phone);
        break;
    case 5:
        printf("Enter new address: ");
        scanf(" %[^\n]", patients[index].address);
        break;
    case 6:
        printf("Enter new ailment: ");
        scanf(" %[^\n]", patients[index].ailment);
        break;
    case 7:
        printf("Enter new doctor assigned (if any): ");
        scanf(" %[^\n]", patients[index].doctorAssigned);
        break;
    case 8:
        printf("Enter new bed number (if assigned): ");
        scanf("%d", &patients[index].bedNumber);
        break;
    case 9:
        printf("Edit cancelled.\n");
        break;
    default:
        printf("Invalid choice!\n");
    }

    printf("Patient details edited successfully!\n");
}

// Function to delete a patient
void deletePatient(int patientID)
{
    int index = -1;
    for (int i = 0; i < numPatients; i++)
    {
        if (patients[i].patientID == patientID)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Patient with ID %d not found!\n", patientID);
        return;
    }

    // Shift elements to remove the deleted patient
    for (int i = index; i < numPatients - 1; i++)
    {
        patients[i] = patients[i + 1];
    }
    numPatients--;
    printf("Patient deleted successfully!\n");
}

// Function to display all patients
void displayAllPatients()
{
    if (numPatients == 0)
    {
        printf("No patients found!\n");
        return;
    }

    printf("\nList of All Patients:\n");
    for (int i = 0; i < numPatients; i++)
    {
        displayPatient(i);
        printf("\n");
    }
}

// Function to save patients' data to a file
void savePatientsToFile()
{
    FILE *fp = fopen("patients.dat", "wb"); // Open in binary write mode

    if (fp == NULL)
    {
        printf("Error opening file for writing!\n");
        return;
    }

    fwrite(patients, sizeof(struct Patient), numPatients, fp); // Write data

    if (ferror(fp))
    {
        printf("Error writing data to file!\n");
    }
    else
    {
        printf("Patients' data saved successfully!\n");
    }

    fclose(fp);
}

// Function to load patients' data from a file
void loadPatientsFromFile()
{
    FILE *fp = fopen("patients.dat", "rb"); // Open in binary read mode

    if (fp == NULL)
    {
        printf("Error opening file for reading (assuming no existing data).\n");
        return;
    }

    numPatients = fread(patients, sizeof(struct Patient), 100, fp); // Read data

    if (ferror(fp))
    {
        printf("Error reading data from file!\n");
    }

    fclose(fp);
}

// Function to find an empty slot in the patients array
int findEmptySlot()
{
    for (int i = 0; i < MAX_PATIENTS; i++)
    {
        if (patients[i].patientID == 0)
        {
            return i;
        }
    }
    return -1; // No empty slot found
}
