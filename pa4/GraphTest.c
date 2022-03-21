//Ravi Gupta
//radgupta
//pa4
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {

   Graph G = newGraph(35);
   List L = newList();
   for(int i=1; i<35; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);
   printGraph(stdout, G);
   printf("%d\n", getOrder(G));
   printf("%d\n", getSource(G));
   printf("%d\n", getSize(G));
   printf("%d\n", getParent(G, 2));
   printf("%d\n", getDist(G, 2));
   BFS(G, 1);
   printf("%d\n", getOrder(G));
   printf("%d\n", getSource(G));
   printf("%d\n", getSize(G));
   printf("%d\n", getParent(G, 2));
   printf("%d\n", getDist(G, 2));
   getPath(L, G, 7);
   printList(stdout, L);

   
   makeNull(G);
   printGraph(stdout, G);

   freeList(&L);
   freeGraph(&G);
}
