#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Cvor;
typedef struct Cvor* Position;

typedef struct Cvor {
    int El;
    Position Next;
} Cvor;

int Stack(Position);
int Queue(Position);
int Push(Position);
int Pop(Position);
int Enqueue(Position);
int Dequeue(Position);
int zatvori(Position);

int main()
{
    Cvor head;
    head.Next = NULL;
    int choice = 0;

    srand((unsigned int)time(NULL));

    while (choice != 3)
    {
        printf("\n1. Stog\n2. Red\n3. Izlaz iz programa\n");
        if (scanf("%d", &choice) != 1)
        {
            printf("Pogresan unos!\n");
            return -1;
        }

        switch (choice)
        {
        case 1:
            Stack(&head);
            break;
        case 2:
            Queue(&head);
            break;
        case 3:
            zatvori(&head);
            break;
        default:
            printf("Pogresan unos\n");
            break;
        }
    }

    printf("Izlaz iz programa\n");
    return 0;
}

int Stack(Position p)
{
    int choice = 0;
    while (choice != 3)
    {
        printf("\n1. Push\n2. Pop\n3. Povratak u prethodni izbornik\n");
        if (scanf("%d", &choice) != 1)
        {
            printf("Pogresan unos!\n");
            return -1;
        }

        switch (choice)
        {
        case 1:
            if (Push(p) == -1)
            {
                zatvori(p);
                return -1;
            }
            break;
        case 2:
            Pop(p);
            break;
        case 3:
            printf("Povratak u prethodni izbornik\n");
            break;
        default:
            printf("Pogresan unos\n");
            break;
        }
    }
    return 0;
}

int Push(Position p)
{
    Position q = (Position)malloc(sizeof(Cvor));
    if (!q)
    {
        printf("Greska u alokaciji\n");
        return -1;
    }
    q->El = rand() % 91 + 10; 
    q->Next = p->Next;
    p->Next = q;
    printf("Push: %d\n", q->El);
    return 0;
}

int Pop(Position p)
{
    Position q = p->Next;
    if (!q)
    {
        printf("Stog je prazan\n");
        return 0;
    }
    printf("Pop: %d\n", q->El);
    p->Next = q->Next;
    free(q);
    return 0;
}

int Queue(Position p)
{
    int choice = 0;
    while (choice != 3)
    {
        printf("\n1. Enqueue\n2. Dequeue\n3. Povratak u prethodni izbornik\n");
        if (scanf("%d", &choice) != 1)
        {
            printf("Pogresan unos!\n");
            return -1;
        }

        switch (choice)
        {
        case 1:
            if (Enqueue(p) == -1)
            {
                zatvori(p);
                return -1;
            }
            break;
        case 2:
            Dequeue(p);
            break;
        case 3:
            printf("Povratak u prethodni izbornik\n");
            break;
        default:
            printf("Pogresan unos\n");
            break;
        }
    }
    return 0;
}

int Enqueue(Position p)
{
    Position q = (Position)malloc(sizeof(Cvor));
    if (!q)
    {
        printf("Greska u alokaciji\n");
        return -1;
    }
    q->El = rand() % 91 + 10; 
    q->Next = NULL;

    while (p->Next != NULL)
        p = p->Next;

    p->Next = q;
    printf("Enqueue: %d\n", q->El);
    return 0;
}

int Dequeue(Position p)
{
    Position q = p->Next;
    if (!q)
    {
        printf("Red je prazan\n");
        return 0;
    }
    printf("Dequeue: %d\n", q->El);
    p->Next = q->Next;
    free(q);
    return 0;
}

int zatvori(Position p)
{
    Position temp;
    while (p->Next != NULL)
    {
        temp = p->Next;
        p->Next = temp->Next;
        free(temp);
    }
    return 0;
}
