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
};

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
    int br = 0;
	printf("Unesite ime datoteke za prvi polinom: ");
    if(read(&p)==-1)
        return -1;
	printf("Unesite ime datoteke za drugi polinom: ");
    if(read(&q)==-1)
        return -1;
    if(zbroj(p.Next, q.Next, &s)==-1)
        return -1;
    if(mnozi(p.Next, q.Next, &z)==-1)
        return -1;
    printf("Polinom 1:\n");
    if(ispis(p.Next)==-1)
        return -1;
    printf("Polinom 2:\n");
    if(ispis(q.Next)==-1)
        return -1;
    printf("Zbroj:\n");
    if(ispis(s.Next)==-1)
        return -1;
    printf("Umnozak:\n");
    if(ispis(z.Next)==-1)
        return -1;
    
	zatvori(&p);
	zatvori(&q);
    printf("Memorija je osloboðena, izlaz iz programa\n");
    return 0;
}

int read(Pozicija p)
{
    FILE* dat;
    Pozicija q;
    Pozicija temp;
    char ime[100] = {};
    scanf(" %s", ime);

    dat = fopen(ime, "r");
    if (dat == NULL)
    {
        printf("greska u citanju datoteke");
        return -1;
    }

    while (1)
    {
        q = (Pozicija)malloc(sizeof(Polinom));
        if (q == NULL)
        {
            printf("\nGreska u alokaciji memorije\n");
            return -1;
        }
        if (fscanf(dat, "%d %d", &q->koeficijent, &q->exponent) != 2)
        {
            free(q);
            break;
        }

        temp = p;
        while (temp->Next != NULL && temp->Next->exponent > q->exponent)
        {
            temp = temp->Next;
        }
        q->Next = temp->Next;
        temp->Next = q;
    }

    fclose(dat);
    printf("\nPolinom uspješno ocitan\n");
    return 0;
}

int ispis(Pozicija p)
{
    if (p == NULL) {
        printf("Prazno\n");
        return 0;
    }

    while (p->Next != NULL)
    {
        if (p->exponent == 1)
        {
            printf(" %dx + ", p->koeficijent);
        }
        else if (p->exponent == 0)
        {
            printf(" %d + ", p->koeficijent);
        }
        else
        {
            printf(" %dx^%d + ", p->koeficijent, p->exponent);
        }
        p = p->Next;
    }
    if (p->exponent == 1)
    {
        printf(" %dx", p->koeficijent);
    }
    else if (p->exponent == 0)
    {
        printf(" %d ", p->koeficijent);
    }
    else
    {
        printf(" %dx^%d", p->koeficijent, p->exponent);
    }
    printf("\n");
    return 0;
}

int zbroj(Pozicija p, Pozicija q, Pozicija s)
{
    Pozicija i;
    i = s;

    while (p != NULL && q != NULL)
    {
        i = (Pozicija)malloc(sizeof(Polinom));
        if (i == NULL)
        {
            printf("Greska u alokaciji memorije");
            return -1;

        }
        if (p->exponent > q->exponent)
        {
            i->koeficijent = p->koeficijent;
            i->exponent = p->exponent;
            p = p->Next;
        }
        else if (p->exponent < q->exponent)
        {
            i->koeficijent = q->koeficijent;
            i->exponent = q->exponent;
            q = q->Next;
        }
        else
        {
            i->koeficijent = p->koeficijent + q->koeficijent;
            i->exponent = p->exponent;
            p = p->Next;
            q = q->Next;
        }
        i->Next = NULL;
        s->Next = i;
        s = s->Next;


    }
    if (p == NULL && q != NULL)
    {
        while (q != NULL)
        {
            i = (Pozicija)malloc(sizeof(Polinom));
            if (i == NULL)
            {
                printf("Greska u alokaciji memorije");
                return -1;
            }
            i->koeficijent = q->koeficijent;
            i->exponent = q->exponent;
            q = q->Next;
            i->Next = NULL;
            s->Next = i;
            s = s->Next;
        }
    }
    else if (q == NULL && p != NULL)
    {
        while (p != NULL)
        {
            i = (Pozicija)malloc(sizeof(Polinom));
            if (i == NULL)
            {
                printf("Greska u alokaciji memorije");
                return -1;
            }
            i->koeficijent = p->koeficijent;
            i->exponent = p->exponent;
            p = p->Next;
            i->Next = NULL;
            s->Next = i;
            s = s->Next;
        }
    }
    return 0;
}

int mnozi(Pozicija p, Pozicija q, Pozicija s)
{
    Pozicija i = s;
    i->Next = NULL;

    for (Pozicija p1 = p; p1 != NULL; p1 = p1->Next)
    {
        for (Pozicija q1 = q; q1 != NULL; q1 = q1->Next)
        {
            Pozicija novi = (Pozicija)malloc(sizeof(Polinom));
            novi->koeficijent = p1->koeficijent * q1->koeficijent;
            novi->exponent = p1->exponent + q1->exponent;
            novi->Next = NULL;

            Pozicija temp = i;
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
