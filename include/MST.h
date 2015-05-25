
#ifndef _MST_H
#define _MST_H

#include <cmath>
#include <iostream>
#include <limits.h>

using namespace std;
 
int *primMST(int n,int p /* # de ojbetivos */,double ***graph);
void printMST(int n,int *parent, double **graph);
int testMST();
double ***read_instance (int *n,int *p);
void getMST(int *n,int *p,double ***graph);
void delete_graph(int n,int p,double ***graph);

#endif

/* eof */
