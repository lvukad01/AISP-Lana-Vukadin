#define _CRT_SECURE_NO_WARNINGS
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

    if (read(&L1) == -1)
    {
        zatvori(&L1);
        return -1;
    }
    printf("\nL1:");
    if (ispis(L1.Next) == -1)
    {
        zatvori(&L1);
        return -1;
    }

    if (read(&L2) == -1)
    {
        zatvori(&L1);
        zatvori(&L2);
        return -1;
    }
    printf("\nL2:");
    if (ispis(L2.Next) == -1)
    {
        zatvori(&L1);
        zatvori(&L2);
        return -1;
    }

    if (Presjek(L1.Next, L2.Next, &P) == -1)
    {
        zatvori(&L1);
        zatvori(&L2);
        zatvori(&P);
        return -1;
    }
    printf("\nPresjek:");
    if (ispis(P.Next) == -1)
    {
        zatvori(&L1);
        zatvori(&L2);
        zatvori(&P);
        return -1;
    }

    if (Unija(L1.Next, L2.Next, &U) == -1)
    {
        zatvori(&L1);
        zatvori(&L2);
        zatvori(&P);
        zatvori(&U);
        return -1;
    }
    printf("\nUnija:");
    if (ispis(U.Next) == -1)
    {
        zatvori(&L1);
        zatvori(&L2);
        zatvori(&P);
        zatvori(&U);
        return -1;
    }

    zatvori(&L1);
    zatvori(&L2);
    zatvori(&P);
    zatvori(&U);

    printf("\nIzlaz iz programa\n");
    return 0;
}

int read(Pozicija p)
{
    Pozicija q, temp;
    char ime[100];

    printf("Unesite ime datoteke: ");
    if (scanf(" %s", ime) != 1)
    {
        printf("Pogresan unos imena datoteke!\n");
        return -1;
    }

    FILE* dat = fopen(ime, "r");
    if (!dat)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    int broj;
    while (fscanf(dat, "%d", &broj) == 1)
    {
        q = (Pozicija)malloc(sizeof(Cvor));
        if (!q)
        {
            printf("Greska u alokaciji memorije!\n");
            zatvori(p);
            fclose(dat);
            return -1;
        }
        q->broj = broj;
        q->Next = NULL;

        temp = p;
        while (temp->Next != NULL && temp->Next->broj < broj)
            temp = temp->Next;

        q->Next = temp->Next;
        temp->Next = q;
    }

    fclose(dat);
    return 0;
}

int ispis(Pozicija p)
{
    if (!p)
    {
        printf("Lista je prazna\n");
        return 0;
    }

    while (p != NULL)
    {
        printf("%d ", p->broj);
        p = p->Next;
    }
    printf("\n");
    return 0;
}

int Presjek(Pozicija p, Pozicija q, Pozicija z)
{
    Pozicija x = z;

    while (p != NULL && q != NULL)
    {
        if (p->broj < q->broj)
            p = p->Next;
        else if (p->broj > q->broj)
            q = q->Next;
        else
        {
            x = (Pozicija)malloc(sizeof(Cvor));
            if (!x)
            {
                printf("Greska u alokaciji!\n");
                zatvori(z);
                return -1;
            }
            x->broj = p->broj;
            x->Next = NULL;
            z->Next = x;
            z = x;
            p = p->Next;
            q = q->Next;
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
        if (!x)
        {
            printf("Greska u alokaciji!\n");
            zatvori(z);
            return -1;
        }

        if (p->broj < q->broj)
        {
            x->broj = p->broj;
            p = p->Next;
        }
        else if (p->broj > q->broj)
        {
            x->broj = q->broj;
            q = q->Next;
        }
        else
        {
            x->broj = p->broj;
            p = p->Next;
            q = q->Next;
        }

        x->Next = NULL;
        z->Next = x;
        z = x;
    }

    while (p != NULL)
    {
        x = (Pozicija)malloc(sizeof(Cvor));
        if (!x)
        {
            printf("Greska u alokaciji!\n");
            zatvori(z);
            return -1;
        }
        x->broj = p->broj;
        x->Next = NULL;
        z->Next = x;
        z = x;
        p = p->Next;
    }

    while (q != NULL)
    {
        x = (Pozicija)malloc(sizeof(Cvor));
        if (!x)
        {
            printf("Greska u alokaciji!\n");
            zatvori(z);
            return -1;
        }
        x->broj = q->broj;
        x->Next = NULL;
        z->Next = x;
        z = x;
        q = q->Next;
    }

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
