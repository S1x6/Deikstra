#define _CRT_SECURE_NO_WARNINGS
#include "subsystem.h"

int ** makeEmptyTable(int vert);

int ** makeAdjacencyTable(FILE * fin, FILE * fout, int vert, int edge) {
	int ** table = makeEmptyTable(vert);
	int ver1, ver2;
	long long w;
	long long c = 0;
	while (fscanf(fin, "%d %d %lld", &ver1, &ver2, &w) == 3)
	{
		if (ver1 < 0 || ver2 < 0 || ver1 > vert || ver2 > vert)
		{
			fprintf(fout, "bad vertex");
			return NULL;
		}
		if (c > edge)
		{
			fprintf(fout, "bad number of lines");
			return NULL;
		}
		if (w < 0 || w > INT_MAX)
		{
			fprintf(fout, "bad length");
			return NULL;
		}
		c++;
		table[ver1-1][ver2-1] = (int)w;
		table[ver2-1][ver1-1] = (int)w;
	}
	return table;
}

int ** makeEmptyTable(int vert)
{
	int i = 0, j;
	int ** table = malloc(vert * sizeof(int*));
	for (; i < vert; i++) {
		table[i] = malloc(vert * sizeof(int));
		j = 0;
		for (; j < vert; j++) {
			table[i][j] = NO_PATH;
		}
	}
	return table;
}

long long * initDistArray(int vert, int f) {
	int i = 0;
	long long * a = malloc(sizeof(long long) * vert);
	for (; i < vert; i++) {
		a[i] = INFINITY;
	}
	a[f] = 0;
	return a;
}

int findIdxOfMinPos(long long * a, int size, char * status) {
	int i = 0, idx = -1;
	long long min = ((long long)INT_MAX) + 1;
	for (; i < size; i++)
	{
		if (min > a[i] && a[i] >= 0 && status[i] == 0) {
			min = a[i];
			idx = i;
		}
	}
	return idx;
}

void findMinPaths(FILE * fout, long long * dist, int ** t, int vert_num, char * status, char * overflow, int iter) {
	int minIdx = findIdxOfMinPos(dist, vert_num, status);
	int i = 0;
	int isValidPath = 0;
	for (; i < vert_num && minIdx != -1; i++) {
		if (t[minIdx][i] != NO_PATH && status[i] != -1) {
			isValidPath = 1;
			if (dist[i] == INFINITY) {
				long long big = (long long)t[minIdx][i] + (long long)dist[minIdx];
				if (big > INT_MAX)
					overflow[i] = 1;
				dist[i] = big;
			}
			else if (dist[i] > t[minIdx][i] + dist[minIdx]) {
				long long big = (long long)t[minIdx][i] + (long long)dist[minIdx];
				if (big > INT_MAX)
					overflow[i] = 1;
				dist[i] = big;
			}
		}
	}
	status[minIdx] = -1;
	if (iter == vert_num)
		return;
	findMinPaths(fout, dist, t, vert_num, status, overflow, iter + 1);
}


void printDist(FILE * fout, long long * dist, int vert_num, char * overflow)
{ 
	int i = 0;
	for (; i < vert_num; i++) {
		if (overflow[i] == 1)
			fprintf(fout, "INT_MAX+ ");
		else if (dist[i] == INFINITY)
			fprintf(fout, "oo ");
		else fprintf(fout, "%lld ", dist[i]);
	}
	fprintf(fout, "\n");
}
void printPath(FILE * fout, int ** matrix, long long * dist, int s, int f, int vert_num, char * overflow)
{
	int n = f;
	if (dist[n] == INFINITY) {
		fprintf(fout, "no path");
		return;
	}
	char isThereMoreThanOnePath = 0;
	while (n != s) {
		int i = 0;
		int n_tmp = n; 
		char didWrite = 0;
		if (isThereMoreThanOnePath != 2)
			isThereMoreThanOnePath = 0;
		for (; i < vert_num; i++)
		{
			if (matrix[i][n] != NO_PATH && dist[n] == (long long)matrix[i][n] + dist[i])
			{
				isThereMoreThanOnePath++;
				if (overflow[f] == 1 && isThereMoreThanOnePath > 1) {
					fprintf(fout, "overflow");
					return;
				}
				if (!didWrite)
					n_tmp = i;
				didWrite = 1;
			}
		}
		fprintf(fout, "%d ", n + 1);
		n = n_tmp;
	}
	fprintf(fout, "%d ", s + 1);
}

