#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include "flat.h"
#include "taxes.h"
using namespace std;


struct flatinf* flati = (struct flatinf*)calloc(1001, sizeof(struct flatinf));
struct resource* res1 = (struct resource*)calloc(10, sizeof(struct resource));
int flats, s_sum, Q;

struct allhome
{
	int m, year;
	long long int resi[15];
};

struct flathome
{
	int m, year;
	int num_flat;
	long long int resi_ind[15];
	int idflat;
};

struct sorthome
{
	int m, year, ipu, odpu, odn;
	int ipu_price, odn_price;
};

// qsort ��� ��������� allhome
int compare(const void* x1, const void* x2)
{
	struct allhome* ta = (struct allhome*)x1;
	struct allhome* tb = (struct allhome*)x2;
	if (ta->year - tb->year)
		return ta->year - tb->year;
	if (ta->year == tb->year && ta->m - tb->m)
		return ta->m - tb->m;
}

// qsort ��� ��������� flathome
int compare2(const void* x1, const void* x2)
{
	struct flathome* tf = (struct flathome*)x1;
	struct flathome* tk = (struct flathome*)x2;
	if (tf->num_flat - tk->num_flat)
		return tf->num_flat - tk->num_flat;
	else if (tf->year - tk->year)
		return tf->year - tk->year;
	else
		return tf->m - tk->m;
}

