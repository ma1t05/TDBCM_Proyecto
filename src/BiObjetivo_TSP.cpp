
#include "BiObjetivo_TSP.h"

using namespace std;

Instancia *BiObjetivo_TSP_read(string file_name1,string file_name2) {
  string omit_line;
  Instancia *I;
  point *puntos;
  double ***C_kij;
  I = new Instancia;
  I->p = 2;
  I->coordenadas = new point*[2];
  
  ifstream TSP_file1(file_name1.c_str());
  getline(TSP_file1,omit_line); 
  getline(TSP_file1,omit_line);
  getline(TSP_file1,omit_line);
  getline(TSP_file1,omit_line,':');
  TSP_file1 >> I->n;
  getline(TSP_file1,omit_line);
  getline(TSP_file1,omit_line);
  getline(TSP_file1,omit_line);
  puntos = new point[I->n];
  
  for (int i = 0;i < I->n;i++)
    TSP_file1 >> puntos[i].label >> puntos[i].x >> puntos[i].y;
  I->coordenadas[0] = puntos;
  TSP_file1.close();

  ifstream TSP_file2(file_name2.c_str());
  getline(TSP_file2,omit_line); 
  getline(TSP_file2,omit_line);
  getline(TSP_file2,omit_line);
  getline(TSP_file2,omit_line,':');
  TSP_file2 >> I->n;
  getline(TSP_file2,omit_line);
  getline(TSP_file2,omit_line);
  getline(TSP_file2,omit_line);
  puntos = new point[I->n];
  for (int i = 0;i < I->n;i++)
    TSP_file2 >> puntos[i].label >> puntos[i].x >> puntos[i].y;
  I->coordenadas[1] = puntos;
  TSP_file2.close();

  C_kij = new double**[2];
  for (int k = 0;k < 2;k++) {
    C_kij[k] = new double*[I->n];
    for (int i = 0;i < I->n;i++)
      C_kij[k][i] = new double[I->n];
  }

  for (int k = 0;k < 2;k++) {
    puntos = I->coordenadas[k];
    for (int i = 0;i < I->n;i++) {
      C_kij[k][i][i] = 0.0;
      for (int j = i+1;j < I->n;j++) {
	C_kij[k][i][j] = dist(&(puntos[i]),&(puntos[j]));
	C_kij[k][j][i] = C_kij[k][i][j];
      }
    }
  }
  I->C = C_kij;

  return I;
}

double dist(point *a,point *b) {
  return sqrt((a->x - b->x)*(a->x - b->x)+(a->y - b->y)*(a->y - b->y));
}

void delete_Instancia(Instancia *I) {
  for (int k = 0;k < I->p;k++) {
    for (int i = 0;i < I->n;i++) {
      delete[] I->C[k][i];
    }
    delete[] I->C[k];
  }
  delete[] I->C;

  for(int k = 0;k < I->p;k++) {
    delete[] I->coordenadas[k];
  }
  delete[] I->coordenadas;

  delete I;
}
