#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SPACE 50
#define MAX 50

void insert();
void update();
void search();
void print();
void filter();
void compare();
void reset();
void restore(FILE *ptr, FILE *ptr1, FILE *ptr2);

struct info
{
    char *name;
    int age;
    float compatability;
} information[SPACE];

int space = 0;
char *username, *password;

void read(FILE *ptr, FILE *ptr1, FILE *ptr2)
{

    char temp[MAX];
    int i = 0;

    fscanf(ptr, "%s", temp);
    username = (char *)malloc(strlen(temp) + 1);
    strcpy(username, temp);

    fscanf(ptr, "%s", temp);
    password = (char *)malloc(strlen(temp) + 1);
    strcpy(password, temp);

    while (fscanf(ptr1, "%s", temp) != EOF)
    {
        information[i].name = (char *)malloc(strlen(temp) + 1);
        strcpy(information[i].name, temp);
        space++;
        i++;
    }

    i = 0;

    while (fscanf(ptr2, "%d", &information[i].age) != EOF)
    {

        fscanf(ptr2, "%f", &information[i].compatability);
        i++;
    }
}

int main()
{
    char temp[MAX];
    char code;
    FILE *ptr, *ptr1, *ptr2;

    ptr = fopen("passuser.txt", "r");
    ptr1 = fopen("name.txt", "r");
    ptr2 = fopen("age_and_compatability.txt", "r");

    read(ptr, ptr1, ptr2);

    printf("                                          TALENT FINDER\n\n");
    printf("Enter Username:");

    for (int i = 0; i < 5; i++)
    {
        scanf("%s", temp);
        if (strcmp(temp, username) == 0)
        {
            break;
        }

        else if (i < 4)
        {
            printf("Username incorrect try again:");
        }

        else
        {
            printf("Too many incorrect attempts.");
            return 0;
        }
    }

    printf("Enter password:");

    for (int i = 0; i < 5; i++)
    {
        scanf("%s", temp);
        if (strcmp(temp, password) == 0)
        {
            break;
        }

        else if (i < 4)
        {
            printf("Password incorrect try again:");
        }

        else
        {
            printf("Too many incorrect attempts.");
            return 0;
        }
    }

    printf("\n\n");

    printf("Instructions:\nFor code i: Insert\nFor code u: Update\nFor code s: Search\nFor code p: Print\nFor code f: Filter\nFor code c: Compare\nFor code r: Reset passwrord\nFor code e: End\n\n");

    while (1)
    {
        printf("Enter Code:");

        scanf(" %c", &code);

        switch (code)
        {
        case 'i':
            insert();
            break;
        case 's':
            search();
            break;
        case 'u':
            update();
            break;
        case 'p':
            print();
            break;
        case 'f':
            filter();
            break;
        case 'c':
            compare();
            break;
        case 'r':
            reset();
            break;
        case 'e':
            ptr = fopen("passuser.txt", "w");
            ptr1 = fopen("name.txt", "w");
            ptr2 = fopen("age_and_compatability.txt", "w");

            restore(ptr, ptr1, ptr2);
            return 0;

        default:
            printf("Illegal code\n");
        }
        printf("\n\n");
    }

    return 0;
}

void insert()
{
    char temp[MAX];

    if (space == SPACE)
    {
        printf("MAX LIMIT REACHED\n");
        return;
    }

    printf("Enter Name:");
    scanf("%s", temp);

    for (int i = 0; i < space; i++)
    {
        if (strcmp(temp, information[i].name) == 0)
        {
            printf("THIS NAME ALREADY EXISTS\n");
            return;
        }
    }

    information[space].name = (char *)malloc(strlen(temp) + 1);
    strcpy(information[space].name, temp);

    printf("Enter Age:");
    scanf("%d", &information[space].age);

    printf("Enter Compatability:");
    scanf("%f", &information[space].compatability);

    while (information[space].compatability > 10)
    {
        printf("Enter compatability again:");
        scanf("%f", &information[space].compatability);
    }

    space++;
}

void update()
{
    char temp[MAX];

    printf("Enter the name of the person whose data u want to change:");
    scanf("%s", temp);

    for (int i = 0; i < space; i++)
    {
        if (strcmp(temp, information[i].name) == 0)
        {
            printf("Enter the name of the new person:");
            scanf("%s", temp);

            information[i].name = (char *)malloc(strlen(temp) + 1);
            strcpy(information[i].name, temp);

            printf("Enter New Age:");
            scanf("%d", &information[i].age);

            printf("Enter New Compatability:");
            scanf("%f", &information[i].compatability);

            while (information[i].compatability > 10)
            {
                printf("Enter compatability again:");
                scanf("%f", &information[i].compatability);
            }
            return;
        }
    }

    printf("THIS NAME DOES NOT EXIST\n");
}

void search()
{
    char temp[MAX];

    printf("Enter the name of whose information you want to view:");
    scanf("%s", temp);

    for (int i = 0; i < space; i++)
    {
        if (strcmp(information[i].name, temp) == 0)
        {
            printf("\n");
            printf("================================================\n");
            printf("Name\t\tAge\t\tCompatability\n\n");
            printf("%s\t\t%d\t\t%f\n", information[i].name, information[i].age, information[i].compatability);
            printf("================================================\n");
            return;
        }
    }

    printf("NO SUCH NAME EXISTS\n");
}

void print()
{
    printf("\n");
    printf("================================================\n");
    printf("Name\t\tAge\t\tCompatability\n\n");
    for (int i = 0; i < space; i++)
    {
        printf("%s\t\t%d\t\t%f\n", information[i].name, information[i].age, information[i].compatability);
    }
    printf("================================================\n");
}

void filter()
{
}

void compare()
{
}

void reset()
{
    char temp[MAX];

    printf("Enter new username:");
    scanf("%s", temp);

    username = (char *)realloc(username, strlen(temp) + 1);
    strcpy(username, temp);

    printf("Enter new password:");
    scanf("%s", temp);

    password = (char *)realloc(password, strlen(temp) + 1);
    strcpy(password, temp);

    printf("Reaffirm Password:");
    scanf("%s", temp);

    while (strcmp(temp, password) != 0)
    {
        printf("Incorrect, enter again:");
        scanf("%s", temp);
    }
}

void restore(FILE *ptr, FILE *ptr1, FILE *ptr2)
{
    fprintf(ptr, "%s\n", username);
    fprintf(ptr, "%s", password);

    for (int i = 0; i < space; i++)
    {
        fprintf(ptr1, "%s ", information[i].name);
        fprintf(ptr2, "%d\n%f\n", information[i].age, information[i].compatability);
    }
}