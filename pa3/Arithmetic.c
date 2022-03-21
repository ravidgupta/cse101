//Ravi Gupta
//radgupta
//pa3

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"

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
}
