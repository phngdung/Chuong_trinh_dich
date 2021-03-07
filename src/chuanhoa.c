#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

void xoa(int id, char a[])
{
    int i;
    for (i = id; i < strlen(a) - 1; i++)
    {
        a[i] = a[i + 1];
    }
    a[strlen(a) - 1] = '\0';
}

void trimLeft(char a[])
{
    for (int i = 0; i < strlen(a); i++)
        if (a[i] == ' ')
            xoa(i--, a);
        else
            break;
}

void trimRight(char a[])
{
    for (int i = strlen(a) - 1; i >= 0; i--)
        if (a[i] == ' ')
            xoa(i, a);
        else
            break;
}

void trimMiddle(char a[])
{
    for (int i = strlen(a) - 2; i >= 0; i--)
    {
        if (a[i] == ' ' && a[i - 1] == ' ')
            xoa(i, a);
    }
}

void Upper(char a[])
{
    a[0] = toupper(a[0]);
    for (int i = 1; i < strlen(a); i++)
    {
        if (a[i - 1] == ' ')
            a[i] = toupper(a[i]);
        else a[i] = tolower(a[i]);
    }
}

void chuanhoa(char a[])
{
    trimLeft(a);
    trimRight(a);
    trimMiddle(a);
    Upper(a);
}

int main()
{
    char a[MAX];
    printf("Nhap xau can chuan hoa: ");
    gets(a);
    chuanhoa(a);
    printf("Xau sau khi chuan hoa la :%s\n", a);
}
