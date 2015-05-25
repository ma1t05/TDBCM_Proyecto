
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

int *MST_to_HC(int n,int *mst) {
  int *HC;
  int p,i;
  int cont = 0;
  i = 0;
  p = mst[i];
  while (p != -1 && cont < n) {
    i = p;
    p = mst[i];
    cont++;
  }
  if (cont == n) return NULL;

  p = i;
  HC = new int[n];
  cont = 0;

  HC[cont++] = p;
  i = 0;
  while (p != -1) {
    for (;i < n;i++) {
      if (mst[i] == p) {
	HC[cont++] = i;
	p = i;
	i = -1; /* -1 */
      }
    }
    i = p + 1;
    p = mst[p];
  }
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
