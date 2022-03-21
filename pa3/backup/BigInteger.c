//Ravi Gupta
//radgupta
//pa3

//-----------------------------------------------------------------------------
// BigInteger.c
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "BigInteger.h"
#include "List.h"

#define BASE 100
#define POWER 2

typedef struct BigIntegerObj{
   List L;
   int sign;
} BigIntegerObj;

typedef struct BigIntegerObj* BigInteger;

BigInteger newBigInteger(){
   BigInteger N;
   N = malloc(sizeof(BigIntegerObj));
   N->L = newList();
   N->sign = 0;
   return(N);
}

void freeBigInteger(BigInteger* pN){
   if(pN!=NULL && *pN!=NULL) {
      List L = ((*pN)->L);
      freeList(&L);
      free(*pN);
      *pN = NULL;
   } 
}

int sign(BigInteger N){
   if( N==NULL ){
      fprintf(stderr,"BigInteger Error: calling sign() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   return (N->sign);
} 

int compare(BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"BigInteger Error: calling compare() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   int a = A->sign;
   int b = B->sign;
   if( a > b ){
      return 1;
   }
   if( a > b ){
      return -1;
   }
   List L = A->L;
   List M = B->L;
   if( length(L) > length(M) ){
      return 1;
   }
   if( length(M) > length(L) ){
      return -1;
   }
   moveFront(L);
   moveFront(M);
   while( index(L)>= 0 || index(M) >= 0 ){
      moveNext(L);
      moveNext(M);
      if( get(L) > get(M) ){
         return 1;
      }
      if( get(M) > get(L) ){
         return -1;
      }
   }  
   if( index(L) >= 0 && index(M) < 0 ){
      return 1;
   }
   if( index(M) >= 0 && index(L) < 0 ){
      return -1;
   }
   return 0;
}

int equals(BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"BigInteger Error: calling equals() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   if ( compare(A, B) == 0 ){
      return 1;
   }
   return 0;
}

void makeZero(BigInteger N){
   if( N==NULL ){
      fprintf(stderr,"BigInteger Error: calling makeZero() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   List L = N->L;
   clear(L);
   N->sign = 0;
}

void negate(BigInteger N){
   if( N==NULL ){
      fprintf(stderr,"BigInteger Error: calling negate() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   N->sign = N->sign * -1;
}

long power(long x, int y){
   long ans = x;
   long mult = 10;
   for( int i = 0; i < y; i++){
      ans = ans * mult;
   }
   return ans;
}
BigInteger stringToBigInteger(char* s){
   int i = 0;
   if(s[0] == '+' || s[0] == '-'){
      i++;
   }
   for( ; i < strlen(s); i++){
      if( isdigit(s[i]) == 0 ){
          fprintf(stderr,"BigInteger Error: calling stringToBigInteger() with non-numeric characters\n");
          exit(EXIT_FAILURE);
      }
   }
   BigInteger N = newBigInteger();
   List L = N->L;
   i = strlen(s) - 1;
   N->sign = 1;
   int j = 0;
   if(s[0] == '-'){
      N->sign = -1;
      j = 1;
   }
   if(s[0] == '+'){
      j = 1;
   }
   long a;
   for( ; i >= 0 + j; ){
      a = 0;
      for( int k = 0; k < POWER; k++){
          a = a + power((long)s[i] - 48, k);
          i--;
      }
      prepend(L, a);
   }
   return N;
}

BigInteger copy(BigInteger N){
   if( N==NULL ){
      fprintf(stderr,"BigInteger Error: calling copy() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   BigInteger O = newBigInteger();
   List L = N->L;
   List P = O->L;
   freeList(&P);
   List M = copyList(L);
   O->L = M;
   O->sign = N->sign;
   return O;
}  

void normalize(BigInteger N){
   long a = 0;
   long b = 0;
   List L = N->L;
   moveBack(L);
   while( index(L) >=0 ){
      a = 0;
      set(L, get(L) + b);
      if( get(L) < 0 ){
         set(L, get(L) + BASE + b);
         a = -1;
      }
      else if( get(L) >= BASE){
         set(L, get(L) - BASE + b);
         a = 1;
      }
      b = a;
      movePrev(L);
   }
   if( a == -1 ){
      N->sign = -1;
   }
   if( a == 1 ){
      prepend(L, a);
   }
}
         
void add(BigInteger S, BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"BigInteger Error: calling add() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   BigInteger M = sum(A, B);
   freeBigInteger(&S);
   S = M;
}

BigInteger sum(BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"BigInteger Error: calling sum() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   BigInteger N = newBigInteger();
   long ans = 0;
   List C = A->L;
   List D = B->L;
   int a = A->sign;
   int b = B->sign;
   List E = N->L;
   N->sign = 1;
   if( a != 0 ){
      moveBack(C);
   }   
   if( b != 0 ){
      moveBack(D);
   } 
   while( index(C) >=0 && index(D) >= 0 ){
      if( a < 0 && b > 0 ){
         ans = get(D) - get(C);
      }
      else if( a > 0 && b < 0 ){
         ans = get(C) - get(D);
      }
      else {
         ans = get(C) + get(D);
      }
      prepend(E, ans);
      movePrev(C);
      movePrev(D);
   }
   if(index(C) >= 0 && a < 0){
      N->sign = -1;
   }
   while(index(C) >= 0){
      prepend(E, get(C));
      movePrev(C);
   }
   if(index(D) >= 0 && b < 0){
      N->sign = -1;
   }
   while(index(D) >= 0){
      prepend(E, get(D));
      movePrev(D);
   }

   normalize(N);

   return N;
}

void subtract(BigInteger D, BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"BigInteger Error: calling subtract() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   BigInteger M = diff(A, B);
   freeBigInteger(&D);
   D = M;
}

BigInteger diff(BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"BigInteger Error: calling diff() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   BigInteger N = newBigInteger();
   long ans = 0;
   List C = A->L;
   List D = B->L;
   int a = A->sign;
   int b = B->sign;
   List E = N->L;
   N->sign = 1;
   if( a != 0 ){
      moveBack(C);
   }
   if( b != 0 ){
      moveBack(D);
   }
   while( index(C) >= 0 && index(D) >= 0 ){
      if( a > 0 && b > 0 ){
         ans = get(C) - get(D);
      }
      else if( a < 0 && b < 0 ){
         ans = get(D) - get(C);
      }
      else {
         ans = get(C) + get(D);
      }
      prepend(E, ans);
      movePrev(C);
      movePrev(D);
   }
   if(index(C) >= 0 && a < 0){
      N->sign = -1;
   }
   while(index(C) >= 0){
      prepend(E, get(C));
      movePrev(C);
   }
   if(index(D) >= 0 && b > 0){
      N->sign = -1;
   }
   while(index(D) >= 0){
      prepend(E, get(D));
      movePrev(D);
   }
   normalize(N);
   return N;
}

void normalize2(BigInteger N){
   long a = 0;
   List L = N->L;
   moveFront(L);
   while( index(L) >= 0 ){
      set(L, get(L) + a );
      while( get(L) >= BASE ){
         set(L, get(L) - BASE);
         a++;
      }
      moveNext(L);
   }
   if( a > 0 ){
      prepend(L, a);
   }
}


void multiply(BigInteger P, BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"BigInteger Error: calling multiply() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   BigInteger M = prod(A, B);
   freeBigInteger(&P);
   P = M;
}

BigInteger prod(BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"BigInteger Error: calling prod() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   BigInteger N = newBigInteger();
   BigInteger O = copy(A);
   BigInteger P = copy(B);
   long sum = 0;
   long sum2 = 0;
   long mult = 1;
   int count = 0;
   List C = A->L;
   List D = B->L;
   List E = O->L;
   List F = P->L;
   int a = A->sign;
   int b = B->sign;
   List G = N->L;
   N->sign = 1;
   if( a != 0 ){
      moveBack(C);
   }
   if( b != 0 ){
      moveBack(D);
   }
   while( index(C) >= 0 && index(D) >= 0 ){
      mult = 1;
      sum = 0;
      sum2 = 0;
      moveBack(E);
      moveBack(F);
      for( int i = 0; i < count; i++){
         movePrev(E);
         movePrev(F);
      }
      while( index(E) >= 0 ){
         sum = sum + get(D) * get(E) * mult;
         movePrev(E);
         mult = mult * 10;
      }
      if( count == 0){
         movePrev(F);
      }
      mult = 1;
      while( index(F) >= 0 ){
         sum2 = sum2 + get(C) * get(F) * mult;
         movePrev(F);
         mult = mult * 10;
      }  
      prepend(G, sum + sum2);
      movePrev(C);
      movePrev(D);
      count++;
   }
   if(b > 0 && a < 0){
      N->sign = -1;
   }
   if(a > 0 && b < 0){
      N->sign = -1;
   }
   normalize(N);
   return N;
}

void printBigInteger(FILE* out, BigInteger N){
   if( N==NULL ){
      fprintf(stderr,
         "BigInteger Error: calling printBigInteger() on NULL BigInteger reference\n");
      exit(EXIT_FAILURE);
   }
   if(N->sign == -1){
      fprintf(out, "-");
   }
   List L = N->L;
   moveFront(L);
   while( index(L) >= 0 ){
      fprintf(out, "%ld", get(L));
      printf("\n");
      moveNext(L);
   }
}
