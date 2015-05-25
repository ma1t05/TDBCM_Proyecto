
#ifndef _TSPMO_H
#define _TSPMO_H

#include <algorithm>
#include <iostream>

using namespace std;

typedef struct solution solution;
typedef struct pareto_front pareto_front;

struct solution {
  int *f; /* evaluation */
  int *sol; /* solution */
  solution *next;
  solution *previous;
};

struct pareto_front {
  solution *begin;
  solution *end;
};

pareto_front *TSPMO_exhaustive(int n,int p,double ***C);
int *TSPMO_eval(int n,int p,double ***C,int *sol);
int is_dominated(int n,int *f1,int *f2);

#endif

/* eof */
