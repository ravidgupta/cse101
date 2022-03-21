//Ravi Gupta
//radgupta
//pa4
//FindCompoonents.c
//finds the ocmponents

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"
#define NIL 0
#define UNDEF -1
int main(int argc, char* argv[]) {
   FILE *in, *out;
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if(in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   int n, first, second = 0;
   fscanf(in, "%d", &n);
   Graph G = newGraph(n);
   while( fgetc(in) != EOF ){
      fscanf(in, "%d", &first);
      fscanf(in, "%d", &second);
      if( first == 0 && second == 0 ){
         break;
      }
      addArc(G, first, second);
   }
   List L = newList();
   for (int i = 1; i <= getOrder(G); i++) {
      append(L, i);
   }
   DFS(G, L);
   Graph T = transpose(G);
   DFS(T, L);
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);
   fprintf(out, "\n");
   int count = 0;
   for (int i = 1; i <= getOrder(T); i++){
       if(getParent(T, i) == NIL){
           count++;
       }
   }
   fprintf(out, "G contains %d strongly connected components:\n", count);
   List *scc = calloc(count + 1, sizeof(List));
   for( int i = 1; i <= count; i++){
       scc[i] = newList();
   }
   int counter = 1;
   moveBack(L);
   while( index(L) >= 0 ){
      movePrev(L);
      int pop = back(L);
      deleteBack(L); 
      prepend(scc[counter], pop); 
      if( getParent(T, pop) == NIL){
         counter++;
      }
   }
   for( int i = 1; i <= count; i++){
      fprintf(out, "Component %d: ", i);
      printList(out, scc[i]);
      fprintf(out, "\n");
   }
   for( int i = 0; i <= count; i++) {
       freeList(&scc[i]);
   }
   freeList(&L); 
   freeGraph(&G); 
   freeGraph(&T);
   free(scc);
   fclose(in); 
   fclose(out);
   return(0);
}
