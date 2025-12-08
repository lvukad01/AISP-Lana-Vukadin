#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

struct Cvor;
typedef struct Cvor* Pozicija;
 struct Cvor
{
	int broj;
	Pozicija Next;
};
 int read(Pozicija);
 int ispis(Pozicija);
 int Presjek(Pozicija, Pozicija, Pozicija);
 int Unija(Pozicija, Pozicija, Pozicija);
 int zatvori(Pozicija);
int main()
{
	Cvor L1, L2, U, P;
	L1.Next = L2.Next = U.Next = P.Next = NULL;
	if(read(&L1)==-1)
		return -1;
	printf("\nL1:");
	if(ispis(L1.Next)==-1)
		return -1;
	if(read(&L2)==-1)
		return -1;
	printf("\nL2:");
	if(ispis(L2.Next)==-1)
		return -1;
	if(Presjek(L1.Next, L2.Next,&P)==-1)
		return -1;
	printf("\nPresjek:");
	if(ispis(P.Next)==-1)
		return -1;
	if(Unija(L1.Next, L2.Next, &U)==-1)
		return -1;
	printf("\nUnija:");
	if(ispis(U.Next)==-1)
		return -1;
	zatvori(&L1);
	zatvori(&L2);
	zatvori(&P);
	zatvori(&U);
	printf("\nIzlaz iz programa");
	return 0;
	

}
int read(Pozicija p)
{
	Pozicija q;
	
	char ime[100] = {};

	printf("unesite ime datoteke\n");
	scanf("%s", ime);
	FILE* dat=fopen(ime,"r");
	if (dat == NULL)
	{
		printf("Greska u citanju datoteke");
		return -1;
	}

	while (!feof(dat))
	{
		q = (Pozicija)malloc(sizeof(Cvor));
		if (q == NULL)
		{
			printf("greska u alokaciji");
			return -1;
		}

		else
		{
			q->Next = NULL;

			Pozicija temp = p;
			fscanf(dat, "%d", &q->broj);
			while (temp->Next != NULL && temp->Next->broj < q->broj)
			{
				temp = temp->Next;
			}
			q->Next = temp->Next;
			temp->Next = q;
		}

		
	}
	fclose(dat);
	return 0;
}
int ispis(Pozicija p)
{
	if (p == NULL)
	{
		printf("lista je prazna");
		return -1;
	}
	printf("\n");
	while (p != NULL)
	{
		printf(" %d ", p->broj);
		p = p->Next;
	}
	printf("\n");
	return 0;
}
int Presjek(Pozicija p,Pozicija q,Pozicija z)
{
	Pozicija x = z;
	while (p != NULL && q != NULL)
	{

		if (p->broj < q->broj)
		{
			p = p->Next;
		}
		else if(p->broj > q->broj)
		{
			q = q->Next;

		}
		else
		{
			x = (Pozicija)malloc(sizeof(Cvor));
			if(x==NULL)
			{
				printf("greska u alokaciji");
				return -1;
			}
			x->broj = p->broj;
			x->Next = NULL;
			z->Next = x;
			p = p->Next;
			q = q->Next;
			z = x;
		}
	}
	
	return 0;
}
int Unija(Pozicija p, Pozicija q, Pozicija z)
{
	Pozicija x = z;
	while (p != NULL && q != NULL)
	{
		x = (Pozicija)malloc(sizeof(Cvor));
		if (x == NULL)
		{
			printf("greska u alokaciji");
			return -1;
		}
		if (p->broj < q->broj)
		{
			x->broj = p->broj;
			x->Next = NULL;
			z->Next = x;
			p = p->Next;
			z = x;
		}
		else if (p->broj > q->broj)
		{
			x->broj = q->broj;
			x->Next = NULL;
			z->Next = x;
			q = q->Next;
			z = x;

		}
		else
		{

			x->broj = p->broj;
			x->Next = NULL;
			z->Next = x;
			p = p->Next;
			q = q->Next;
			z = x;
		}
	}
	if(p!=NULL)
	{
		while(p!=NULL)
		{
			x = (Pozicija)malloc(sizeof(Cvor));
			if (x == NULL)
			{
				printf("greska u alokaciji");
				return -1;
			}
			x->broj = p->broj;
			x->Next = NULL;
			z->Next = x;
			p = p->Next;
			z = x;
		}
	}
	else if (q != NULL)
	{
		while (q != NULL)
		{
			x = (Pozicija)malloc(sizeof(Cvor));
			if (x == NULL)
			{
				printf("greska u alokaciji");
				return -1;
			}
			x->broj = q->broj;
			x->Next = NULL;
			z->Next = x;
			q = q->Next;
			z = x;
		}
	}
	

	return 0;
}
int zatvori(Pozicija p)
{
	Pozicija q;
	if (p->Next == NULL)
	{
		printf("prazno");
	}
	else
	{
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
	}
	return 0;

}