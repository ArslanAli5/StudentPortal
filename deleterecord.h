#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include "StudentPortal.cpp"

void deleterecord(void)
{
    FILE* fp;
    char student_reg[30] = "";
    char student_name[30] = "";
    int position, n1, n2;
    FILE* fileptr1;
    char ch = 'A';
    int delete_line, temp = 0;
    fp = fopen("data.txt", "r+");
    if (fp == NULL)
    {
        printf("Error");
    }
    fseek(fp, 0, 0);
    fscanf(fp, "%d %d", &n1, &n2);
    int s_number = n1;
    int i = 2, i2 = 0;
    printf("Enter Number to Delete the Record!\n_____________________\n\n");
    int s = 1;
    for (s_number = n1; s_number > 0; s_number--)
    {
        rewind(fp);
        position = (280 * i) - 240 + i2;
        fseek(fp, position, 0);
        fgets(student_reg, 20, fp);
        position = (280 * i) - 179 + i2;
        fseek(fp, position, 0);
        fgets(student_name, 20, fp);
        printf("%-2d %-45s%-25s\n", s, student_name, student_reg);
        i++; i2++; s++;
    }
    printf("_____________________\n");
    gotoxy(30, 14);
    rewind(fp);
    do
    {
        scanf("%d", &delete_line);
    } while (delete_line<0 || delete_line>n1);
    fileptr1 = fopen("replica.txt", "w");
    while (ch != EOF)
    {
        ch = getc(fp);
        if (temp != delete_line)
        {
            putc(ch, fileptr1);
        }
        if (ch == '\n')
        {
            if (temp == delete_line)
            {
                delete_line += n1;
            }
            temp++;
        }
    }
    rewind(fp);
    system("cls");
    char aa[20] = "RECORD DELETED";
    printtitle(aa, 0, 7);
    Sleep(3000);
    n1--;
    rewind(fileptr1);
    fprintf(fileptr1, "%d %d", n1, n2);
    fclose(fp);
    fclose(fileptr1);
    remove("data.txt");
    rename("replica.txt", "data.txt");

}
