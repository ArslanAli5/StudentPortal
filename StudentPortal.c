#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include"addteacher.h"
#include"addstudentrecord.h"
#include"deleterecord.h"
#include"teacher.h"
void addingQuiz();
void attempquiz();
void printtitle(char* ptrs, int x, int y);
void gotoxy(int x, int y);
void fnmarks(FILE* FP, int i, int dum1);
void Psubject(FILE* FP, int i, int i2);
void printbox(void);

void subject_student_enroll_f(FILE* ptr, char roll_no[]);
void teacher_name_tok_f(char teacher_name[]);
int student_roll_no_conversion_f(char roll_no[]);
int position_f(int t_students, int roll_no_tok, int choice);
void display_quiz_f(FILE* ptr, int position, int* total_quiz_marks);
void display_assignments_f(FILE* ptr, int position, int* total_assignments_marks);
void display_sessional_f(FILE* ptr, int position, int* total_sessional_terminal_marks);
void display_attendence_f(FILE* ptr, int position);
void gpa_display_f(int total_quiz_marks, int total_assignments_marks, int total_sessional_terminal_marks);
void printtitle_student(char* ptrs);
void gotoxy(int x, int y);

typedef struct                              //structure for the quiz//
{
    char question[40];
    char option[20];
    char answer[3];

}quiz_t;



int main(void)
{

    int i, j;
    printtitle("WELCOME", 0, 0);
    gotoxy(20, 7);
    printf("Three For Student Login\n");
    gotoxy(21, 9);
    printf("Two For Teacher Login\n");
    gotoxy(22, 11);
    printf("One For Admin Login\n");

    gotoxy(30, 13);
    scanf("%d", &i);

    //Sleep(1000);
    system("cls");
    if (i == 1)
    {
        while (1)
        {
            printtitle("ADMIN", 0, 0);
            gotoxy(2, 5);
            printf("1) Create Teacher Account\n");
            gotoxy(2, 7);
            printf("2) Add Student Data\n");
            gotoxy(2, 9);
            printf("3) Delete Student Record\n");
            gotoxy(2, 11);
            printf("0) Exit");
            printf("\n_____________________\n");
            gotoxy(30, 14);
            scanf("%d", &j);
            system("cls");
            if (j == 1)
                addteacher();
            if (j == 2)
                addstudentrecord();
            if (j == 3)
                deleterecord();
            if (j == 0)
                break;
            system("cls");
        }

    }
    else if (i == 2)
    {
        teacherlogin();
    }
    else if (i == 3)
    {
        char roll_no[15];
        printf("Enter your roll no(****-***-***) \n");
        printtitle_student(" ");
        gotoxy(23, 3);
        fflush(stdin);
        gets(roll_no);
        system("cls");
        FILE* ptr;
        ptr = fopen("data.txt", "r+");
        if (ptr == NULL)
        {
            printf("ERROR");
        }
        subject_student_enroll_f(ptr, roll_no);
        fclose(ptr);
    }
}









void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}





//Start of the quiz creating function for teacher
void addingQuiz()
{
    int total_quizs;
    char quizzz[5];

    FILE* ptr;
    if ((ptr = fopen("quiz1.txt", "w")) == NULL)
        printf("File does not exist");

    printf("Enter no of quiz questions : ");
    scanf("%d", &total_quizs);

    printf("\n\n\n");

    itoa(total_quizs, quizzz, 10);
    fputs(quizzz, ptr);
    quiz_t quiz;
    fputs("\n", ptr);

    for (int i = 0; i < total_quizs; i++)
    {
        printf("\n\nEnter the %d question of quiz :  ", i + 1);
        fflush(stdin);
        gets(quiz.question);
        fputs(quiz.question, ptr);
        fputs("\n", ptr);

        for (int o = 0; o < 4; o++)
        {
            printf("\nEnter the %d option for the question %d : ", o + 1, i + 1);
            fflush(stdin);
            gets(quiz.option);
            fputs(quiz.option, ptr);
            fputs("\n", ptr);
        }

        printf("\nEnter the correct option number of question %d : ", i + 1);
        fflush(stdin);
        gets(quiz.answer);
        fputs(quiz.answer, ptr);
        fputs("\n", ptr);
    }
    fclose(ptr);
}

