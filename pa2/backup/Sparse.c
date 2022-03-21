//Ravi Gupta
//radgupta
//pa2
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 40

int main(int argc, char* argv[]){

   int n = 0;
   int count = 0;
   FILE *in, *out;
   char line[MAX_LEN];

   if( argc != 3 ){
      printf("Usage: Sparse inputfile outputfile");
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
}
