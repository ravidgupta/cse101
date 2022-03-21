//Ravi Gupta
//radgupta
//pa3
//-----------------------------------------------------------------------------
// BigIntegerTest.c
// Test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"

int main(int argc, char* argv[]){
   char *s = "1234";
   char *t = "-5678";
   BigInteger A = stringToBigInteger(s);
   BigInteger B = stringToBigInteger(t);
   printBigInteger(stdout,A);
   printf("\n");
   printBigInteger(stdout,B);
   printf("\n");
   BigInteger C = sum(A, B);
   printBigInteger(stdout,C);
   printf("\n");
   BigInteger D = diff(B, A);
   printBigInteger(stdout,D);
   printf("\n");
   freeBigInteger(&A);
   freeBigInteger(&B);
   return (0);
}
