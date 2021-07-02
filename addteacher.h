#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void addteacher(void)
{
    FILE* fp;
    int t_lenght, position;
    int m_subject, n_student;
    int i;
    char teacher_id[40];
    char regno_student[20];
    char course_titile[40];
    char batch[5] = "";
    char degree[5] = "";
    char dump3[5] = "";
    char dump4[5] = "";
    char credit[2];
    char teacher_pas[8];
    int count;
    fp = fopen("data.txt", "w");
    if (fp == NULL)
    {
        printf("Error");
    }
    printf("\nNo of Students: ");
    scanf("%d", &n_student);
    fflush(stdin);
    printf("\nBatch: ");
    scanf("%s", batch);
    fflush(stdin);
    printf("\nDegree: ");
    scanf("%s", degree);
    fflush(stdin);
    printf("\nNO of Courses: ");
    scanf("%d", &m_subject);
    fflush(stdin);
    fprintf(fp, "%d %d %d", n_student, m_subject, 60);
    count = 279 - ftell(fp);
    fseek(fp, count, 1);
    fputs("\n", fp);
    while (m_subject > 0)
    {
        int n, k, i;
        printf("\nTeacher ID: ");
        scanf("%s", teacher_id);
        fflush(stdin);
        printf("\nPassword: ");
        scanf("%s", teacher_pas);
        fflush(stdin);
        printf("\nCourse Title: ");
        gets(course_titile);
        fflush(stdin);
        printf("\nCredit: ");
        scanf("%d", &i);
        fflush(stdin);
        itoa(i, credit, 10);
        t_lenght = 24 - strlen(teacher_id);//This line is for finding the last bytes of string out of 30
        position = strlen(teacher_id); // This line is for finding the
        position = position + t_lenght;
        for (k = 1; k <= n_student; k++)
        {
            char roll_no[5] = "";
            char dump[5] = "00";
            char dump1[5] = "0";
            itoa(k, roll_no, 10);
            if (strlen(roll_no) == 1)
            {
                strcat(dump, roll_no);
                strcpy(roll_no, "");
                strcpy(roll_no, dump);
            }
            else if (strlen(roll_no) == 2)
            {
                strcat(dump1, roll_no);
                strcpy(roll_no, dump1);
            }
            strcat(strcat(strcat(strcat(strcpy(regno_student, batch), "-"), degree), "-"), roll_no);
            printf("%s\n", regno_student);
            fputs(teacher_id, fp);

            position = ftell(fp) + t_lenght;

            fseek(fp, position, 0);
            fputs(teacher_pas, fp);
            fseek(fp, position + 15, 0);
            fputs(regno_student, fp);
            position = position + 40;
            fseek(fp, position, 0);
            fputs(course_titile, fp);
            position = position + 110;
            fseek(fp, position, 0);
            fputs(credit, fp);
            fseek(fp, position + 105, 0);
            fputs("\n", fp);
        }
        m_subject--;
    }
    for (i = 279; i > 0; i--)
    {
        fputs("0", fp);
    }
    fclose(fp);
}
