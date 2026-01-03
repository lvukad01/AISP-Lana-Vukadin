#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Polinom;
typedef struct Polinom* Pozicija;
typedef struct Polinom
{
    int koeficijent;
    int exponent;
    Pozicija Next;
} Polinom;

int read(Pozicija);
int ispis(Pozicija);
int zbroj(Pozicija, Pozicija, Pozicija);
int mnozi(Pozicija, Pozicija, Pozicija);
int zatvori(Pozicija);

int main()
{
    Polinom p, q, s, z;
    p.Next = NULL;
    q.Next = NULL;
    s.Next = NULL;
    z.Next = NULL;

    printf("Unesite ime datoteke za prvi polinom: ");
    if (read(&p) == -1)
    {
        zatvori(&p);
        return -1;
    }

    printf("Unesite ime datoteke za drugi polinom: ");
    if (read(&q) == -1)
    {
        zatvori(&p);
        zatvori(&q);
        return -1;
    }

    if (zbroj(p.Next, q.Next, &s) == -1)
    {
        zatvori(&p);
        zatvori(&q);
        zatvori(&s);
        return -1;
    }

    if (mnozi(p.Next, q.Next, &z) == -1)
    {
        zatvori(&p);
        zatvori(&q);
        zatvori(&s);
        zatvori(&z);
        return -1;
    }

    printf("Polinom 1:\n");
    if (ispis(p.Next) == -1)
    {
        zatvori(&p);
        return -1;
    }

    printf("Polinom 2:\n");
    if (ispis(q.Next) == -1)
    {
        zatvori(&p);
        zatvori(&q);
        return -1;
    }

    printf("Zbroj:\n");
    if (ispis(s.Next) == -1)
    {
        zatvori(&p);
        zatvori(&q);
        zatvori(&s);
        return -1;
    }

    printf("Umnozak:\n");
    if (ispis(z.Next) == -1)
    {
        zatvori(&p);
        zatvori(&q);
        zatvori(&s);
        zatvori(&z);
        return -1;
    }

    // Oslobaðanje memorije
    zatvori(&p);
    zatvori(&q);
    zatvori(&s);
    zatvori(&z);

    printf("Memorija je osloboðena, izlaz iz programa\n");
    return 0;
}

int read(Pozicija p)
{
    FILE* dat;
    Pozicija q, temp;
    char ime[100] = { 0 };

    if (scanf(" %s", ime) != 1)
    {
        printf("Pogresan unos imena datoteke!\n");
        return -1;
    }

    dat = fopen(ime, "r");
    if (!dat)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    while (1)
    {
        q = (Pozicija)malloc(sizeof(Polinom));
        if (!q)
        {
            printf("Greska u alokaciji memorije!\n");
            zatvori(p);
            fclose(dat);
            return -1;
        }

        if (fscanf(dat, "%d %d", &q->koeficijent, &q->exponent) != 2)
        {
            free(q);
            break;
        }

        temp = p;
        while (temp->Next != NULL && temp->Next->exponent > q->exponent)
            temp = temp->Next;

        q->Next = temp->Next;
        temp->Next = q;
    }

    fclose(dat);
    printf("Polinom uspjesno ucitan.\n");
    return 0;
}

int ispis(Pozicija p)
{
    if (!p)
    {
        printf("Prazno\n");
        return 0;
    }

    while (p->Next != NULL)
    {
        if (p->exponent == 1)
            printf(" %dx +", p->koeficijent);
        else if (p->exponent == 0)
            printf(" %d +", p->koeficijent);
        else
            printf(" %dx^%d +", p->koeficijent, p->exponent);

        p = p->Next;
    }
    p = p->Next;
	printf(" %d\n", p->koeficijent); 
    return 0;
}

int zbroj(Pozicija p, Pozicija q, Pozicija s)
{
    Pozicija i = s, novi;

    while (p != NULL || q != NULL)
    {
        novi = (Pozicija)malloc(sizeof(Polinom));
        if (!novi)
        {
            printf("Greska u alokaciji memorije!\n");
            zatvori(s);
            return -1;
        }
        novi->Next = NULL;

        if (p != NULL && (q == NULL || p->exponent > q->exponent))
        {
            novi->koeficijent = p->koeficijent;
            novi->exponent = p->exponent;
            p = p->Next;
        }
        else if (q != NULL && (p == NULL || q->exponent > p->exponent))
        {
            novi->koeficijent = q->koeficijent;
            novi->exponent = q->exponent;
            q = q->Next;
        }
        else
        {
            novi->koeficijent = p->koeficijent + q->koeficijent;
            novi->exponent = p->exponent;
            p = p->Next;
            q = q->Next;
        }

        i->Next = novi;
        i = i->Next;
    }

    return 0;
}

int mnozi(Pozicija p, Pozicija q, Pozicija s)
{
    s->Next = NULL;

    for (Pozicija p1 = p; p1 != NULL; p1 = p1->Next)
    {
        for (Pozicija q1 = q; q1 != NULL; q1 = q1->Next)
        {
            Pozicija novi = (Pozicija)malloc(sizeof(Polinom));
            if (!novi)
            {
                printf("Greska u alokaciji memorije!\n");
                zatvori(s);
                return -1;
            }

            novi->koeficijent = p1->koeficijent * q1->koeficijent;
            novi->exponent = p1->exponent + q1->exponent;
            novi->Next = NULL;

            Pozicija temp = s;
            while (temp->Next != NULL && temp->Next->exponent > novi->exponent)
                temp = temp->Next;

            if (temp->Next != NULL && temp->Next->exponent == novi->exponent)
            {
                temp->Next->koeficijent += novi->koeficijent;
                free(novi);
            }
            else
            {
                novi->Next = temp->Next;
                temp->Next = novi;
            }
        }
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