// Starts of quizs attempting function
void attempquiz()
{
    FILE* prt;
    char t_quize[5];
    char option[5];
    int count_correct = 0;
    int count_wrong = 0;
    int total_quizs;
    quiz_t attempt;
    if ((prt = fopen("quiz1.txt", "r")) == NULL)
        printf("Failed to open the File");

    fgets(t_quize, 5, prt);
    total_quizs = atoi(t_quize);

    for (int i = 0; i < total_quizs; i++)
    {
        fflush(stdin);
        fgets(attempt.question, 40, prt);
        printf("Q%d)%s\n", i + 1, attempt.question);

        for (int o = 0; o < 4; o++)
        {
            fgets(attempt.option, 20, prt);
            printf("%d)%s", o + 1, attempt.option);
        }
        printf("\nEnter the correct option number : ");
        fflush(stdin);
        gets(option);                                       /* Taking option from the student*/
        fgets(attempt.answer, 5, prt);
        strcat(option, "\n");


        if (!strcmp(option, attempt.answer))                 /*Checking if the user option is correct or wrong*/
        {
            printf("Correct answer\n\n\n");
            count_correct++;
        }
        else
        {
            printf("Oops Wrong answer\n\n\n");
            count_wrong++;
        }



    }
    printf("Your total correct answers : %d\n", count_correct);
    printf("Your total wrong answers : %d\n", count_wrong);



}


void printtitle(char* ptrs, int x, int y)
{
    gotoxy(x, y);
    printf("                           __________               \n\n");
    gotoxy(x, y + 1);
    printf("                             %s                               \n", ptrs);
    gotoxy(x, y + 2);
    printf("                           __________                 ");
}


void fnmarks(FILE* FP, int i, int dum1)
{
    int position;
    char marks[2];
    int mark;
    position = (280 * i) - dum1 + i + 1;
    fseek(FP, position, 0);
    do
    {
        scanf("%d", &mark);
    } while (mark < 0 || mark>99);
    itoa(mark, marks, 10);
    fprintf(FP, "%s", marks);
}

void Psubject(FILE* FP, int i, int i2)
{
    int position;
    char subject[40];
    position = (280 * i) - 215 + i2;
    fseek(FP, position, 0);
    fgets(subject, 40, FP);
    printf("SUBJECT: %s\n\n", strupr(subject));
}




void printbox(void)
{
    gotoxy(15, 5);
    printf("* * * * * * * * * * * * * * * * * \n");
    gotoxy(15, 6);
    printf("* USERNAME:                     *\n");
    gotoxy(15, 7);
    printf("*                               *\n");
    gotoxy(15, 8);
    printf("* PASSWORD:                     *\n");
    gotoxy(15, 9);
    printf("* * * * * * * * * * * * * * * * * \n");

}

void regname(FILE* fp, int i, int s)
{
    char student_reg[20];
    char studen_name[20];
    int position = (280 * i) - 240 + i - 2;
    rewind(fp);
    fseek(fp, position, 0);
    fgets(student_reg, 20, fp);
    position = (280 * i) - 179 + i - 2;
    fseek(fp, position, 0);
    fgets(studen_name, 20, fp);
    printf("%-3d%-45s%-25s", s, studen_name, strupr(student_reg));
}


/*All student Interface Functions */

