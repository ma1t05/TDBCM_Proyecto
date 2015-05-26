
#include "MST.h"
#include "TSPMO.h"
#include "BiObjetivo_TSP.h"

int main_exhaustivo (int argc,char** argv) {
  int n,p;
  double ***C;
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

int *Christofides_heuristic(Instancia *I) {
  int *mst;
  bool *is_odd;
  int *PM,*HC;
  mst = primMST(I->n,I->p,I->C);
  is_odd = odd_nodes_of_MST(I->n,mst);
  PM = perfect_matching(is_odd,I);
  HC = NULL; /* Pendiente pasar de PM a HC */
  return HC;
}

int main (int argc, char** argv) {
  /* int a,b; 
     int *mst,*HC,*f; */
  int tope;
  Instancia *I;
  pareto_front *PF;
  solution *ND,*next;
  tope = (argc > 1 ? atoi(argv[1]) : 10);
  cout << "Comienza lectua de instancia" << endl;
  I = BiObjetivo_TSP_read("euclidA100.tsp","euclidB100.tsp");
  cout << "Termina lectuan de instancia n = " << I->n
       << " p = " << I->p << endl;
  cout << "Comienza algoritmo prime para obtener MST" << endl;
  for (int l = 6;l < tope;l++) {
    PF = TSPMO_exhaustive(l,I->p,I->C);
    ND = PF->begin;
    cout << "Comienza impresion de soluciones" << endl;
    while (ND != NULL) {
      next = ND->next;
      for (int k = 0;k < I->p;k++)
	cout << ND->f[k] << " ";
      cout << endl;
      delete[] ND->f;
      delete[] ND->sol;
      delete ND;
      ND = next;
    }
    delete PF;
    /*
    mst = primMST(l,I->p,I->C);
    for (int i = 0;i < l;i++)
      cout << mst[i] << " ";
    cout << endl;
    cout << "Comienza conversion de MST a HC" << endl;
    HC = MST_to_HC(l,mst);
    if (HC != NULL) {
      for (int i = 0;i < l;i++) {
	a = HC[i];
	b = HC[(i+1)%(l)];
	cout << a << "\t->\t" << b << "\t:";
	for (int k = 0;k < I->p;k++)
	  cout << "\t" << I->C[k][a][b];
	cout << endl;
      }
      cout << endl;
      cout << "Comienza evaluacion de HC" << endl;
      f = TSPMO_eval(l,I->p,I->C,HC);
      cout << "Se obtienen los siguientes valores" << endl;
      for (int k = 0;k < I->p;k++)
	cout << f[k] << " ";
      cout << endl;
  
      delete[] f;
      delete[] HC;
    }

    delete[] mst; */
  }
  delete_Instancia(I);
  return 0;
}
