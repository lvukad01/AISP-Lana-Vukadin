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
int main()
{
	Cvor L1, L2, U, P;
	L1.Next = L2.Next = U.Next = P.Next = NULL;
	read(&L1);
	printf("\nL1:");
	ispis(L1.Next);
	read(&L2);
	printf("\nL2:");
	ispis(L2.Next);
	Presjek(L1.Next, L2.Next,&P);
	printf("\nPresjek:");
	ispis(P.Next);
	Unija(L1.Next, L2.Next, &U);
	printf("\nUnija:");
	ispis(U.Next);

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
		printf("Greska");
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