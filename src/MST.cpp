// A C / C++ program for Prim's Minimum Spanning Tree (MST) algorithm.
// The program is for adjacency matrix representation of the graph
 
#include "MST.h"

// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int n,int *key, bool *mstSet)
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < n; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}
 
// A utility function to print the constructed MST stored in parent[]
void printMST(int n,int *parent, double **graph)
{
  cout << "Edge   Weight" << endl;
   for (int i = 1; i < n; i++)
     cout << parent[i] << i << graph[i][parent[i]] << endl;
}

int **normMST(int n,int p,double ***graph){
  int **G;
  G = new int*[n];
  for(int i = 0;i < n;i++)
    G[i] = new int[n];
  for(int i = 0;i < n;i++) {
    for(int j = 0;j < n;j++) {
      double sum = 0.0;
      for(int k = 0;k < p;k++) {
	sum += graph[k][i][j]*graph[k][i][j];
      }
      G[i][j] = sqrt(sum);
    }
  }
  return G;
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
int* primMST(int n,int p,double ***graph){
  int *parent; // Array to store constructed MST
  int *key;   // Key values used to pick minimum weight edge in cut
  bool *mstSet;  // To represent set of vertices not yet included in MST
  int **G;
  
  G = normMST(n,p,graph);
  parent = new int[n];
  key  = new int[n];
  mstSet = new bool[n];
 
  // Initialize all keys as INFINITE
  for (int i = 0; i < n; i++)
    key[i] = INT_MAX, mstSet[i] = false;
 
  // Always include first 1st vertex in MST.
  key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
  parent[0] = -1; // First node is always root of MST
 
  // The MST will have n vertices
  for (int count = 0; count < n-1; count++) {
    // Pick thd minimum key vertex from the set of vertices
    // not yet included in MST
    int u = minKey(n,key, mstSet);
 
    // Add the picked vertex to the MST Set
    mstSet[u] = true;
 
    // Update key value and parent index of the adjacent vertices of
    // the picked vertex. Consider only those vertices which are not yet
    // included in MST
    for (int v = 0; v < n; v++) {
      // G[u][v] is non zero only for adjacent vertices of m
      // mstSet[v] is false for vertices not yet included in MST
      // Update the key only if G[u][v] is smaller than key[v]
      if (G[u][v] && mstSet[v] == false && G[u][v] <  key[v])
	parent[v]  = u, key[v] = G[u][v];
    }
  }
  delete[] mstSet;
  delete[] key;
  return parent;
  for (int i = 0; i < n; i++)
    delete[] G[i];
  delete[] G;
}
 
 
// driver program to test above function
int testMST() {
   /* Let us create the following graph
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          */
  int *parent;
  double **graph;
  graph = new double*[5];
  for (int i = 0;i < 5;i++)
    graph[i] = new double[5];
  for (int i = 0;i < 5;i++)
    graph[i][i] = 0;
  graph[0][1] = 2;
  graph[0][2] = 0;
  graph[0][3] = 6;
  graph[0][4] = 0;
  graph[1][0] = 2;
  graph[1][2] = 3;
  graph[1][3] = 8;
  graph[1][4] = 5;
  graph[2][0] = 0;
  graph[2][1] = 3;
  graph[2][3] = 0;
  graph[2][4] = 7;
  graph[3][0] = 6;
  graph[3][1] = 8;
  graph[3][2] = 0;
  graph[3][4] = 9;
  graph[4][0] = 0;
  graph[4][1] = 5;
  graph[4][2] = 7;
  graph[4][3] = 9;
  /* 
     {{0, 2, 0, 6, 0},
     {2, 0, 3, 8, 5},
     {0, 3, 0, 0, 7},
     {6, 8, 0, 0, 9},
     {0, 5, 7, 9, 0}, };
  */
  parent = primMST(5,1,&graph);
  printMST(5,parent,graph);
  for (int i = 0;i < 5;i++)
    delete[] graph[i];
  delete[] graph;
  return 0;
}

double ***read_instance (int *n,int *p) {
  double ***graph;
  cin >> (*n) >> (*p);
  graph = new double**[(*p)];
  for (int k = 0;k < (*p);k++) {
    graph[k] = new double*[(*n)];
    for (int i = 0;i < (*n);i++) {
      graph[k][i] = new double[(*n)];
      for (int j = 0;j < (*n);j++) {
	cin >> graph[k][i][j];
      }
    }
  }
  return graph;
}

void  getMST(int n,int p,double ***graph){
  int *parent;
  parent = primMST(n,p,graph);
  printMST(n,parent,graph[0]);
}

void delete_graph(int n,int p,double ***graph){
  for (int k = 0;k < p;k++) {
    for (int i = 0;i < n;i++) {
      delete[] graph[k][i];
    }
    delete graph[k];
  }
  delete[] graph;
}

bool *odd_nodes_of_MST(int n,int *mst) {
  bool *is_odd;
  is_odd = new bool[n];
  for (int i = 0;i < n;i++) is_odd[i] = (mst[i] >= 0);
  for (int i = 0;i < n;i++) {
    if (mst[i] >= 0)
      is_odd[mst[i]] = !is_odd[mst[i]];
  }
  return is_odd;
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
