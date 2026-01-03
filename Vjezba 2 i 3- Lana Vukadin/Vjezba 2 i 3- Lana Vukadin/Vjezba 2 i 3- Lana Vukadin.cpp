#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Osoba;
typedef struct Osoba* Pozicija;
typedef struct Osoba
{
    char ime[100], prezime[100];
    int god_rod;
    Pozicija Next;
} Osoba;

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

    while (izbor != 11)
    {
        printf("\nunesite broj za radnju koju zelite odraditi:\n"
            "1. dinamièki dodati novi element na poèetak liste\n"
            "2. ispis liste\n"
            "3. dinamièki dodajati novi element na kraj liste,\n"
            "4. pronalazak elementa u listi(po prezimenu),\n"
            "5. brisanje odreðenog element iz liste\n"
            "6. dinamièki dodaje novi element iza odreðenog elementa\n"
            "7. dinamièki dodaje novi element ispred odreðenog elementa\n"
            "8. sortira listu po prezimenima osoba\n"
            "9. upisuje listu u datoteku\n"
            "10. èita listu iz datoteke\n"
            "11. kraj programa\n");

        scanf("%d", &izbor);
        switch (izbor)
        {
        case 1:
            if (unos(&head) != 0)
            {
                zatvori(&head);
                return -1;
            }
            printf("Osoba je uspješno unesena u listu na poèetak.\n");
            break;
        case 2:
            if (ispis(head.Next) != 0)
            {
                zatvori(&head);
                return -1;
            }
            break;
        case 3:
            if (unos_kraj(&head) != 0)
            {
                zatvori(&head);
                return -1;
            }
            printf("Osoba je uspješno unesena u listu na kraj.\n");
            break;
        case 4:
        {
            Pozicija p = trazi(head.Next);
            if (p != NULL)
                printf("\n %s %s %d.\n", p->ime, p->prezime, p->god_rod);
            else
                printf("\nnema tog elementa u listi\n");
            break;
        }
        case 5:
            if (brisi(&head) != 0)
            {
                zatvori(&head);
                return -1;
            }
            printf("Osoba je uspješno izbrisana iz liste.\n");
            break;
        case 6:
            if (unos_iza(&head) != 0)
            {
                zatvori(&head);
                return -1;
            }
            printf("Osoba je uspješno dodana iza odabrane osobe.\n");
            break;
        case 7:
            if (unos_ispred(&head) != 0)
            {
                zatvori(&head);
                return -1;
            }
            printf("Osoba je uspješno dodana ispred odabrane osobe.\n");
            break;
        case 8:
            if (sort(&head) != 0)
            {
                zatvori(&head);
                return -1;
            }
            printf("Osoba je uspješno sortirano unesena po prezimenu.\n");
            break;
        case 9:
            if (write(head.Next) != 0)
            {
                zatvori(&head);
                return -1;
            }
            printf("Lista je uspješno upisana u datoteku.\n");
            break;
        case 10:
            if (read(&head) != 0)
            {
                zatvori(&head);
                return -1;
            }
            printf("Lista je uspješno uèitana iz datoteke.\n");
            break;
        case 11:
            zatvori(&head);
            printf("\nKraj programa.\n");
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
        printf("\ngreska u alokaciji\n");
        return -1;
    }

    printf("upisite ime prezime i godinu rodj: ");
    if (scanf("%s %s %d", q->ime, q->prezime, &q->god_rod) != 3)
    {
        printf("pogresan unos\n");
        free(q);
        return -1;
    }

    q->Next = p->Next;
    p->Next = q;
    return 0;
}

int ispis(Pozicija a)
{
    if (a == NULL)
    {
        printf("\nprazna lista\n");
        return -1;
    }

    while (a != NULL)
    {
        printf(" %s %s %d.\n", a->ime, a->prezime, a->god_rod);
        a = a->Next;
    }
    return 0;
}

int unos_kraj(Pozicija p)
{
    while (p->Next != NULL)
        p = p->Next;

    return unos(p);
}

Pozicija trazi(Pozicija p)
{
    char a[100] = { 0 };
    printf("\nUpisite prezime osobe: ");
    scanf("%s", a);

    while (p != NULL)
    {
        if (strcmp(a, p->prezime) == 0)
            return p;

        p = p->Next;
    }
    return NULL;
}

int brisi(Pozicija p)
{
    if (p == NULL || p->Next == NULL)
    {
        printf("\nprazna lista\n");
        return -1;
    }

    char a[100] = { 0 };
    printf("\nUpisite prezime osobe koju zelite izbrisati: ");
    scanf("%s", a);

    Pozicija temp;
    while (p->Next != NULL)
    {
        if (strcmp(a, p->Next->prezime) == 0)
        {
            temp = p->Next;
            p->Next = temp->Next;
            free(temp);
            return 0;
        }
        p = p->Next;
    }

    printf("Osoba nije pronadjena.\n");
    return -1;
}

int unos_iza(Pozicija p)
{
    Pozicija q = trazi(p->Next);
    if (q == NULL)
    {
        printf("\nosoba nije pronadjena\n");
        return -1;
    }
    return unos(q);
}

Pozicija trazip(Pozicija p)
{
    char a[100] = { 0 };
    printf("\nUpisite prezime osobe: ");
    scanf("%s", a);

    while (p->Next != NULL)
    {
        if (strcmp(a, p->Next->prezime) == 0)
            return p;

        p = p->Next;
    }
    return NULL;
}

int unos_ispred(Pozicija p)
{
    Pozicija q = trazip(p);
    if (q == NULL)
    {
        printf("\nosoba nije pronadjena\n");
        return -1;
    }
    return unos(q);
}

int sort(Pozicija p)
{
    Pozicija q = (Pozicija)malloc(sizeof(Osoba));
    if (q == NULL)
    {
        printf("\ngreska u alokaciji\n");
        return -1;
    }

    printf("\nupisite ime prezime i godinu rodj: ");
    if (scanf("%s %s %d", q->ime, q->prezime, &q->god_rod) != 3)
    {
        printf("pogresan unos\n");
        free(q);
        return -1;
    }

    q->Next = NULL;
    Pozicija temp = p;

    while (temp->Next != NULL && strcmp(temp->Next->prezime, q->prezime) < 0)
        temp = temp->Next;

    q->Next = temp->Next;
    temp->Next = q;

    return 0;
}

int write(Pozicija p)
{
    FILE* dat = fopen("vjezba23.txt", "w");
    if (!dat)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    while (p != NULL)
    {
        fprintf(dat, "%s %s %d\n", p->ime, p->prezime, p->god_rod);
        p = p->Next;
    }

    fclose(dat);
    return 0;
}

int read(Pozicija p)
{
    FILE* dat = fopen("vjezba23.txt", "r");
    if (!dat)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    zatvori(p);

    Pozicija q;
    while (1)
    {
        q = (Pozicija)malloc(sizeof(Osoba));
        if (!q)
        {
            printf("Greska u alokaciji memorije!\n");
            fclose(dat);
            return -1;
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
    Pozicija temp;
    while (p->Next != NULL)
    {
        temp = p->Next;
        p->Next = temp->Next;
        free(temp);
    }
    return 0;
}
