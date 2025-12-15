
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//7. Napisati program koji pomoæu vezanih listi simulira rad :
//a) cirkularnog stoga(maksimalni broj elemenata na stogu definira korisnik kad se program
//pokrene),
//b) reda s prioritetom(prioritet može biti od 1 - 5 i generira se sluèajno, a veæi broj znaèi i veæi
//prioritet).
//Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 - 100
struct QCvor;
typedef struct QCvor* QPosition;

typedef struct QCvor {
	int El;         
	int Prioritet; 
	QPosition Next;
};
struct Cvor;
typedef struct Cvor* Position;

typedef struct Cvor {
	int El;
	Position Next;
};
int Stack(Position);
int Queue(QPosition);
int PrintList(Position, int);
int Enqueue(QPosition);
int Dequeue(QPosition);
int Push(Position, int);
int Pop(Position,int);
int Count(Position);
int zatvori(Position);
int ZatvoriQ(QPosition);
int CountQ(QPosition);
int PrintListQ(QPosition);

int main()
{
	Cvor head;
	QCvor qhead;
	qhead.Next = NULL;
	head.Next = NULL;
	srand(time(NULL));
	int choice = 0;
	while (choice != 3)
	{
		printf("1. Cirkularni stog\n2. Red s prioritetom\n3.Izlaz iz programa\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			Stack(&head);
			break;
		case 2:
			Queue(&qhead);
			break;
		case 3:
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
	int max = 0;
	while (max < 4 || max>50)
	{
		printf("Unesite max broj elemenata na stogu(4-50): ");
		scanf("%d", &max);
		if (max < 4 || max>50)
			printf("Pogresan unos\n");
	}
	int choice = 0;
	while (choice != 3)
	{
		printf("\n\n\n1.Push\n2.Pop\n3.Povratak u prethodni izbornik\n");

		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			Push(p, max);
			PrintList(p->Next, Count(p));
			break;
		case 2:
			Pop(p,max);
			PrintList(p->Next, Count(p));
			break;
		case 3:
			zatvori(p);
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
		return Count(p);
	}

	Position q = (Position)malloc(sizeof(struct Cvor));
	if (!q)
	{
		printf("Greska u alokaciji.\n");
		return Count(p);
	}

	q->El = rand() % 91 + 10;  
	q->Next = p->Next;         
	p->Next = q;

	printf("Push: %d.\n", q->El);  

	return 0;  
}



int Pop(Position P, int n)
{
	static Position last = NULL;
	Position tmp;

	if (P->Next != NULL)
	{

		tmp = P->Next;

		printf("\r\nPop: %d.", tmp->El);

		P->Next = tmp->Next;

		if (last == NULL && n > 1)
		{
			while (P->Next != tmp)
				P = P->Next;
			last = P;
		}

		last->Next = tmp->Next;

		free(tmp);
		n--;
		if (n == 0)
			last = NULL;
	}
	else
		printf("\r\Stog je prazan.");

	return n;
}

int PrintList(Position P, int n)
{

	printf("\r\n\r\nIspis liste\r\n", n);
	while (n > 0)
	{
		printf(" %d", P->El);
		P = P->Next;
		n--;
	}
	return 0;
}


int Queue(QPosition p)
{
	int choice = 0;
	while (choice != 3)
	{
		printf("\n\n\n1.Enqueue\n2.Dequeue\n3.Povratak u prethodni izbornik\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			Enqueue(p);
			PrintListQ(p->Next);
			break;
		case 2:
			Dequeue(p);
			PrintListQ(p->Next);
			break;
		case 3:

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
	if (q == NULL)
	{
		printf("Greska u alokaciji");
		return -1;
	}
	q->Prioritet = rand() % 5 + 1;
	q->El = rand() % 90 + 10;
	while (p->Next != NULL&&p->Next->Prioritet>=q->Prioritet)
	{
		p = p->Next;
	}
	q->Next = p->Next;
	p->Next = q;

	printf("Prioritet:%d\nEnqueue: %d\n",q->Prioritet, q->El);
	return 0;
}
int Dequeue(QPosition p)
{
	QPosition q = p->Next;
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

		q = p->Next;
		while (q->Next->Next != NULL)
		{
			q = q->Next;
		}
		free(q->Next);
		q->Next = NULL;
	}
	return 0;


}
int zatvoriQ(QPosition p)
{
	QPosition q;
	while (p->Next != NULL)
	{

		q = p->Next;
		while (q->Next->Next != NULL)
		{
			q = q->Next;
		}
		free(q->Next);
		q->Next = NULL;
	}
	return 0;

}
int Count(Position p)
{
	int count = 0;
	while (p->Next != NULL)
	{
		count++;
		p = p->Next;
	}
	return count;
}
int PrintListQ(QPosition P)
{

	printf("\r\n\r\nIspis liste\r\n");
	while (P != NULL)
	{
		printf(" %d", P->El);
		P = P->Next;
	}
	return 0;
}