#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct good {
	char name[20];
	int price;
	char type[20];
	char article[20];
	int quantity;
};

good storage[50];

good temp[50];

int Number;


int Print_Menu(void)
{
    int c = 0;
    printf("Choose print type:\n");
    printf("1 : Print to console\n"
        "2 : Print to file\n"
        ">");
    scanf("%s", &c);
    return c;
}

void Save_Base(void)
{
    FILE* F;
    int i;

    if ((F = fopen("base.txt", "wt")) == NULL)
    {
        fprintf(stderr, "Open for save error 'base.txt'\n");
        return;
    }

    fprintf(F, "%i\n", Number);
    for (i = 0; i < Number; i++)
        fprintf(F, "%s %i %s %s %i\n", storage[i].name, storage[i].price, storage[i].type, storage[i].article, storage[i].quantity);


    fclose(F);
}

void Print_Base(void) {
    int i;
    printf("\n\n\n");
    printf(" N                   Name  Price                  Type               Article  Quant\n");
    for (i = 0; i < Number; i++)
        printf("%2i.  %20s  %5i  %20s  %20s  %5i\n", i + 1, storage[i].name, storage[i].price, storage[i].type, storage[i].article, storage[i].quantity);
    printf("\n\n\n");
}

void Output(void)
{
    int i, Selection;

    Selection = Print_Menu();

    while (Selection)
    {

        if (Selection == '1')
        {
            Print_Base();
            break;
        }
        if (Selection == '2')
        {
            Save_Base();
            break;
        }
        if (Selection < '0' || Selection > '2')
        {
            printf("Wrong choose in output menu, try again\n");
            Selection = Print_Menu();
        }
    }
}


int Input_Menu(void)
{
    int c = 0;
    printf("Choose input type:\n");
    printf("1 : Input from keyboard\n2 : Load base from file\n>");
    scanf("%s", &c);
    return c;
}

void Input_Base_From_Keyboard(void)
{
    int i;
    printf("Input N > ");
    scanf("%d", &Number);
    printf("Input data base\n");
    printf("Name Price Type Article Quantity \n");
    for (i = 0; (i < Number); i++)
    {
        scanf("%s %i %s %s %i", storage[i].name, &storage[i].price, storage[i].type, storage[i].article, &storage[i].quantity);
    }
    Print_Base();
}

void Load_Base_From_File(void)
{
    FILE* F;
    int i;

    if ((F = fopen("base.txt", "rt")) == NULL)
    {
        printf("Open for load error 'base.txt'\n");
        return;
    }

    fscanf(F, "%i", &Number);
    for (i = 0; i < Number; i++)
        fscanf(F, "%s %i %s %s %i\n", storage[i].name, &storage[i].price, storage[i].type, storage[i].article, &storage[i].quantity);

    fclose(F);
    Print_Base();
}

void Input(void) 
{
    int i, Selection;

    Selection = Input_Menu();

    while (Selection)
    {

        if (Selection == '1')
        {
            Input_Base_From_Keyboard();
            break;
        }
        if (Selection == '2')
        {
            Load_Base_From_File();
            break;

            Print_Base();
        }
        if (Selection < '0' || Selection > '2')
        {
            printf("Wrong choose in input menu, try again\n");
            Selection = Input_Menu();
        }
    }
}

void Add(void)
{
    int lines, i;
    if (Number == 49)
    {
        printf("Impossbile to add new elements\n");
        return;
    }

    printf("\n\n\n");
    printf("How many lines to add? > ");
    scanf("%d", &lines);
    if (lines + Number < 49)
    {
        printf("Name Price Type Article Quantity \n");
        for (i = Number; i < Number + lines; i++)
        {
            scanf("%s %i %s %s %i", storage[i].name, &storage[i].price, storage[i].type, storage[i].article, &storage[i].quantity);
        }
        Number = Number + lines;
    }

    else 
    {
        printf("ERROR : To much lines to add");
        Add();
    }
}


int Del_Menu(void)
{
    int c = 0;
    printf("\n");
    printf("1 : Delete from N to K\n2 : Delete N string\n>");
    scanf("%s", &c);
    return c;
}

void Del_N(void) 
{    
    int i;
    printf("Input N > ");
    scanf("%i", &i);
    if (i < 1 || i > Number)
    {
        printf("ERROR : No such element %i exist\n", i);
        return;
    }

    for (i--; i < Number - 1; i++)
        storage[i] = storage[i + 1];

    Number--;

}

