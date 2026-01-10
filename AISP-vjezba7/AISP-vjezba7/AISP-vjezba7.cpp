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

struct QCvor;
typedef struct QCvor* QPosition;

typedef struct QCvor {
    int El;
    int Prioritet;
    QPosition Next;
} QCvor;

int Stack(Position);
int Push(Position, int);
int Pop(Position);
int Count(Position);
int PrintList(Position);
int zatvori(Position);

int Queue(QPosition);
int Enqueue(QPosition);
int Dequeue(QPosition);
int PrintListQ(QPosition);
int zatvoriQ(QPosition);

int main()
{
    Cvor head;
    QCvor qhead;
    head.Next = NULL;
    qhead.Next = NULL;

    srand((unsigned int)time(NULL));

    int choice = 0;
    while (choice != 3)
    {
        printf("\n1. Cirkularni stog\n2. Red s prioritetom\n3. Izlaz iz programa\n");
        if (scanf("%d", &choice) != 1)
        {
            printf("Pogresan unos!\n");
            break;
        }

        switch (choice)
        {
        case 1:
            if (Stack(&head) != 0)
            {
				printf("Izlaz iz programa\n");
				zatvori(&head);
                return -1;
            };
            break;
        case 2:
            if (Queue(&qhead) != 0)
            {
				printf("Izlaz iz programa\n");
                zatvoriQ(&qhead);
				return -1;
            };
            break;
        case 3:
            break;
        default:
            printf("Pogresan unos\n");
            break;
        }
    }

    zatvori(&head);
    zatvoriQ(&qhead);

    printf("Izlaz iz programa\n");
    return 0;
}

int Stack(Position p)
{
    int max = 0;
    while (max < 4 || max > 50)
    {
        printf("Unesite max broj elemenata na stogu (4-50): ");
        if (scanf("%d", &max) != 1) { printf("Pogresan unos\n"); continue; }
        if (max < 4 || max > 50) printf("Pogresan unos\n");
    }

    int choice = 0;
    while (choice != 3)
    {
        printf("\n1. Push\n2. Pop\n3. Povratak u prethodni izbornik\n");
        if (scanf("%d", &choice) != 1) { printf("Pogresan unos\n"); continue; }

        switch (choice)
        {
        case 1:
            if (Push(p, max) != 0)
            {
				return -1;
            };
            PrintList(p);
            break;
        case 2:
            Pop(p);
            PrintList(p);
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

int Push(Position p, int max)
{
    if (Count(p) >= max)
    {
        printf("Stog je pun.\n");
        return -1;
    }

    Position q = (Position)malloc(sizeof(Cvor));
    if (!q)
    {
        printf("Greska u alokaciji.\n");
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
    if (!p->Next)
    {
        printf("Stog je prazan.\n");
        return -1;
    }

    Position q = p->Next;
    p->Next = q->Next;
    printf("Pop: %d\n", q->El);
    free(q);
    return 0;
}

int Count(Position p)
{
    int count = 0;
    while (p->Next)
    {
        count++;
        p = p->Next;
    }
    return count;
}

int PrintList(Position p)
{
    if (!p->Next)
    {
        printf("Stog je prazan.\n");
        return 0;
    }
    printf("Stog: ");
    p = p->Next;
    while (p)
    {
        printf("%d ", p->El);
        p = p->Next;
    }
    printf("\n");
    return 0;
}

int zatvori(Position p)
{
    Position tmp;
    while (p->Next)
    {
        tmp = p->Next;
        p->Next = tmp->Next;
        free(tmp);
    }
    return 0;
}

int Queue(QPosition p)
{
    int choice = 0;
    while (choice != 3)
    {
        printf("\n1. Enqueue\n2. Dequeue\n3. Povratak u prethodni izbornik\n");
        if (scanf("%d", &choice) != 1) { printf("Pogresan unos\n"); continue; }

        switch (choice)
        {
        case 1:
            if (Enqueue(p) != 0)
            {
				return -1;
            };
            PrintListQ(p);
            break;
        case 2:
            Dequeue(p);
            PrintListQ(p);
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

int Enqueue(QPosition p)
{
    QPosition q = (QPosition)malloc(sizeof(QCvor));
    if (!q)
    {
        printf("Greska u alokaciji.\n");
        return -1;
    }

    q->El = rand() % 91 + 10;
    q->Prioritet = rand() % 5 + 1;
    q->Next = NULL;

    QPosition temp = p;
    while (temp->Next && temp->Next->Prioritet >= q->Prioritet)
        temp = temp->Next;

    q->Next = temp->Next;
    temp->Next = q;

    printf("Enqueue: %d (Prioritet: %d)\n", q->El, q->Prioritet);
    return 0;
}

int Dequeue(QPosition p)
{
    if (!p->Next)
    {
        printf("Red je prazan.\n");
        return -1;
    }

    QPosition q = p->Next;
    p->Next = q->Next;
    printf("Dequeue: %d (Prioritet: %d)\n", q->El, q->Prioritet);
    free(q);
    return 0;
}

int PrintListQ(QPosition p)
{
    if (!p->Next)
    {
        printf("Red je prazan.\n");
        return 0;
    }

    printf("Red: ");
    p = p->Next;
    while (p)
    {
        printf("%d(p%d) ", p->El, p->Prioritet);
        p = p->Next;
    }
    printf("\n");
    return 0;
}

int zatvoriQ(QPosition p)
{
    QPosition tmp;
    while (p->Next)
    {
        tmp = p->Next;
        p->Next = tmp->Next;
        free(tmp);
    }
    return 0;
}
