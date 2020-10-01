#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <conio.h>
#include <string.h>
using namespace std;

/* Структура для хранения информации про одного человека */
typedef struct tagITEM
{
    char Surname[20], Name[20];
    int Age;
} ITEM;

/* Массив максимум на 20 человек */
ITEM Men[20];

/* Количество занятых элементов в массиве */
int Number;

/* Функция для вывода всех элеиентов */
void Print(void)
{
    int i;

    printf(" N  Surname              Name                  Age\n");
    for (i = 0; i < Number; i++)
        printf("%2i. %-20s %-20s %3i\n", i + 1, Men[i].Surname,
            Men[i].Name, Men[i].Age);
} /* End of 'Print' function */

/* Функция для добавления элемента */
void Add(void)
{
    if (Number == 19)
    {
        fprintf(stderr, "error to add\n");
        return;
    }

    printf("Surname > ");
    scanf("%s", Men[Number].Surname);
    printf("Name > ");
    scanf("%s", Men[Number].Name);
    printf("Age > ");
    scanf("%i", &Men[Number].Age);

    Number++;
} /* End of 'Add' function */

/* Функция для удаления элемента */
void Del(void)
{
    int i;

    Print();
    printf("N > ");
    scanf("%i", &i);
    if (i < 1 || i > Number)
    {
        fprintf(stderr, "%i dont exist\n", i);
        return;
    }

    for (i--; i < Number - 1; i++)
        Men[i] = Men[i + 1];

    Number--;
} /* End of 'Del' function */

/* Функция для сохранения массива в файле */
void Save(void)
{
    FILE* F;
    int i;

    if ((F = fopen("task1.dat", "wt")) == NULL)
    {
        fprintf(stderr, "error open to w 'task1.dta'\n");
        return;
    }

    fprintf(F, "%i\n", Number);
    for (i = 0; i < Number; i++)
        fprintf(F, "%s\n%s\n%i\n", Men[i].Surname, Men[i].Name, Men[i].Age);

    fclose(F);
} /* End of 'Save' function */

/* Функция для чтения массива из файла */
void Load(void)
{
    FILE* F;
    int i;

    if ((F = fopen("task1.dat", "rt")) == NULL)
    {
        fprintf(stderr, "error open to r 'task1.dta'\n");
        return;
    }

    fscanf(F, "%i", &Number);
    for (i = 0; i < Number; i++)
        fscanf(F, "%s%s%i", Men[i].Surname, Men[i].Name, &Men[i].Age);

    fclose(F);
} /* End of 'Load' function */

/* Функция для упорядочивания массива по фамилии */
void Sort(void)
{
    int i, j;
    ITEM Temp;

    for (j = Number - 1; j > 0; j--)
        for (i = 0; i < j; i++)
            if (strcmp(Men[i].Surname, Men[i + 1].Surname) > 0)
            {
                Temp = Men[i];
                Men[i] = Men[i + 1];
                Men[i + 1] = Temp;
            }
} /* End of 'Sort' function */

/* Вывод меню и чтение номера выбранного пункта */
int Menu(void)
{
    int c = 0;

    while ((c < '0' || c > '6') && c != 27)
    {
        printf("0 : exit\n"
            "1 : add\n"
            "2 : save\n"
            "3 : load\n"
            "4 : print\n"
            "5 : sort\n"
            "6 : del\n"
            ">");
        c = getch();
        printf("%c\n", c);
    }
    return c;
} /* End of 'Menu' function */

/* Основная функция */
void main(void)
{
    int Selection;

    Number = 0;
    while ((Selection = Menu()) != '0' && Selection != 27)
        switch (Selection)
        {
        case '1':
            Add();
            break;
        case '2':
            Save();
            break;
        case '3':
            Load();
            break;
        case '4':
            Print();
            break;
        case '5':
            Sort();
            break;
        case '6':
            Del();
            break;
        }
} /* End of 'main' function */

/* End of 'task_1_1.c' file */