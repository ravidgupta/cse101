//Ravi Gupta
//radgupta
//pa1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 40

int main(int argc, char * argv[]){
   
   int n = 0;
   int count = 0;
   FILE *in, *out;
   char line[MAX_LEN];

   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   while( fgets(line, MAX_LEN, in) != NULL)  {
      n++;
   }
   char** inputs = calloc(n,sizeof(char*)) ;
   rewind(in);
   while( fgets(line, MAX_LEN, in) != NULL)  {
         inputs[count] = malloc(sizeof(char)*128);
         strcpy(inputs[count],line);
         count++;
   }
   for(int i = 0; i < n; i++){
      printf("%s", inputs[i]);
   }
   List L = newList();
   prepend(L, 0);
   for( int i = 0; i < n; i++ ){
      moveFront(L);
      for ( int j = 0; j < n; j++){
         if( strcmp(inputs[i], inputs[index(L)]) > 0 ){
            if(index(L) + 1 >= length(L)){
               insertAfter(L,i);
            }
            else {
               moveNext(L);
            }
         }
         else{   
            insertBefore(L,i);
         }
      } 
   }
   printList(out,L);
   moveFront(L);
   int x;
   while(0 <= index[L]){
      printf("a");
      x = get(L);
      printf("b");
      fprintf(out,"%s + \n", inputs[x]);
     // free(inputs[x]);
      moveNext(L);
   }
   
   freeList(&L);
   free(inputs);
   fclose(in);
   fclose(out);
}
