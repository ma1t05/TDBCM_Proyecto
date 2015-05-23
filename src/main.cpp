
#include "MST.h"
#include "TSPMO.h"

int main (int argc,char** argv) {
  int n,p;
  int ***C;
  solution *ND;
  pareto_front *PF;
  cout << "Comienza lectura de instancia" << endl;
  C = read_instance(&n,&p);
  cout << "Comienza creacion de Frente de pareto" << endl;
  PF = TSPMO_exhaustive(n,p,C);
  cout << "Termina TSP MO exhaustivo" << endl;
  ND = PF->begin;
  cout << "Comienza impresion de soluciones" << endl;
  while (ND != NULL) {
    for (int k = 0;k < p;k++)
      cout << ND->f[k] << " ";
    cout << "|";
    for (int i = 0;i < n;i++)
      cout << ND->sol[i] << "->";
    cout << endl;
    ND = ND->next;
  }
  return 0;
}
