#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <conio.h> //getch();

unsigned prioritate(char c)
{
	if (c == ')' || c == '(')
		return 0;
	else
		if (c == '*' || c == '/')
			return 1;
		else
			if (c == '+' || c == '-')
				return 2;
	return -1; // cel mai probabil este litera
}

char validare(char stfp[], int marime_fn)
{
	uint8_t c1 = 0, c2 = 0, c3 = 0; int poz;
	if (stfp[0] != '(' || stfp[strlen(stfp) - 1] != ')') // daca nu avem expresia fara paranteze la inceput si/sau la final, incorect
		return -1;
	else {
		if (prioritate(stfp[0]) == 2)		c2++;
		if (prioritate(stfp[0]) == 1)		c1++;
		if (prioritate(stfp[0]) != 0 && prioritate(stfp[0]) != 1 && prioritate(stfp[0]) != 2)		c3++;
		for (poz = 1; poz < marime_fn; poz++) {
			if (prioritate(stfp[poz]) == 2)		c2++;
			if (prioritate(stfp[poz]) == 1)		c1++;
			if (prioritate(stfp[poz]) != 0 && prioritate(stfp[poz]) != 1 && prioritate(stfp[poz]) != 2)		c3++;
			if (prioritate(stfp[poz - 1]) == prioritate(stfp[poz]) && prioritate(stfp[poz]) != 0 && strchr("(*/-+)", stfp[poz]) != 0 && strchr("(*/-+)", stfp[poz - 1]) != 0) // daca in expresie avem doi operatori unul langa altul diferiti de paranteze amandoi cu aceleasi prioritati, incorect
				return 0;
			else
			{
				if ((stfp[poz - 1] < 'a' || stfp[poz - 1] > 'z') && (stfp[poz] < 'a' || stfp[poz] > 'z') && prioritate(stfp[poz]) != 0 && prioritate(stfp[poz - 1]) != 0) // daca avem operatori unul langa altul ( diferiti de paranteze ), incorect
					return -3;
				else
					if (stfp[poz - 1] >= 'a' && stfp[poz - 1] <= 'z' && stfp[poz] >= 'a' && stfp[poz] <= 'z') // daca avem operanzi unul langa altul, incorect
						return -4;
					else
						if (strchr("(*/-+)abcdefghijklmnopqrstuvwxyz", stfp[poz - 1]) == 0 || strchr("(*/-+)abcdefghijklmnopqrtstuvwxyz", stfp[poz]) == 0)
							return -2;
						else
							if (stfp[poz - 1] == '(' && stfp[poz] == ')' || stfp[poz - 1] == ')' && stfp[poz] == '(')
								return -5;
			}
		}
		if ((c2 == 1 || c1 == 1) && c3 == 1)
			return -6;
	}
	return 1;
}

