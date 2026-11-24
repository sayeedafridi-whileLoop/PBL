
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int id;
    char name[50];
    float fees;
    char course[20];
    char grade[20];
};

void addStudent();
void displayStudents();
void searchStudent();
void updateFees();
void allocateCourse();
void enterResult();
void displayResults();

int main()
{
    int choice;
    char userid[20], password[20];

    printf("=================================\n");
    printf("   STUDENT MANAGEMENT SYSTEM\n");
    printf("=================================\n");

    // Authentication
    printf("Enter User ID: ");
    scanf("%19s", userid);

    printf("Enter Password: ");
    scanf("%19s", password);

    if (strcmp(userid, "admin") != 0 ||
        strcmp(password, "12345") != 0)
    {
        printf("Invalid User ID or Password!\n");
        return 0;
    }

    printf("\nLogin Successful!\n");

    do
    {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Fees\n");
        printf("5. Allocate Course\n");
        printf("6. Enter Result\n");
        printf("7. Display Results\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateFees();
                break;

            case 5:
                allocateCourse();
                break;

            case 6:
                enterResult();
                break;

            case 7:
                displayResults();
                break;

            case 8:
                printf("Thank you for using the system!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 8);

    return 0;
}

// Add Student
void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("student.dat", "ab");

    if(fp == NULL)
    {
        printf("File opening error!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter Fees Paid: ");
    scanf("%f", &s.fees);

    strcpy(s.course, "Not Allocated");
    strcpy(s.grade, "Pending");

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("Student Added Successfully!\n");
}

// Display Students
void displayStudents()
{
    FILE *fp;
    struct Student s;

    fp = fopen("student.dat", "rb");

    if(fp == NULL)
    {
        printf("No student records found!\n");
        return;
    }

    printf("\nID\tName\t\tFees\tCourse\tGrade\n");

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("%d\t%-15s\t%.2f\t%s\t%s\n",
        s.id, s.name, s.fees, s.course, s.grade);
    }

    fclose(fp);
}

// Search Student
void searchStudent()
{
    FILE *fp;
    struct Student s;
    int id, found = 0;

    printf("Enter Student ID: ");
    scanf("%d", &id);

    fp = fopen("student.dat", "rb");

    if(fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.id == id)
        {
            printf("\nStudent Found!\n");
            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.name);
            printf("Fees: %.2f\n", s.fees);
            printf("Course: %s\n", s.course);
            printf("Grade: %s\n", s.grade);

            found = 1;
            break;
        }
    }

    if(!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

// Update Fees
void updateFees()
{
    FILE *fp;
    struct Student s;
    int id, found = 0;
    float fees;

    fp = fopen("student.dat", "rb+");

    if(fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.id == id)
        {
            printf("Enter Updated Fees: ");
            scanf("%f", &fees);

            s.fees = fees;

            fseek(fp, -(long)sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            printf("Fees Updated Successfully!\n");
            break;
        }
    }

    if(!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

// Allocate Course
void allocateCourse()
{
    FILE *fp;
    struct Student s;
    int id, found = 0, choice;

    fp = fopen("student.dat", "rb+");

    if(fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.id == id)
        {
            found = 1;

            if(s.fees <= 0)
            {
                printf("Fees not paid. Course cannot be allocated!\n");
                break;
            }

            printf("\nSelect Course:\n");
            printf("1. DS\n");
            printf("2. AI\n");
            printf("3. ML\n");
            printf("4. Web\n");

            printf("Enter Choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
                case 1:
                    strcpy(s.course, "DS");
                    break;

                case 2:
                    strcpy(s.course, "AI");
                    break;

                case 3:
                    strcpy(s.course, "ML");
                    break;

                case 4:
                    strcpy(s.course, "Web");
                    break;

                default:
                    printf("Invalid Course!\n");
                    break;
            }

            if(choice >= 1 && choice <= 4)
            {
                fseek(fp, -(long)sizeof(s), SEEK_CUR);
                fwrite(&s, sizeof(s), 1, fp);
                printf("Course Allocated Successfully!\n");
            }

            break;
        }
    }

    if(!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

// Enter Result
void enterResult()
{
    FILE *fp;
    struct Student s;
    int id, choice, found = 0;

    fp = fopen("student.dat", "rb+");

    if(fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.id == id)
        {
            found = 1;

            if(strcmp(s.course, "Not Allocated") == 0)
            {
                printf("Course not allocated yet!\n");
                break;
            }

            printf("\nSelect Grade:\n");
            printf("1. Excellent\n");
            printf("2. Good\n");
            printf("3. Fail\n");

            printf("Enter Choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
                case 1:
                    strcpy(s.grade, "Excellent");
                    break;

                case 2:
                    strcpy(s.grade, "Good");
                    break;

                case 3:
                    strcpy(s.grade, "Fail");
                    break;

                default:
                    printf("Invalid Grade!\n");
                    break;
            }

            if(choice >= 1 && choice <= 3)
            {
                fseek(fp, -(long)sizeof(s), SEEK_CUR);
                fwrite(&s, sizeof(s), 1, fp);
                printf("Result Updated Successfully!\n");
            }

            break;
        }
    }

    if(!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

// Display Results
void displayResults()
{
    FILE *fp;
    struct Student s;

    fp = fopen("student.dat", "rb");

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("\nID\tName\t\tCourse\tGrade\n");

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("%d\t%-15s\t%s\t%s\n",
        s.id, s.name, s.course, s.grade);
    }

    fclose(fp);
}

