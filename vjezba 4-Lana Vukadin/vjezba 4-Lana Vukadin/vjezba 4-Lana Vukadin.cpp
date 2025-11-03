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
int zbroj(Pozicija, Pozicija,Pozicija);
int mnozi(Pozicija, Pozicija, Pozicija);

int main()
{
    Polinom p,q,s,z;
    p.Next = NULL;
    q.Next = NULL;
    s.Next = NULL;
    z.Next = NULL;
    read(&p);
    read(&q);
    zbroj(p.Next,q.Next,&s);
    mnozi(p.Next, q.Next, &z);
    printf("Polinom 1:\n");
    ispis(p.Next);
    printf("Polinom 2:\n");
    ispis(q.Next);
    printf("Zbroj:\n");
    ispis(s.Next);
    printf("Umnozak:\n");
    ispis(z.Next);
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
        printf("greska u citanju");
        return -1;
    }

    while (1)
    {
        q = (Pozicija)malloc(sizeof(Polinom));
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
    return 0;
}

int ispis(Pozicija p)
{

    while (p->Next!= NULL)
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
int zbroj(Pozicija p, Pozicija q,Pozicija s)
{
    Pozicija i;
    i = s;
 
    while (p != NULL && q != NULL)
    {
        i = (Pozicija)malloc(sizeof(Polinom));
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
            i->koeficijent = q->koeficijent;
            i->exponent = q->exponent;
            q = q->Next;
            i->Next = NULL;
            s->Next = i;
            s = s->Next;
        }
    }
    else if (q == NULL && p!= NULL)
    {
        while (q != NULL)
        {
            i = (Pozicija)malloc(sizeof(Polinom));
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
        for (Pozicija q1= q; q1 != NULL; q1 = q1->Next)
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