void subject_student_enroll_f(FILE* ptr, char roll_no[])
{
    int t_students, t_subjects;
    char roll_no_f[25];
    char subject_f[60];
    int position_student = 39;
    int roll_no_tok;
    int position;
    int total_quiz_marks = 0;
    int total_assignments_marks = 0;
    int total_sessional_terminal_marks = 0;

    fscanf(ptr, "%d %d", &t_students, &t_subjects);
    int possibilities = t_students * t_subjects;

    int i = 0, z = 1, l = 1, choice;
    char teacher_name[30];
    char credit_hours[5];
    char student_name[80];
    while (i <= possibilities)
    {
        position_student += 281;

        fseek(ptr, position_student - 39, 0);
        fgets(teacher_name, 25, ptr);

        fseek(ptr, position_student + 134, 0);
        fgets(credit_hours, 3, ptr);

        fseek(ptr, position_student + 61, 0);
        fgets(student_name, 75, ptr);

        fseek(ptr, position_student, 0);
        fgets(roll_no_f, 13, ptr);
        i++;

        if (!strnicmp(roll_no, roll_no_f, strlen(roll_no)))       /*checking is roll no matched or not */
        {
            if (l == 1)
            {
                printtitle_student(strupr(student_name));
                l++;
                printf("\n\n       SUBJECT                          TEACHER NAME      CREDIT HOUR\n\n");
            }
            fseek(ptr, 8, 1);
            fgets(subject_f, 40, ptr);

            printf("%d)%-10s", z, subject_f);
            teacher_name_tok_f(teacher_name);                   /* Separating Teacher Name */

            printf("%s\n\n", credit_hours);                      /* printing credit hours of the subject */
            z++;
        }
    }

    if (z == 1)                                                 /* If the roll no does not exist */
    {
        printf("\n\n            Roll no does not exist\n\n");
        return;
    }

    printf("\n_________________________________________________________________\n");    /* Subject to select to show data */
    printf("Enter the subject no you want to check : ");
    scanf("%d", &choice);

    if (choice >= z)                                           /* To check for invalid subject choice */
    {
        system("cls");
        printf("\n\n        INVALID CHOICE\n\n");
        return;
    }

    roll_no_tok = student_roll_no_conversion_f(roll_no);       /* Taking the roll_no in int */
    position = position_f(t_students, roll_no_tok, choice);
    display_quiz_f(ptr, position, &total_quiz_marks);
    display_assignments_f(ptr, position, &total_assignments_marks);
    display_sessional_f(ptr, position, &total_sessional_terminal_marks);
    display_attendence_f(ptr, position);

    printf("      Press 1 if u want to see GPA of this subject or 2 to attempt the quiz\n");
    printf("                                  ( )");
    gotoxy(35, 60);
    scanf("%d", &choice);

    if (choice == 1)                  /* displaying GPA */
    {
        gpa_display_f(total_quiz_marks, total_assignments_marks, total_sessional_terminal_marks);
    }
    else if (choice == 2)            /* attempting quiz */
    {
        attempquiz();
    }

}


void teacher_name_tok_f(char teacher_name[])
{
    char* token = strtok(teacher_name, "@");
    printf("%-20s", strupr(teacher_name));
}
int student_roll_no_conversion_f(char roll_no[])
{
    /* to get roll no in int */
    char* token = strtok(roll_no, "-");
    token = strtok(NULL, "-");
    token = strtok(NULL, "-");

    int roll_no_tok = atoi(token);
    return (roll_no_tok);
}

/* To find the position of the enter roll no according to the selected subject */