void Del_From_N_to_K(void)
{
    int N, K, i;
    printf("Input N >");
    scanf("%i", &N);
    printf("Input K >");
    scanf("%i", &K);
    if (N < 0 || N > Number)
    {
        printf("ERROR : Can not delete\n");
        return;
    }
    if (K < 1 || K > Number || K < N)
    {
        printf("ERROR: Can not delete\n");
        return;
    }

    for (i = N; K > i; i++)
        for (; i < Number - 1; i++)
            storage[i] = storage[i + 1];
        

    Number = Number - (K - N);

}

void Del(void)
{
    int i, Selection;

    Print_Base();
    Selection = Del_Menu();

    while (Selection)
    {

        if (Selection == '1')
        {
            Del_From_N_to_K();
            Print_Base();
            break;
        }
        if (Selection == '2')
        {
            Del_N();
            Print_Base();
            break;
        }

        if (Selection < '0' || Selection > '2')
        {
            printf("Wrong choose in menu delete, try again\n");
            Selection = Del_Menu();
        }
    }
}


int Sort_Menu(void)
{
    int c = 0;
    printf("Sort by:\n");
    printf("1 : By Name\n2 : By Price\n3 : By Type\n4 : By Article\n5 : By Quantity\n>");
    scanf("%s", &c);
    return c;
}

void Sort_By_Name(void)
{
    int i, j;
    good Temp;

    for (j = Number - 1; j > 0; j--)
        for (i = 0; i < j; i++)
            if (strcmp(storage[i].name, storage[i + 1].name) > 0)
            {
                Temp = storage[i];
                storage[i] = storage[i + 1];
                storage[i + 1] = Temp;
            }
}

void Sort_By_Type(void)
{
    int i, j;
    good Temp;

    for (j = Number - 1; j > 0; j--)
        for (i = 0; i < j; i++)
            if (strcmp(storage[i].type, storage[i + 1].name) > 0)
            {
                Temp = storage[i];
                storage[i] = storage[i + 1];
                storage[i + 1] = Temp;
            }
}

void Sort_By_Article(void)
{
    int i, j;
    good Temp;

    for (j = Number - 1; j > 0; j--)
        for (i = 0; i < j; i++)
            if (strcmp(storage[i].article, storage[i + 1].name) > 0)
            {
                Temp = storage[i];
                storage[i] = storage[i + 1];
                storage[i + 1] = Temp;
            }
}

void Sort_By_Price(void)
{
    int i, j;
    good Temp;

    for (j = Number - 1; j > 0; j--)
        for (i = 0; i < j; i++)
            if (storage[i].price > storage[i + 1].price)
            {
                Temp = storage[i];
                storage[i] = storage[i + 1];
                storage[i + 1] = Temp;
            }
}

void Sort_By_Quantity(void)
{
    int i, j;
    good Temp;

    for (j = Number - 1; j > 0; j--)
        for (i = 0; i < j; i++)
            if (storage[i].quantity > storage[i + 1].quantity)
            {
                Temp = storage[i];
                storage[i] = storage[i + 1];
                storage[i + 1] = Temp;
            }
}

void Sort(void)
{
    int Selection;
    Selection = Sort_Menu();
    while (Selection)
    {

        if (Selection == '1')
        {
            Sort_By_Name();
            break;
        }
        if (Selection == '2')
        {
            Sort_By_Price();
            break;
        }
        if (Selection == '3')
        {
            Sort_By_Type();
            break;
        }
        if (Selection == '4')
        {
            Sort_By_Article();
            break;
        }
        if (Selection == '5')
        {
            Sort_By_Quantity();
            break;
        }
        if (Selection < '0' || Selection > '5')
        {
            printf("Wrong choose search, try again\n");
            Selection = Sort_Menu();
        }
    }

}


int Search_Menu(void)
{
    int c = 0;
    printf("Search by:\n");
    printf("1 : By Name\n2 : By Price\n3 : By Type\n4 : By Article\n5 : By Quantity\n>");
    scanf("%s", &c);
    return c;
}

