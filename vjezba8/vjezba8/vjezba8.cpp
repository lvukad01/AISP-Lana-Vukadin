#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Cvor;
typedef struct Cvor* Position;

struct Cvor
{
    int El;
    Position Next;
};

int Push(Position, int);
int Pop(Position, int*);  
int Calculate(int, char, int);
void FreeStack(Position);

int main()
{
    struct Cvor head;
    FILE* dat;
    char ime_dat[1024] = { 0 };

    head.Next = NULL;

    printf("Unesite ime datoteke za citanje: ");
    scanf(" %s", ime_dat);

    dat = fopen(ime_dat, "r");
    if (dat == NULL)
    {
        printf("Greska u citanju datoteke!\n");
        return -1;
    }

    printf("\nIzraz: ");
    char data[32];
    while (fscanf(dat, " %s", data) == 1)  
    {
        printf(" %s", data);

        int x = atoi(data);
        if (x == 0 && data[0] != '0')  
        {
            int a, b;
            if (!Pop(&head, &b) || !Pop(&head, &a))
            {
                printf("\nGreska: nedovoljno operanada za operator '%c'\n", data[0]);
                FreeStack(&head);
                fclose(dat);
                return -1;
            }

            int n = Calculate(a, data[0], b);
            Push(&head, n);
        }
        else  
        {
            Push(&head, x);
        }
    }

    fclose(dat);

    if (head.Next)
    {
        printf("\nRezultat: %d\n", head.Next->El);
    }
    else
    {
        printf("\nNema rezultata, stog je prazan!\n");
    }

    FreeStack(&head);
    return 0;
}

int Push(Position P, int n)
{
    Position q = (Position)malloc(sizeof(struct Cvor));
    if (!q)
    {
        printf("\nGreska u alokaciji memorije!\n");
        return -1;
    }
    q->El = n;
    q->Next = P->Next;
    P->Next = q;
    return 0;
}

int Pop(Position P, int* result)
{
    if (!P->Next)
    {
        return 0;  
    }

    Position q = P->Next;
    *result = q->El;
    P->Next = q->Next;
    free(q);
    return 1;
}

int Calculate(int x, char c, int y)
{
    int n = 0;
    switch (c)
    {
    case '+': n = x + y; break;
    case '-': n = x - y; break;
    case '*': n = x * y; break;
    case '/':
        if (y != 0)
            n = x / y;
        else
            printf("\nNe moze se dijeliti s 0.\n");
        break;
    case '%':
        if (y != 0)
            n = x % y;
        else
            printf("\nNe moze se dijeliti s 0.\n");
        break;
    default:
        printf("\nNepoznat operator: %c\n", c);
        break;
    }
    return n;
}

void FreeStack(Position P)
{
    Position tmp;
    while (P->Next)
    {
        tmp = P->Next;
        P->Next = tmp->Next;
        free(tmp);
    }
}
