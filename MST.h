
#ifndef _MST_H
#define _MST_H

#include <cmath>
#include <iostream>
#include <limits.h>

using namespace std;
 
int *primMST(int n,int p /* # de ojbetivos */,int ***graph);
void printMST(int n,int *parent, int **graph);
int testMST();

#endif

/* eof */
