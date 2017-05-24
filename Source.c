#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>
#include "subsystem.h"

#define ERROR_WRONG_VERTEX_NUM 1
#define ERROR_WRONG_EDGE_NUM 2
#define ERROR_WRONG_LINES_NUM 3
#define ERROR_WRONG_START 4
#define ERROR_WRONG_FINISH 5

int checkInput(FILE * fout, int vert, int edge, int s, int f);

int main()
{
	int vert_num = -1, edge_num = -1, s = -1, f = -1;
	FILE * fin = fopen("in.txt", "r");
	FILE * fout = fopen("out.txt", "w");
	if (fscanf(fin, "%d", &vert_num) != 1) {
		printf("bad number of lines");
		fclose(fin);
		fclose(fout);
		return 0;
	}
	if (fscanf(fin, "%d %d", &s, &f) != 2) {
		printf("bad number of lines"); //?
		fclose(fin);
		fclose(fout);
		return 0;
	}
	if (fscanf(fin, "%d", &edge_num) != 1) {
		printf("bad number of lines");
		fclose(fin);
		fclose(fout);
		return 0;
	}
	if (checkInput(fout, vert_num, edge_num, f, s)) {
		fclose(fin);
		fclose(fout);
		return 0;
	}
	
	int ** t = makeAdjacencyTable(fin, fout, vert_num, edge_num);
	if (t == NULL)
		return 0;
	long long * dist = initDistArray(vert_num, s-1);
	char * status = (char *)calloc(vert_num,sizeof(char));
	char * overflow = (char*)calloc(vert_num,(sizeof(char)));
	findMinPaths(fout, dist, t, vert_num, status, overflow, 0);
	printDist(fout, dist, vert_num, overflow);
	printPath(fout, t, dist, s-1, f-1, vert_num, overflow);
	return 0;
}

int checkInput(FILE * fout, int vert, int edge, int s, int f)
{
	if (vert < 0 || vert > 5000) {
		fprintf(fout, "bad number of vertices");
		return ERROR_WRONG_VERTEX_NUM;
	}
	if (edge < 0 || edge > vert*(vert + 1) / 2) {
		fprintf(fout, "bad number of edges");
		return ERROR_WRONG_EDGE_NUM;
	}
	if (s < 1 || s > vert) {
		fprintf(fout, "bad vertex");
		return ERROR_WRONG_START;
	}
	if (f < 1 || f > vert) {
		fprintf(fout, "bad vertex");
		return ERROR_WRONG_FINISH;
	}
	
	return 0;
}