void Search_By_Name(char search_value[20])
{
    int i, j = 0;
    printf("\n\n\n");
    printf(" N                   Name  Price                  Type               Article  Quant\n");
    for (i = 0; i < Number; i++)
        if (strcmp(storage[i].name, search_value) == 0)
        {
            printf("%2i.  %20s  %5i  %20s  %20s  %5i\n", j + 1, storage[i].name, storage[i].price, storage[i].type, storage[i].article, storage[i].quantity);
            j += 1;
        }
    printf("\n\n\n");
}

void Search_By_Type(char search_value[20]) 
{
    int i, j = 0;
    printf("\n\n\n");
    printf(" N                   Name  Price                  Type               Article  Quant\n");
    for (i = 0; i < Number; i++)
        if (strcmp(storage[i].type, search_value) == 0)
        {
            printf("%2i.  %20s  %5i  %20s  %20s  %5i\n", j + 1, storage[i].name, storage[i].price, storage[i].type, storage[i].article, storage[i].quantity);
            j += 1;
        }
    printf("\n\n\n");
}

void Search_By_Article(char search_value[20]) 
{
     int i, j = 0;
     printf("\n\n\n");
     printf(" N                   Name  Price                  Type               Article  Quant\n");
     for (i = 0; i < Number; i++)
         if (strcmp(storage[i].article, search_value) == 0)
         {
             printf("%2i.  %20s  %5i  %20s  %20s  %5i\n", j + 1, storage[i].name, storage[i].price, storage[i].type, storage[i].article, storage[i].quantity);
             j += 1;
         }
     printf("\n\n\n");
}

void Search_By_Price(char search_value[20]) 
{
    int i, j = 0;
    int tmp;
    printf("\n\n\n");
    printf(" N                   Name  Price                  Type               Article  Quant\n");
    for (i = 0; i < Number; i++) {
        tmp = atoi(&search_value[0]);
        if (tmp == storage[i].price)
        {
            printf("%2i.  %20s  %5i  %20s  %20s  %5i\n", j + 1, storage[i].name, storage[i].price, storage[i].type, storage[i].article, storage[i].quantity);
            j += 1;
        }
    }
    printf("\n\n\n");
}

void Search_By_Quantity(char search_value[20]) 
{
    int i, j = 0;
    int tmp;
    printf("\n\n\n");
    printf(" N                   Name  Price                  Type               Article  Quant\n");
    for (i = 0; i < Number; i++) {
        tmp = atoi(&search_value[0]);
        if (tmp == storage[i].quantity)
        {
            printf("%2i.  %20s  %5i  %20s  %20s  %5i\n", j + 1, storage[i].name, storage[i].price, storage[i].type, storage[i].article, storage[i].quantity);
            j += 1;
        }
    }
    printf("\n\n\n");
}

void Search(void)
{
    int Selection;
    char search_value[20];
    printf("Input search value > ");
    scanf("%s", search_value);
    Selection = Search_Menu();
    while (Selection)
    {

        if (Selection == '1')
        {
            Search_By_Name(search_value);
            break;
        }
        if (Selection == '2')
        {
            Search_By_Price(search_value);
            break;
        }
        if (Selection == '3')
        {
            Search_By_Type(search_value);
            break;
        }
        if (Selection == '4')
        {
            Search_By_Article(search_value);
            break;
        }
        if (Selection == '5')
        {
            Search_By_Quantity(search_value);
            break;
        }
        if (Selection < '0' || Selection > '5')
        {
            printf("Wrong choose search, try again\n");
            Selection = Search_Menu();
        }
    }

}


int Menu(void)
{
    int c = 0;
    printf("0 : Clean Console\n1 : Add strings\n2 : Input\n3 : Output\n4 : Sort base\n5 : Delete strings\n6 : Search\n>");
    scanf("%s", &c);
    system("cls");
    return c;

}

void main(void)
    {
        int Selection;

        Number = 0;
        Selection = Menu();
        while (Selection)
        {
            
            if (Selection == '1')
            {
                Add();
                Print_Base();
            }

            if (Selection == '2') 
            {
                Input();
            }

            if (Selection == '3') 
            {
                Output();
            }

            if (Selection == '4') 
            {
                Sort();
                Print_Base();
            }

            if (Selection == '5')
            {
                Del();
            }

            if (Selection == '6')
            {
                Print_Base();
                Search();
            }

            if (Selection < '0' || Selection > '7')
                printf("Wrong choose, try again\n");
            Selection = Menu();
        }
    }