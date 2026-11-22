
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[100];
    int age;
    float marks;
};

void createFile();
void insertRecords();
void displayRecords();
void searchRecord();
void appendRecords();
void updateRecord();
void deleteRecord();
void countRecords();
void copyFile();
void printStudent(struct Student s);
void clearInput();

int main() {
    int choice;

    do {
        printf("\n===== STUDENT RECORD MANAGEMENT SYSTEM =====\n");
        printf("1. Create File\n");
        printf("2. Insert Records\n");
        printf("3. Display Records\n");
        printf("4. Search Record\n");
        printf("5. Append Records\n");
        printf("6. Update Record\n");
        printf("7. Delete Record\n");
        printf("8. Count Records\n");
        printf("9. Copy File\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInput();

        switch (choice) {
            case 1: createFile(); break;
            case 2: insertRecords(); break;
            case 3: displayRecords(); break;
            case 4: searchRecord(); break;
            case 5: appendRecords(); break;
            case 6: updateRecord(); break;
            case 7: deleteRecord(); break;
            case 8: countRecords(); break;
            case 9: copyFile(); break;
            case 10: printf("Exiting program.\n"); break;
            default: printf("Invalid choice.\n");
        }

    } while (choice != 10);

    return 0;
}

void clearInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void printStudent(struct Student s) {
    printf("\nRoll Number : %d", s.roll);
    printf("\nName        : %s", s.name);
    printf("\nAge         : %d", s.age);
    printf("\nMarks       : %.2f\n", s.marks);
}

void createFile() {
    FILE *fp = fopen("students.txt", "w");

    if (fp == NULL) {
        printf("File creation failed.\n");
        return;
    }

    fputs("", fp);
    fclose(fp);

    printf("File created successfully.\n");
}

void insertRecords() {
    FILE *fp = fopen("students.txt", "a");
    struct Student s;
    int n, i;

    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    printf("Enter number of students: ");
    scanf("%d", &n);
    clearInput();

    for (i = 0; i < n; i++) {
        printf("\nEnter roll number: ");
        scanf("%d", &s.roll);
        clearInput();

        printf("Enter name: ");
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = '\0';

        printf("Enter age: ");
        scanf("%d", &s.age);

        printf("Enter marks: ");
        scanf("%f", &s.marks);
        clearInput();

        fprintf(fp, "%d|%s|%d|%.2f\n",
                s.roll, s.name, s.age, s.marks);
    }

    fclose(fp);
    printf("Records inserted successfully.\n");
}

void displayRecords() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;

    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("\n===== STUDENT RECORDS =====\n");

    while (fscanf(fp, "%d|%99[^|]|%d|%f",
                  &s.roll, s.name, &s.age, &s.marks) == 4) {
        printStudent(s);
    }

    if (ferror(fp))
        printf("Error reading file.\n");

    fclose(fp);
}

void searchRecord() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &roll);
    clearInput();

    rewind(fp);

    while (fscanf(fp, "%d|%99[^|]|%d|%f",
                  &s.roll, s.name, &s.age, &s.marks) == 4) {
        if (s.roll == roll) {
            printStudent(s);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student record not found.\n");

    fclose(fp);
}

void appendRecords() {
    FILE *fp = fopen("students.txt", "a+");
    struct Student s;
    int n, i;
    long position;

    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    position = ftell(fp);

    printf("Current file size: %ld bytes\n", position);
    printf("Enter number of records to append: ");
    scanf("%d", &n);
    clearInput();

    for (i = 0; i < n; i++) {
        printf("\nEnter roll number: ");
        scanf("%d", &s.roll);
        clearInput();

        printf("Enter name: ");
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = '\0';

        printf("Enter age: ");
        scanf("%d", &s.age);

        printf("Enter marks: ");
        scanf("%f", &s.marks);
        clearInput();

        fprintf(fp, "%d|%s|%d|%.2f\n",
                s.roll, s.name, s.age, s.marks);
    }

    fclose(fp);
    printf("Records appended successfully.\n");
}

void updateRecord() {
    FILE *fp = fopen("students.txt", "r+");
    FILE *temp = fopen("temp.txt", "w+");
    struct Student s;
    int roll, found = 0;

    if (fp == NULL || temp == NULL) {
        printf("Unable to open files.\n");
        if (fp != NULL) fclose(fp);
        if (temp != NULL) fclose(temp);
        return;
    }

    printf("Enter roll number to update: ");
    scanf("%d", &roll);
    clearInput();

    rewind(fp);

    while (fscanf(fp, "%d|%99[^|]|%d|%f",
                  &s.roll, s.name, &s.age, &s.marks) == 4) {

        if (s.roll == roll) {
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
            clearInput();
            found = 1;
        }

        fprintf(temp, "%d|%s|%d|%.2f\n",
                s.roll, s.name, s.age, s.marks);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        if (remove("students.txt") == 0 &&
            rename("temp.txt", "students.txt") == 0)
            printf("Record updated successfully.\n");
        else
            printf("Error replacing original file.\n");
    } else {
        remove("temp.txt");
        printf("Student record not found.\n");
    }
}

void deleteRecord() {
    FILE *fp = fopen("students.txt", "r+");
    FILE *temp = fopen("temp.txt", "w+");
    struct Student s;
    int roll, found = 0;

    if (fp == NULL || temp == NULL) {
        printf("Unable to open files.\n");
        if (fp != NULL) fclose(fp);
        if (temp != NULL) fclose(temp);
        return;
    }

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);
    clearInput();

    rewind(fp);

    while (fscanf(fp, "%d|%99[^|]|%d|%f",
                  &s.roll, s.name, &s.age, &s.marks) == 4) {

        if (s.roll == roll) {
            found = 1;
            continue;
        }

        fprintf(temp, "%d|%s|%d|%.2f\n",
                s.roll, s.name, s.age, s.marks);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        if (remove("students.txt") == 0 &&
            rename("temp.txt", "students.txt") == 0)
            printf("Record deleted successfully.\n");
        else
            printf("Error replacing original file.\n");
    } else {
        remove("temp.txt");
        printf("Student record not found.\n");
    }
}

void countRecords() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;
    int count = 0;

    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    rewind(fp);

    while (fscanf(fp, "%d|%99[^|]|%d|%f",
                  &s.roll, s.name, &s.age, &s.marks) == 4) {
        count++;
    }

    if (ferror(fp))
        printf("Error reading file.\n");
    else if (feof(fp))
        printf("End of file reached.\n");

    printf("Total number of records: %d\n", count);

    fclose(fp);
}

void copyFile() {
    FILE *source = fopen("students.txt", "r");
    FILE *destination = fopen("backup.txt", "w");
    int ch;

    if (source == NULL || destination == NULL) {
        printf("Unable to open files.\n");
        if (source != NULL) fclose(source);
        if (destination != NULL) fclose(destination);
        return;
    }

    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
    }

    if (ferror(source) || ferror(destination))
        printf("Error copying file.\n");
    else
        printf("File copied successfully to backup.txt.\n");

    fclose(source);
    fclose(destination);
}
