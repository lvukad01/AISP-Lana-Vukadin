// vjezba1-LanaVukadin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Napisati program koji prvo proèita koliko redaka ima datoteka, tj.koliko ima studenata zapisanih u
//datoteci.Nakon toga potrebno je dinamièki alocirati prostor za niz struktura studenata(ime, prezime,
//	bodovi) i uèitati iz datoteke sve zapise.Na ekran ispisati ime, prezime, apsolutni i relativni broj bodova.
//	Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
//	relatvan_br_bodova = br_bodova / max_br_bodova * 100
typedef struct Student
{
	char ime[100], prezime[100];
	int bodovi;
};
int br_redaka(char*);

int ocj(char*, Student*, int);
int main()
{
	char naziv[100] = "osobe.txt";
	int redak = 0;
	redak = br_redaka(naziv)-1;
	Student* studenti = (Student*)malloc(redak * sizeof(Student));
	int i = 0, suma = 0;
	float max_br = 0;
	ocj(naziv, studenti, redak);
	for (i = 0;i < redak;i++)
	{
		suma=suma+ studenti[i].bodovi;
	}
	printf("%d", suma);

	for (i = 0;i < redak;i++)
	{
		max_br = (float)studenti[i].bodovi /suma * 100;
		printf(" %s %s-  relativni broj: %f \t apsolutni broj: %d\n", studenti[i].ime, studenti[i].prezime, max_br, studenti[i].bodovi);
	}
	free(studenti);
	return 0;
}
int ocj(char* naziv, Student* studenti, int br)
{
	srand(time(NULL));
	FILE* dat = fopen(naziv, "r");
	if (dat == NULL)
	{

		printf("greska pri otvaranju datoteke");
		return -1;
	}
	int i = 0;
	for (i = 0;i < br;i++)
	{
		fscanf(dat, " %s %s", studenti[i].ime, studenti[i].prezime);
		studenti[i].bodovi = rand() % 101;
	}
	fclose(dat);
	return 0;
}
int br_redaka(char* naziv)
{
	char buffer[1024] = { 0 };
	int count = 0;
	FILE* dat = fopen(naziv, "r");
	if (dat == NULL)
	{

		printf("greska pri otvaranju datoteke");
		return -1;
	}
	while (!feof(dat))
	{
		fgets(buffer, 1024, dat);
		count++;
	}
	fclose(dat);
	return count;
}
