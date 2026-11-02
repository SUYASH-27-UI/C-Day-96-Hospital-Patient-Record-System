#include <stdio.h>

#define MAX 100

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

struct Patient patients[MAX];
int count = 0;

int findPatient(int id) {
    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            return i;
        }
    }

    return -1;
}

void loadPatients() {
    FILE *file = fopen("patients.txt", "r");

    if (file == NULL) {
        return;
    }

    while (count < MAX &&
           fscanf(file, "%d %49s %d %49s",
                  &patients[count].id,
                  patients[count].name,
                  &patients[count].age,
                  patients[count].disease) == 4) {
        count++;
    }

    fclose(file);
}

void savePatients() {
    FILE *file = fopen("patients.txt", "w");

    if (file == NULL) {
        printf("Error saving records!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %d %s\n",
                patients[i].id,
                patients[i].name,
                patients[i].age,
                patients[i].disease);
    }

    fclose(file);
}

void addPatient() {
    if (count >= MAX) {
        printf("Patient limit reached!\n");
        return;
    }

    struct Patient p;

    printf("Enter Patient ID: ");
    if (scanf("%d", &p.id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    if (findPatient(p.id) != -1) {
        printf("Patient ID already exists!\n");
        return;
    }

    printf("Enter Patient Name (one word): ");
    scanf("%49s", p.name);

    printf("Enter Age: ");
    if (scanf("%d", &p.age) != 1 || p.age < 0) {
        printf("Invalid age!\n");
        return;
    }

    printf("Enter Disease (one word): ");
    scanf("%49s", p.disease);

    patients[count] = p;
    count++;

    savePatients();

    printf("Patient record added successfully!\n");
}

void displayPatients() {
    if (count == 0) {
        printf("No patient records available.\n");
        return;
    }

    printf("\n--- Patient Records ---\n");

    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Age: %d | Disease: %s\n",
               patients[i].id,
               patients[i].name,
               patients[i].age,
               patients[i].disease);
    }
}

void searchPatient() {
    int id;

    printf("Enter Patient ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    int index = findPatient(id);

    if (index == -1) {
        printf("Patient not found!\n");
    } else {
        printf("\nPatient Found!\n");
        printf("Name: %s\n", patients[index].name);
        printf("Age: %d\n", patients[index].age);
        printf("Disease: %s\n", patients[index].disease);
    }
}

void updatePatient() {
    int id;

    printf("Enter Patient ID to update: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    int index = findPatient(id);

    if (index == -1) {
        printf("Patient not found!\n");
        return;
    }

    printf("Enter New Name: ");
    scanf("%49s", patients[index].name);

    printf("Enter New Age: ");

    if (scanf("%d", &patients[index].age) != 1 ||
        patients[index].age < 0) {
        printf("Invalid age!\n");
        return;
    }

    printf("Enter New Disease: ");
    scanf("%49s", patients[index].disease);

    savePatients();

    printf("Patient record updated!\n");
}

void deletePatient() {
    int id;

    printf("Enter Patient ID to delete: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    int index = findPatient(id);

    if (index == -1) {
        printf("Patient not found!\n");
        return;
    }

    for (int i = index; i < count - 1; i++) {
        patients[i] = patients[i + 1];
    }

    count--;

    savePatients();

    printf("Patient record deleted!\n");
}

int main() {
    int choice;

    loadPatients();

    while (1) {
        printf("\n===== HOSPITAL MANAGEMENT =====\n");
        printf("1. Add Patient\n");
        printf("2. Display Patients\n");
        printf("3. Search Patient\n");
        printf("4. Update Patient\n");
        printf("5. Delete Patient\n");
        printf("6. Exit\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addPatient();
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 4:
                updatePatient();
                break;

            case 5:
                deletePatient();
                break;

            case 6:
                printf("Program closed.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
