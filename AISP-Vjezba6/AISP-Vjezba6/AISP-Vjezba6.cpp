#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//Napisati program koji pomoæu vezanih listi simulira rad :
//a) stoga,
//b) reda.
//Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 - 100.
struct Cvor;
typedef struct Cvor* Position;

typedef struct Cvor {
	int El;
	Position Next;
};
int Stack(Position);
int Queue(Position);
int Enqueue(Position);
int Dequeue(Position);
int Push(Position);
int Pop(Position);
int zatvori(Position);
int main()
{
	Cvor head;
	head.Next = NULL;
	int choice = 0;
	while (choice != 3)
	{
		printf("1. Stog\n2. Red\n3.Izlaz iz programa\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			Stack(&head);
			break;
		case 2:
			Queue(&head);
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
	printf("\n1.Push\n2.Pop\n3.Povratak u prethodni izbornik\n");
	int choice = 0;
	while (choice != 3)
	{
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			Push(p);
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
	if (q == NULL)
	{
		printf("Greska u alokaciji");
		return -1;
	}
	srand(time(NULL));
	q->El=rand()%90+10;
	q->Next = p->Next;
	p->Next = q;
	printf("Push: %d\n", q->El);
	return 0;
}
int Pop(Position p)
{
	Position q = p->Next;
	if (q == NULL)
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
	printf("\n1.Enqueue\n2.Dequeue\n3.Povratak u prethodni izbornik\n");
	int choice = 0;
	while (choice != 3)
	{
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			Enqueue(p);
			break;
		case 2:
			Dequeue(p);
			break;
		case 3:

			choice = 3;
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
	if (q == NULL)
	{
		printf("Greska u alokaciji");
		return -1;
	}
	srand(time(NULL));
	q->El = rand() % 90 + 10;
	while (p->Next != NULL)
	{
		p = p->Next;
	}
	q->Next = p->Next;
	p->Next = q;

	printf("Enqueue: %d\n", q->El);
	return 0;
}
int Dequeue(Position p)
{
	Position q = p->Next;
	if (q == NULL)
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
	Position q;
		while (p->Next != NULL)
		{

			q = p;
			while (q->Next->Next != NULL)
			{
				q = q->Next;
			}
			free(q->Next);
			q->Next = NULL;
		}
	return 0;

}