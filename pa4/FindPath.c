//Ravi Gupta
//radgupta
//pa4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

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
   int n, first, second, d = 0;
   fscanf(in, "%d", &n);
   Graph G = newGraph(n);
   List L = newList();
   while( fgetc(in) != EOF ){
      fscanf(in, "%d", &first);
      fscanf(in, "%d", &second);
      if( first == 0 && second == 0 ){
         break;
      }
      addEdge(G, first, second);
   }
   printGraph(out, G);
   while( fgetc(in) != EOF ){
      fprintf(out, "\n");
      fscanf(in, "%d", &first);
      fscanf(in, "%d", &second);
      if( first == 0 && second == 0 ){
         break;
      }
      BFS(G, first);
      getPath(L, G, second);
      d = getDist(G, second);
      if( d != INF ){
         fprintf(out, "The distance from %d to %d is %d\n", first, second, d); 
         fprintf(out, "A shortest %d-%d path is: ", first, second);
         printList(out, L);
      }
      else{
         fprintf(out, "The distance from %d to %d is infinity\n", first, second);
         fprintf(out, "No %d-%d path exists", first, second);
      }
      fprintf(out, "\n");
      clear(L);   
   }
   freeList(&L);
   freeGraph(&G);
   fclose(in);
   fclose(out);
   return(0);
   
}
