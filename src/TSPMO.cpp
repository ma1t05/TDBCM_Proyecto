
#include "TSPMO.h"

int *TSPMO_eval(int n,int p,int ***C,int *sol);
int is_dominated(int n,int *f1,int *f2);

int *TSPMO_eval(int n,int p,int ***C,int *sol) {
  int a,b;
  int *f;
  f = new int[p];
  for (int k = 0;k < p;k++) f[k] = 0;
  for (int i = 0;i < n;i++) {
    a = sol[i];
    b = sol[(i+1)%n];
    for(int k = 0;k < p;k++) f[k] += C[k][a][b];
  }
  return f;
}

int is_dominated(int p,int *f1,int *f2) {
  /* return
    1 if f1 is dominated by f2
    -1 if f2 is dominated by f1
    0 otherwise */
  bool f1df2 = true,f2df1 = true;
  for (int k = 0;k < p;k++) {
    if (f1[k] < f2[k]) {
      f2df1 = false;
      if (!f1df2) break;
    } else if (f1[k] > f2[k]) {
      f1df2 = false;
      if (!f2df1) break;
    }
  }
  if (f1df2 && f2df1) {
    //cerr << "Soluciones iguales" << endl;
    return 1;
  }
  if (f1df2) return -1;
  if (f2df1) return 1;
  return 0;     
}

pareto_front *TSPMO_exhaustive(int n,int p,int ***C) {
  int cont;
  int *f,*sol;
  bool sol_is_nd;
  solution *new_s;
  solution *ND,*next;
  pareto_front *PF;
  
  //cout << "Entra a TSPMO" << endl;
  PF = new pareto_front;
  PF->begin = NULL;
  PF->end = NULL;
  //cout << "Crea frente de pareto" << endl;

  sol = new int[n];
  for (int i = 0;i < n;i++) sol[i] = i;
  //cout << "termina creacion de solucion inicial" << endl;
  cont = 0;
  do {
    //cout << "Comienza iteracion " << ++cont << endl;
    f = TSPMO_eval(n,p,C,sol);
    //cout << "Termina evaluacion de solucion" << endl;
    sol_is_nd = true;
    ND = PF->begin;
    while (ND != NULL && sol_is_nd) {
      next = ND->next;
      switch (is_dominated(p,f,ND->f)) {
      case -1:
	//cout << "Elimina solucion" << endl;
	if (ND->previous != NULL)
	  ND->previous->next=ND->next;
	else
	  PF->begin = ND->next;
	if (ND->next != NULL)
	  ND->next->previous=ND->previous;
	else
	  PF->end = ND->previous;
	delete[] ND->f;
	delete[] ND->sol;
	delete ND;
	break;
      case 1:
	//cout << "La solucion es dominada" << endl;
	sol_is_nd=false;
	delete[] f;
      case 0:
	break;
      }
      ND = next;
    }
    if (sol_is_nd) {
      //cout << "Agrega solucion al frente de pareto" << endl;
      new_s=new solution;
      new_s->f=f;
      new_s->sol=new int[n];
      for(int i=0;i<n;i++) {
	new_s->sol[i]=sol[i];
	cout << sol[i] << "->";
      }
      cout << endl;
      new_s->next=PF->begin;
      new_s->previous=NULL;
      if (PF->begin != NULL)
	PF->begin->previous=new_s;
      else
	PF->end = new_s;
      PF->begin=new_s;
    }
    //else cout << "No agrega solucion" << endl;
  } while (next_permutation(sol+1,sol+n));
  //cout << "Termina TSPMO exahustivo" << endl;
  return PF;
}
