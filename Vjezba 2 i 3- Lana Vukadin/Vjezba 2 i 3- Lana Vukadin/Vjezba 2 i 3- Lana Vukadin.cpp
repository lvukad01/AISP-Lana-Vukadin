
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
//a) dinamièki dodaje novi element na poèetak liste,
//b) ispisuje listu,
//c) dinamièki dodaje novi element na kraj liste,
//d) pronalazi element u listi(po prezimenu),
//e) briše odreðeni element iz liste.

//Prethodnom zadatku dodati funkcije :
//a) dinamièki dodaje novi element iza odreðenog elementa,
//b) dinamièki dodaje novi element ispred odreðenog elementa,
//c) sortira listu po prezimenima osoba,
//d) upisuje listu u datoteku,
//e) èita listu iz datoteke.
struct Osoba;
typedef struct Osoba* Pozicija;
typedef struct Osoba
{
	char ime[100], prezime[100];
	int god_rod;
	Pozicija Next;
};
int unos(Pozicija);
int ispis(Pozicija);
int unos_kraj(Pozicija);
Pozicija trazi(Pozicija);
int brisi(Pozicija);

Pozicija trazip(Pozicija);
int unos_iza(Pozicija);
int unos_ispred(Pozicija);
int sort(Pozicija);
int write(Pozicija);
int read(Pozicija);
int zatvori(Pozicija);
int main()
{
	Osoba head;
	head.Next = NULL;
	int izbor = 0;
	printf("\nunesite broj za radnju koju zelite odraditi:\n1. dinamièki dodati novi element na poèetak liste\n2. ispis liste\n3. dinamièki dodajati novi element na kraj liste,\n4. pronalazak elementa u listi(po prezimenu),\n5. brisanje odreðenog element iz liste\n6. dinamièki dodaje novi element iza odreðenog elementa\n7.dinamièki dodaje novi element ispred odreðenog elementa\n8. sortira listu po prezimenima osoba\n9. upisuje listu u datoteku\n10.èita listu iz datoteke.\n11.kraj programa\n");

	while (izbor != 11)
	{
		scanf("%d", &izbor);
		switch (izbor)
		{
		case 1:
			unos(&head);
			break;
		case 2:
			ispis(head.Next);
			break;
		case 3:
			unos_kraj(&head);
			break;
		case 4:
		{
			Pozicija p = trazi(head.Next);
			if (p != NULL)
			{
				printf("\n %s %s %d.", p->ime, p->prezime, p->god_rod);

			}
			else
			{
				printf("nema");
			}
			break;
		}
		case 5:
			brisi(&head);
			break;
		case 6:
			unos_iza(&head);
			break;
		case 7:
			unos_ispred(&head);
			break;
		case 8:
			sort(&head);
			break;
		case 9:
			write(head.Next);
			break;
		case 10:
			read(&head);
			break;
		case 11:
			zatvori(&head);
			break;

		default:
			printf("pogresan unos\n");
			break;
		}
	}

	return 0;

}
int unos(Pozicija p)
{
	Pozicija q = (Pozicija)malloc(sizeof(Osoba));

	if (q == NULL)
	{
		printf("greska u alokaciji");
		return -1;
	}
	else
	{
		printf("upisite ime prezime i godinu rodj\n");
		scanf("%s %s %d", q->ime, q->prezime, &q->god_rod);
		q->Next = p->Next;
		p->Next = q;
	}
	return 0;
}
int ispis(Pozicija a)
{

	if (a == NULL)
	{
		printf("prazno");
	}
	else
	{
		while (a != NULL)
		{
			printf(" %s %s %d.\n", a->ime, a->prezime, a->god_rod);
			a = a->Next;
		}

	}
	return 0;
}
int unos_kraj(Pozicija p)
{
	while (p->Next != 0)
	{
		p = p->Next;
	}
	unos(p);
	return 0;
}
Pozicija trazi(Pozicija p)
{
	char a[100] = { 0 };
	printf("\nUpisite prezime osobe\n");
	scanf(" %s", a);
	while (p != NULL)
	{

		if (strcmp(a, p->prezime) == 0)
		{
			return p;
		}



		p = p->Next;
	}

	return NULL;
}
int brisi(Pozicija p)
{
	char a[100] = { 0 };
	printf("\nUpisite prezime osobe koju zelite izbrisati\n");
	scanf(" %s", a);
	Pozicija q = p;
	while (p != NULL)
	{
		if (strcmp(a, p->Next->prezime) == 0)
		{
			q = p->Next->Next;
			free(p->Next);
			p->Next = q;
			return 0;
		}
		p = p->Next;
	}
	return 0;
}
int unos_iza(Pozicija p)
{
	Pozicija q = trazi(p);
	if (q == NULL)
	{
		printf("osoba nije pronadjena");
		return 0;
	}
	else
	{
		unos(q);
	}

}
Pozicija trazip(Pozicija p)
{
	char a[100] = { 0 };
	printf("\nUpisite prezime osobe\n");
	scanf(" %s", a);
	while (p != NULL)
	{

		if (strcmp(a, p->Next->prezime) == 0)
		{
			return p;
		}

		p = p->Next;
	}

	return NULL;
}
int unos_ispred(Pozicija p)
{
	Pozicija q = trazip(p);
	if (q == NULL)
	{
		printf("osoba nije pronadjena");
		return 0;
	}
	else
	{
		unos(q);
	}

}
int sort(Pozicija p)
{
	Pozicija q = (Pozicija)malloc(sizeof(Osoba));
	Pozicija temp = p;


	printf("upisite ime prezime i godinu rodj\n");
	scanf("%s %s %d", q->ime, q->prezime, &q->god_rod);
	q->Next = NULL;
	if (p->Next == NULL)
	{
		p->Next = q;
		return 0;
	}
	while (p->Next != NULL)
	{
		if (strcmp(p->Next->prezime, q->prezime) > 0)
		{
			temp = p->Next;
			p->Next = q;
			q->Next = temp;
			return 0;
		}
		p = p->Next;
	}



	return 0;
}
int write(Pozicija p)
{
	FILE* dat = fopen("vjezba23.txt", "w");
	if (p == NULL)
	{
		printf("prazno");
	}
	else
	{
		while (p != NULL)
		{
			fprintf(dat," %s %s %d\n", p->ime, p->prezime, p->god_rod);
			p= p->Next;
		}

	}
	fclose(dat);
	return 0;
}
int read(Pozicija p)
{
	FILE* dat = fopen("vjezba23.txt", "r");
	if (dat == NULL)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	Pozicija q = NULL;

	while (1)
	{
		q = (Pozicija)malloc(sizeof(Osoba));
		if (q == NULL)
		{
			printf("Greska u alokaciji memorije!\n");
			break;
		}

		
		if (fscanf(dat, "%s %s %d", q->ime, q->prezime, &q->god_rod) != 3)
		{
			free(q);
			break;
		}

		q->Next = NULL;
		p->Next = q;
		p = q;       
	}

	fclose(dat);
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