int main()
{

	printf("\n | Assignment 1 - introducere Problema 2 ( forma_poloneza ) | \n");
	printf(" | Stan Alexandu Daniel ; Subgrupa 03.1 IS Anul 1 | \n");
	printf("\n | Cerinta | 2. Se da o expresie aritmetica in forma normala si valorile fiecarui operand al expresiei. Sa se calculeze rezultatul expresiei aritmetice. (Vezi Curs 2)\n");
	printf("\n | INFO | Se introduce expresia aritmetica in forma normala, apoi algoritmul determina expresie aritmetica in forma poloneza, apoi calculeaza valoarea expresiei in forma poloneza!\n");
	printf("          Indiferent de ordinea operanzilor si litere ( a b c ; a c b ; h d p etc. ) problema se va executa!\n");
	printf("          Orice eroare legata de scriere a expresiei ( de exemplu: doua litere una langa alta, lipsa parantezelor la un capat sau la ambele capete, doi operatori unul langa altul etc. ) vor fi eliminate prin reintroducerea expresiei de la tastatura!\n");
	printf("          Cantitatile care nu corespund conditiilor ( sa fie litere mici si operatorii /, *, + si -) nu se introduc in stiva, fiind afisata o eroare de informare si reintroducandu-se expresia!\n\n");
	printf("          Atentie ca in expresie sa nu fie introduse in diferite locuri aceeasi litera ( de exemplu: (a*(b-c)+d/(a+f*g)-h) ), deoarece este posibil sa va dea un rezultat eronat!\n\n");
	printf("          In cazul in care se va ivi sa se faca o impartire la 0 a unei cantitati, se va afisa eroare runtime! \n\n");

	char* stfp = (char*)malloc(200 * sizeof(char) + 1);
	if (stfp == NULL) {
		printf(" | ERROR | Nu s-a putut aloca memorie dinamica pentru citirea formei initiale a expresiei introduse de la tastatura (stfp)! \n");
		exit(EXIT_FAILURE);
	}
	printf(" | INPUT | Introduceti expresia dorita pentru transformare in forma poloneza: ");
	scanf("%s", stfp);
	int marime_fn = strlen(stfp);
	while (validare(stfp, marime_fn) != 1) {
		char valid = validare(stfp, marime_fn);
		printf(" | ERROR | Expresia introdusa nu este corecta!\n");
		if (valid == -1)
			printf(" Avem expresia fara paranteze la inceput si / sau la final!\n");
		else
			if (valid == 0)
				printf(" In expresie sunt operatori unul langa altul ( diferiti de paranteze ), amandoi cu aleleasi prioritati!\n");
			else
				if (valid == -2)
					printf(" In expresie se afla si alte caractere in afara de litere englezesti mici si /, *, -, +!\n");
				else
					if (valid == -3)
						printf(" In expresie se afla operatori unul langa altul ( diferiti de paranteze )!\n");
					else
						if (valid == -4)
							printf(" In expresie se afla operanzi unul langa altul!\n");
						else
							if (valid == -5)
								printf(" In expresie se afla ( si ) sau/si ) si ( unul langa altul!\n");
							else
								if (valid == -6)
									printf(" In expresie se afla doar o litera si un semn (invalid)!\n");

		printf(" | INPUT | Introduceti din nou expresia scrisa corect: ");
		scanf("%s", stfp);
	}

	char* fp = (char*)malloc(200 * sizeof(char) + 1);
	if (fp == NULL) {
		printf(" | ERROR | Nu s-a putut aloca memorie dinamica pentru \"fp\"! \n");
		exit(EXIT_FAILURE);
	}

	char* stf = (char*)malloc(26 * sizeof(char) + 1);
	// 26 de litere in alfabetul englez ( abcdefghijklmnopqrstuvwxyz ) + terminator
	if (stf == NULL) {
		printf(" | ERROR | Nu s-a putut aloca memorie dinamica pentru \"stf\"! \n");
		exit(EXIT_FAILURE);
	}

	char* st = (char*)malloc(200 * sizeof(char) + 1);
	if (st == NULL) {
		printf(" | ERROR | Nu s-a putut aloca memorie dinamica pentru \"st\"! \n");
		exit(EXIT_FAILURE);
	}

	uint8_t ok = 0, okk = 0, nr_op_semn_pr2 = 0;
	int contor_semne = 0, nr_paran = 0, nr_paran2 = 0;
	int i = 0, index_st = -1, index_stf = -1, index_fp = -1, nrc = strlen(stfp), poz_index_st_i;

	while (i < nrc) {
		if (stfp[i] >= 'a' && stfp[i] <= 'z') {
			if (ok == 0)
				ok = 1;
			fp[++index_fp] = stfp[i];
			stf[++index_stf] = stfp[i];
		}
		else {
			okk = 0;
			if (prioritate(stfp[i]) == 2)
				nr_op_semn_pr2++;
			st[++index_st] = stfp[i];
			if (prioritate(stfp[i]) == 1)
				poz_index_st_i = i;
		}

		if (stfp[i] == '(') {
			nr_paran++; ok++;
		}

		if (ok == 2)
			nr_paran2 = 1;

		if (ok == 1 && prioritate(st[index_st]) == 2)
			okk = 1;

		if (i < strlen(stfp) - 1 && okk == 0 && prioritate(st[index_st]) == 1 && prioritate(stfp[i + 1]) != 0 && ok == 1 && stfp[poz_index_st_i + 1] >= 'a' && stfp[poz_index_st_i + 1] <= 'z') {
			if (fp[index_fp] < 'a' || fp[index_fp] > 'z') {
				fp[++index_fp] = stfp[poz_index_st_i + 1]; i++;
				if (stfp[poz_index_st_i] < 'a' || stfp[poz_index_st_i] > 'z')
				{
					fp[++index_fp] = stfp[poz_index_st_i];
					if (index_st != 0)
						index_st--;
				}
				stf[++index_stf] = stfp[i];

			}
			else {
				if (stfp[poz_index_st_i + 1] != fp[index_fp]) {
					fp[++index_fp] = stfp[poz_index_st_i + 1]; i++;
					stf[++index_stf] = stfp[i];
				}
				fp[++index_fp] = st[index_st];
				if (index_st != 0)
					index_st--;
			}
		}

		if (prioritate(stfp[i]) == 2 && ok == 0)
			contor_semne++;

		if (prioritate(st[index_st]) == 2 && ok == 0) {
			char vf_st = st[index_st--];
			while (prioritate(st[index_st]) == 1) {
				fp[++index_fp] = st[index_st--];
			}
			index_st++;
			st[index_st] = vf_st;
		}

		if (st[index_st] == ')') {
			ok = 0; okk = 0;
			while (index_st > 0 && st[--index_st] != '(') {
				fp[++index_fp] = st[index_st];
			}
			index_st--;
			if (index_st == 0 && (st[0] < 'a' || st[0]>'z') && prioritate(st[0]) == 1)
				fp[++index_fp] = st[index_st];
		}
		i++;
	}
	index_stf++;
	free(stfp);
	fp[index_fp + 1] = '\0';
	printf(" | OUTPUT | Transformatrea expresiei in fpp. este: %s \n", fp);

	double vect[201];
	int indexs;
	for (int i = 0; i < index_stf; i++) {
		printf(" | INPUT | Introduceti valoarea pentru %c= ", stf[i]);
		indexs = stf[i] - 'a';
		scanf("%lf", &vect[indexs]);
	}

	free(stf);
	free(st);

	double rez, val_1, val_2;
	char op; uint8_t ok2;
	int index_str = 0;
	double* str = (double*)malloc(201 * sizeof(double));
	// 26 de litere in alfabetul englez ( abcdefghijklmnopqrstuvwxyz ) + terminator de sir
	if (str == NULL) {
		printf(" | ERROR | Nu s-a putut aloca memorie dinamica pentru \"str\"! \n");
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (i < strlen(fp)) {
		if (fp[i] >= 'a' && fp[i] <= 'z')
			str[index_str++] = vect[fp[i] - 'a'];
		else {
			ok2 = 0;
			printf(" | INFO | Stiva la pozitia %d este: ", i);
			for (int j = 0; j < index_str; j++)
				printf("%lg ", str[j]);
			printf("\n");
			op = fp[i];
			val_1 = str[index_str - 2];
			val_2 = str[index_str - 1];
			if (op == '+' && fp[i + 1] == '-' && i < strlen(fp) - 1) {
				rez = -val_1 + val_2; fp[i + 1] = '+'; ok2 = 1;
			}
			else
				if (op == '+' && fp[i + 1] != '-' && i < strlen(fp) - 1) {
					rez = val_1 + val_2; ok2 = 1;
				}
			if (op == '-' && fp[i + 1] == '-' && i < strlen(fp) - 1) {
				rez = -val_1 - val_2; fp[i + 1] = '+'; ok2 = 1;
			}
			else
				if (op == '-' && fp[i + 1] != '-' && i < strlen(fp) - 1) {
					rez = val_1 - val_2; ok2 = 1;
				}
			if (op == '*') {
				rez = val_1 * val_2; ok2 = 1;
			}
			if (op == '/') {
				if (val_2 == 0) {
					printf(" | RUNTIME_ERROR | Nu s-a putut face impartirea la 0 : rez = val_1 /val_2 ! \n");
					exit(EXIT_FAILURE);
				}
				rez = val_1 / val_2; ok2 = 1;
			}
			if (ok2 == 1) {
				str[index_str - 2] = rez; index_str--;
			}
		}
		i++;
	}

	if (i == strlen(fp) && i >= 3 && index_str > 1) {
		op = fp[i - 1];
		if (ok2 == 0)	index_str--;
		val_1 = str[index_str - 1];
		val_2 = str[index_str];
		index_str++;
		if (op == '+')		rez = val_1 + val_2;
		if (op == '-')		rez = val_1 - val_2;
		if (op == '*')		rez = val_1 * val_2;
		if (op == '/') {
			if (val_2 == 0) {
				printf(" | RUNTIME_ERROR | Nu s-a putut face impartirea la 0 : rez = val_1 / val_2 ! \n");
				exit(EXIT_FAILURE);
			}
			rez = val_1 / val_2;
		}
		str[index_str - 2] = rez; index_str--;
	}
	else
		if (i == 1)		rez = str[index_str - 1];

	printf(" | INFO | Stiva la final este: ");
	for (int j = 0; j < index_str; j++)
		printf("%lg ", str[j]);
	printf("\n");

	printf(" | OUTPUT | Rezultatul expresiei aritmetice sub forma poloneza este: %lg \n", rez);
	printf(" The End! :) \n");

	free(str);
	free(fp);

	system("pause"); // getch();
	return 0;
}