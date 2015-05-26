// Minimum weight perfect matching algorithm,
// from "Algorithm Design" - Kleinberg, Tardos 

#include "klein-tardos.h"
#include "BiObjetivo_TSP.h"
#include "MST.h"

void Node::add_in_edge(Edge *e)  {e->set_hkey(edges.insert(e, 0));}
void Node::add_out_edge(Edge *e) {e->set_tkey(edges.insert(e, 1));}

BiDigraph* prepare_graph(char *name) {
  FILE *f = fopen(name, "r");
  Cost cost;
  Name x, y;
  BiDigraph *g = new BiDigraph();
  map<Name, Node*> lstx, lsty;

  // <node> <node> <edgecost>, where node is represented by int
  while (fscanf(f, "%d %d %d\n", &x, &y, &cost) != EOF) {
    Node *xnode, *ynode;
    if ( lstx.find(x) == lstx.end() )
      lstx[x] = xnode = g->add_node(x, XNode);
    if ( lsty.find(y) == lsty.end() )
      lsty[y] = ynode = g->add_node(y, YNode);
    xnode = lstx[x];
    ynode = lsty[y];

    g->add_edge(xnode, ynode, cost);
  }

  Node *s = g->add_node(0, SourceNode);
  Node *t = g->add_node(0, TargetNode);
  map<Name, Node*>::iterator it;
  for (it=lstx.begin(); it!=lstx.end(); it++)
    g->add_edge(s, it->second, 0);
  for (it=lsty.begin(); it!=lsty.end(); it++)
    g->add_edge(it->second, t, 0);

  fclose(f);

  return g;
}

BiDigraph* prepare_graph(int n,bool *is_odd,Cost **C) {
  Cost cost;
  BiDigraph *g = new BiDigraph();
  map<Name, Node*> lstx, lsty;
  Node *xnode,*ynode;

  for (Name i = 0;i < (unsigned int) n;i++) if(is_odd[i]) {
      xnode = g->add_node(i, XNode);
      lstx[i] = xnode;
      ynode = g->add_node(i, YNode);
      lsty[i] = ynode;
    }

  for (Name i = 0;i < (unsigned int) n;i++) if(is_odd[i]) {
      for (Name j = i + 1;j < (unsigned int) n;j++) if (is_odd[j]) {
	  xnode = lstx[i];
	  ynode = lsty[j];
	  cost = C[i][j];
	  g->add_edge(xnode, ynode, cost);

	  xnode = lstx[j];
	  ynode = lsty[i];
	  g->add_edge(xnode, ynode, cost);
	}
    }
  
  Node *s = g->add_node(0, SourceNode);
  Node *t = g->add_node(0, TargetNode);
  map<Name, Node*>::iterator it;
  for (it=lstx.begin(); it!=lstx.end(); it++)
    g->add_edge(s, it->second, 0);
  for (it=lsty.begin(); it!=lsty.end(); it++)
    g->add_edge(it->second, t, 0);

  return g;
}

int *perfect_matching(bool *is_odd,Instancia *I) {
  int **G;
  int *PM;
  BiDigraph *g;
  G = normMST(I->n,I->p,I->C);
  g = prepare_graph(I->n,is_odd,G);
  PM = g->matching();
  for (int i = 0;i < I->n;i++)
    delete[] G[i];
  delete[] G;
  delete g;
  return PM;
}