int main()
{
	// ���� ������ ����� ���������� �� ����� home.txt
	 numberFlatsInput();
	 allSquareInput();
	 flatsSquareInput();

	// ���� ������ ����� ���������� �� ����� text.txt
	 numberResourceInput();
	 resourceInput();

	// �������� ���� ������ �� ����� deltails.txt
	FILE* inf3 = fopen("details.txt", "r");
	int L, M;
	fscanf(inf3, "%d", &L);
	struct allhome* allh = (struct allhome*)calloc(L, sizeof(struct allhome));
	for (int i = 0; i < L; i++)
	{
		fscanf(inf3, "%d.%d", &allh[i].m, &allh[i].year);
		for (int j = 0; j < Q; j++)
		{
			fscanf(inf3, "%I64d", &allh[i].resi[j]);
		}
	}
	fscanf(inf3, "%d", &M);
	struct flathome* flath = (struct flathome*)calloc(M, sizeof(struct flathome));
	for (int i = 0; i < M; i++)
	{
		fscanf(inf3, "%d.%d", &flath[i].m, &flath[i].year);
		fscanf(inf3, "%d", &flath[i].num_flat);
		for (int j = 0; j < Q; j++)
		{
			fscanf(inf3, "%I64d", &flath[i].resi_ind[j]);
		}
	}
	fclose(inf3);

	// �������� ���� ������ �� ����� input.txt
	FILE* inf4 = fopen("input.txt", "r");
	int n, startm, starty, endm, endy;
	char name_res[15];
	fscanf(inf4, "%d", &n);
	fscanf(inf4, "%s", &name_res);
	fscanf(inf4, "%d.%d-%d.%d", &startm, &starty, &endm, &endy);
	fclose(inf4);

	/* C��������� ��������, ���������� ���������� � �����������
	*  � ���� � ��� � ������ �������� �� �����
	*/
	qsort(allh, L, sizeof(struct allhome), compare);
	qsort(flath, M, sizeof(struct flathome), compare2);

	int ipu(0), idresource(0), price(0), sum_ipu(0), odn(0), sum_odn(0);
	struct sorthome* shome = (struct sorthome*)calloc(M, sizeof(struct sorthome));

	// ������� ���� ������� n-�� �������� �� ��� �������� ��� ���������� ��� �� 1 ��������.
	double ss = (double)flati[n-1].sflat / (double)s_sum;

	// ������� ���������� ������� � ����.
	double citizens(0);
	for (int i = 0; i < flats; i++)
	{
		citizens += flati[i].ncitizen;
	}
	
	// ������� ���� ���������� ������� n-�� �������� �� ���������� ������� ���� ��� ���������� ��� �� 2 ��������.
	double cc = (double)flati[n - 1].ncitizen / citizens;
	
	// ����������� id ������������ �������.
	int key(0);
	for (int i = 0; i < Q; i++)
	{
		if (strcmp(res1[i].res, name_res) == 0)
		{
			idresource = i;
			price = res1[i].tarif;
			key = res1[i].k;
			break;
		}
	}
	
	// ���������� id ������� ���������� ���� � ������.
	int nachid(9);
	for (int i = 0; i < M; i++)
	{
		if (flath[i].m == startm && flath[i].year == starty)
		{
			nachid = i;
			break;
		}
	}

	// ���������� ����������� ��� � ������ �� ��� ��� n-�� �������� �� ������ �����
	int count(0);
	int nom(0), nfl(1);
	for (int i = 0; i < M; i++)
	{
		if (starty == flath[i].year && startm == flath[i].m && n == flath[i].num_flat)
		{
			shome[count].m = flath[i].m;
			shome[count].year = flath[i].year;
			if (i % L != 0)
			{
				shome[count].ipu = flath[i].resi_ind[idresource] - flath[i - 1].resi_ind[idresource];
			}	
			else
			{
				shome[count].ipu = 0;
			}
			ipu += shome[count].ipu;
			shome[count].ipu_price = shome[count].ipu * price;
			sum_ipu += shome[count].ipu_price;
			count++;
			if (starty == endy && startm == endm)
			{
				break;
			}
			startm++;
			if (startm > 12)
			{
				startm = 1;
				starty++;
			}
		}
	}

	// ���������� ����������� ���� �� ������ �����
	int number(0);
	for (int i = 0; i < L; i++)
	{
		if (allh[i].m == shome[number].m && allh[i].year == shome[number].year)
		{
			if (i != 0)
			{
				shome[number].odpu = allh[i].resi[idresource] - allh[i - 1].resi[idresource];
			}
			else
			{
				shome[number].odpu = 0;
			}
			number++;
		}
	}

	// ���������� ����������� ��� � ������ �� ��� �� ������ �����
	int str = nachid;
	int f(0);
	for (int i = 0; i < count; i++)
	{
		int ipu_sum_flats(0);
		if (str % L != 0)
		{
			for (int i = str; i < M; i += L)
			{
				ipu_sum_flats += flath[i].resi_ind[idresource] - flath[i - 1].resi_ind[idresource];
			}
			if (key == 0)
			{
				shome[f].odn = (shome[f].odpu - ipu_sum_flats) * ss;
			}
			else
			{
				shome[f].odn = (shome[f].odpu - ipu_sum_flats) * cc;
			}
			shome[f].odn_price = shome[f].odn * price;
			odn += shome[f].odn;
			sum_odn += shome[f].odn_price;
		}
		else
		{
			shome[f].odn = 0;
			shome[f].odn_price = 0;
		}
		str++;
		f++;
	}


	// ����� ���� �����������
	FILE* outf = fopen("answer.txt", "w");
	fprintf(outf, "%d %d %d %d\n", ipu, sum_ipu, odn, sum_odn);
	fprintf(outf, "%d\n", count);
	for (int i = 0; i < count; i++)
	{
		if (shome[i].m < 10)
		{
			fprintf(outf, "0%d.%d %d %d %d %d\n", shome[i].m, shome[i].year, shome[i].ipu, shome[i].ipu_price, shome[i].odn, shome[i].odn_price);
		}
		else
		{
			fprintf(outf, "%d.%d %d %d %d %d\n", shome[i].m, shome[i].year, shome[i].ipu, shome[i].ipu_price, shome[i].odn, shome[i].odn_price);
		}
	}

	fclose(outf);
	free(flati);
	free(res1);
	free(allh);
	free(flath);
	free(shome);
	return 0;
}