int position_f(int t_students, int roll_no_tok, int choice)
{
    int line = t_students * (choice - 1) + roll_no_tok;

    /* Position of student in file */
    int position = line * 281;
    return (position);
}
void display_quiz_f(FILE* ptr, int position, int* total_quiz_marks)
{
    /* to get quiz data from file */

    int position_quiz = position + 176;
    char quiz[5];
    printf("\n\n         Quiz Marks       \n");
    printf("        ------------\n\n");
    for (int i = 1; i <= 4; i++)
    {
        fseek(ptr, position_quiz, 0);
        fgets(quiz, 3, ptr);
        printf("Quiz%d : %s\n", i, quiz);
        *total_quiz_marks += atoi(quiz);
    }

}
void display_assignments_f(FILE* ptr, int position, int* total_assignment_marks)
{
    /* To print assignments data */

    int position_assignment = position + 188;
    char assignment[5];
    printf("\n\n      Assignments Marks      \n");
    printf("    --------------------\n\n");
    for (int inner = 1; inner <= 4; inner++)
    {
        fseek(ptr, position_assignment, 0);
        fgets(assignment, 3, ptr);
        printf("Assignment%d : %s\n", inner, assignment);
        *total_assignment_marks += atoi(assignment);
    }

}
void display_sessional_f(FILE* ptr, int position, int* total_sessional_terminal_marks)
{
    /* To print sessionals and terminals dara */

    int position_sessionals = position + 200;
    char sessional[5];
    printf("\n\n       Sessional Marks\n");
    printf("      -----------------\n");
    for (int s = 1; s <= 3; s++)
    {
        fseek(ptr, position_sessionals, 0);
        fgets(sessional, 3, ptr);
        if (s == 3)
        {
            printf("\n\n       Terminal Marks \n");
            printf("      ----------------\n\n");
            printf("Terminal marks : %s\n", sessional);
            *total_sessional_terminal_marks += atoi(sessional);
            break;
        }
        printf("\nSessiona %d Marks : %s\n", s, sessional);
        *total_sessional_terminal_marks += atoi(sessional);
    }

}
void display_attendence_f(FILE* ptr, int position)
{
    /* To count the presents and absents of student */

    int position_attendence = position + 220;
    rewind(ptr);
    int t_attendence, g, g1;
    fscanf(ptr, "%d %d %d", &g, &g1, &t_attendence);

    char attendence[3];
    int absents = 0, presents = 0;
    for (int a = 0; a <= 60; a++)
    {
        fseek(ptr, position_attendence, 0);
        fgets(attendence, 2, ptr);
        position_attendence += 1;
        if (!strcmp(attendence, "p") || !strcasecmp(attendence, "P"))
        {
            presents++;
        }
        else if (!strcmp(attendence, "a") || !strcmp(attendence, "A"))
        {
            absents++;
        }
    }
    t_attendence = (presents + absents);
    printf("\n\n        Attendence\n");
    printf("       ------------\n\n");
    printf("     Total Classes : %d\n", t_attendence);
    printf("Presents : %d\n", presents);
    printf("Absents :  %d\n\n", absents);
}

void gpa_display_f(int total_quiz_marks, int total_assignments_marks, int total_sessional_terminal_marks)
{
    /* To display GPA and grade */

    printf("           GPA\n");
    printf("          -----\n\n");
    double total_marks;
    char grade[3];
    double gpa;

    total_quiz_marks = total_quiz_marks / 40 * 10;
    total_assignments_marks = total_assignments_marks * 0.375;
    total_marks = total_quiz_marks + total_assignments_marks + total_sessional_terminal_marks;
    printf("Total marks :%f\n", total_marks);

    if (total_marks >= 90.00)
    {
        strcat(grade, "A");
        gpa = 4;
    }
    else if (total_marks >= 85)
    {
        strcat(grade, "A-");
        gpa = 3.7;
    }
    else if (total_marks >= 80)
    {
        strcat(grade, "B+");
        gpa = 3.3;
    }
    else if (total_marks >= 75)
    {
        strcat(grade, "B");
        gpa = 3.0;
    }
    else if (total_marks >= 70)
    {
        strcat(grade, "  B-");
        gpa = 2.7;
    }
    else if (total_marks >= 65)
    {
        strcat(grade, "C+");
        gpa = 2.3;
    }
    else if (total_marks >= 60)
    {
        strcat(grade, "C");
        gpa = 2.0;
    }
    else if (total_marks >= 55)
    {
        strcat(grade, "C-");
        gpa = 1.7;
    }
    else if (total_marks >= 50)
    {
        strcat(grade, "D");
        gpa = 1.3;
    }
    else
    {
        strcat(grade, "F");
        gpa = 0.0;
    }
    printf("GPA : %.2f\n", gpa);
    fflush(stdin);
    printf("Grade : %s\n\n\n", grade);

}


void printtitle_student(char* ptrs)
{
    printf("                ___________________________               \n\n");
    printf("                           %s                               \n", ptrs);
    printf("                ___________________________                 \n");
}
