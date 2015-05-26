
#ifndef _BIOBJETIVO_TSP
#define _BIOBJETIVO_TSP

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

typedef struct point point;
typedef struct Instancia Instancia;

struct point {
  int label;
  int x,y;
};

struct Instancia {
  int n;
  int p; /* 2 */
  point **coordenadas;
  double ***C;
};

double dist(point *a,point *b);
Instancia *BiObjetivo_TSP_read(string file_name1,string file_name2);
void delete_Instancia(Instancia *I);

#endif

/* eof */
