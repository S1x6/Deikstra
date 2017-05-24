#ifndef  _SUBSYSTEM_H
#define _SUBSYSTEM_H

#include <stdio.h>
#include <limits.h>
#include <malloc.h>

#define INFINITY -1
#define NO_PATH -2

int ** makeAdjacencyTable(FILE * fin, FILE * fout, int vert, int edge);
long long * initDistArray(int vert, int f);
int findIdxOfMinPos(long long * a, int size, char * status);
void findMinPaths(FILE * fout, long long * dist, int ** t, int vert_num, char * status, char* overflow, int iter);
void printDist(FILE * fout, long long * dist, int vert_num, char * overflow);
void printPath(FILE * fout, int ** matrix, long long * dist, int s, int f, int vert_num, char * overflow);
#endif // ! _SUBSYSTEM_H
