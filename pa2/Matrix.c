//Ravi Gupta
//radgupta
//pa2
//
//-----------------------------------------------------------------------------
// Matrix.c
// Implementation file for Matrix ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include "List.h"

// structs --------------------------------------------------------------------

// private EntryObj type
typedef struct EntryObj{
   int j;
   double data;  
} EntryObj;

// private Entry type
typedef EntryObj* Entry;

// private Matrix type
typedef struct MatrixObj{
   List* L;
   int size;
   int zero;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------

Entry newEntry(int j, double data){
   Entry E = malloc(sizeof(EntryObj));
   E->j = j;
   E->data = data;
   return(E);
}

void freeEntry(Entry* pE){
   if( pE!=NULL && *pE!=NULL ){
      free(*pE);
      *pE = NULL;
   }
}

Matrix newMatrix(int n){
   Matrix M = malloc(sizeof(MatrixObj));
   M->L = calloc(n, sizeof(List));
   for( int i = 1; i <= n; i++ ){
      List L = newList();
      M->L[i-1] = L;
   }
   M->size = n;
   M->zero = 0;
   return M;
}

void freeMatrix(Matrix* pM){
   if(pM!=NULL && *pM!=NULL){
      makeZero(*pM);
      for( int i = 1; i <= (*pM)->size; i++){
         freeList(&((*pM)->L[i-1]));
      }
      free((*pM)->L);
      free(*pM);
      (*pM) = NULL;
   }
}

int size(Matrix M){
   if( M==NULL ){
      fprintf(stderr,"Matrix Error: calling size() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   return(M->size);
}

int NNZ(Matrix M){
   if( M==NULL ){
      fprintf(stderr,"Matrix Error: calling NNZ() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   return(M->zero);
}

int equals(Matrix A, Matrix B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"Matrix Error: calling equal() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   List C,D;
   int equal = 0;
   Entry E, F;
   if ( A->size == B->size && A->zero == B->zero ){
      for( int i = 1; i <= A->size; i++){
         C = A->L[i-1];
         D = B->L[i-1];
         equal = (length(C)==length(D));
         moveFront(C);
         moveFront(D);
         while( index(C)>=0 && equal){
            E = get(C);
            F = get(D);
            equal = ( E->data==F->data );
            moveNext(C);
            moveNext(D);
         }
         if( !equal ){
            break;
         }
      }
   }
   return equal;
}

void makeZero(Matrix M){
   if( M==NULL ){
      fprintf(stderr,"Matrix Error: calling makeZero() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   for( int i = 1; i <= M->size; i++){
      for( int j = 1; j <= M->size; j++ ){
         changeEntry(M, i, j, 0.0);
      }
      if(M->zero == 0){
         break;
      }
   } 

}

void changeEntry(Matrix M, int i, int j, double x){
   if( M==NULL ){
      fprintf(stderr,"Matrix Error: calling changeEntry() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   } 
   if( i < 1 && i > M->size && j < 1 && j > M->size ){ 
      fprintf(stderr,"Matrix Error: calling changeEntry() with coordinates not in Matrix\n");
      exit(EXIT_FAILURE);
   }
   List L = M->L[i-1];
   Entry E, F;
   int y = 0;
   if( length(L)==0 ){
      if( x==0.0 ){
         return;
      }
      F = newEntry(j, x);
      prepend(L, F);
      M->zero++;
      return;
   }
   moveFront(L);
   while( y <= j && index(L)!= -1){
      E = get(L);
      y = E->j;
      if( y==j ) {
         break;
      }
      moveNext(L);
   }
   if( y==j ){
      if( x == 0.0 ){
         freeEntry(&E);
         delete(L);
         M->zero--;
      }
      else{
         F = newEntry(j, x);
         insertAfter(L, F);
         freeEntry(&E);
         delete(L);
      }
   }
   else{
      if( x != 0.0 ){
         F = newEntry(j, x);
         if(index(L)!=0){
            append(L, F);
         }
         else{
            insertBefore(L, F);
         }
         M->zero++;
      }
   }
}

Matrix copy(Matrix A){
   if( A==NULL ){
      fprintf(stderr,"Matrix Error: calling copy() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   Matrix M = newMatrix(A->size);
   List B;
   Entry E;
   for( int i = 1; i <= A->size; i++){
      B = A->L[i-1];
      moveFront(B);
      while( index(B)>=0 ){
         E = get(B);
         changeEntry(M, i, E->j, E->data);
         moveNext(B);
      }
   }
   return M;
}

Matrix transpose(Matrix A){
   if( A==NULL ){
      fprintf(stderr,"Matrix Error: calling transpose() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   Matrix M = newMatrix(A->size);  
   List B;
   Entry E;
   for( int i = 1; i <= A->size; i++){
      B = A->L[i-1];
      moveFront(B);
      while( index(B)>=0 ){ 
         E = get(B);
         changeEntry(M, E->j, i, E->data); 
         moveNext(B);
      }
   }
   return M;
}

Matrix scalarMult(double x, Matrix A){
   if( A==NULL ){
      fprintf(stderr,"Matrix Error: calling scalarMult() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   Matrix M = newMatrix(A->size);
   List B;
   Entry E;
   for( int i = 1; i <= A->size; i++){
      B = A->L[i-1];
      moveFront(B);
      while( index(B)>=0 ){
         E = get(B);
         changeEntry(M, i, E->j, E->data * x);
         moveNext(B);
      }
   }
   return M;
}

Matrix sum(Matrix A, Matrix B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"Matrix Error: calling sum() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   if( size(A)!=size(B) ){
      fprintf(stderr,"Matrix Error: calling sum() on different sized Matrices\n");
      exit(EXIT_FAILURE);
   }
   Matrix M = newMatrix(A->size);
   List C, D;
   Entry E, F;
   for( int i = 1; i <= A->size; i++){
      C = A->L[i-1];
      D = B->L[i-1];
      moveFront(C);
      moveFront(D);
      while( index(C)>=0 && index(D)>=0 ){
         E = get(C);
         F = get(D);
         if( E->j < F->j ){
            changeEntry(M, i, E->j, E->data);
            moveNext(C);
         }
         else if( E->j > F->j){
            changeEntry(M, i, F->j, F->data);
            moveNext(D);
         }
         else{
            changeEntry(M, i, E->j, E->data + F->data);   
            moveNext(C);
            moveNext(D);
         }
      }
      while(index(C)>=0){
         E = get(C);
         changeEntry(M, i, E->j, E->data);
         moveNext(C);
      }
      while(index(D)>=0){
         F = get(D);
         changeEntry(M, i, F->j, F->data);
         moveNext(D);
      }
   }
   return M; 
}

Matrix diff(Matrix A, Matrix B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"Matrix Error: calling diff() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   if( size(A)!=size(B) ){
      fprintf(stderr,"Matrix Error: calling diff() on different sized Matrices\n");
      exit(EXIT_FAILURE);
   }
   Matrix M = newMatrix(A->size);
   List C, D;
   Entry E, F;
   for( int i = 1; i <= A->size; i++){
      C = A->L[i-1];
      D = B->L[i-1];
      moveFront(C);
      moveFront(D);
      while( index(C)>=0 && index(D)>=0 ){
         E = get(C);
         F = get(D);
         if( E->j < F->j ){
            changeEntry(M, i, E->j, E->data);
            moveNext(C);
         }
         else if( E->j > F->j){
            changeEntry(M, i, F->j, F->data * -1);
            moveNext(D);
         }
         else{
            changeEntry(M, i, E->j, E->data - F->data);
            moveNext(C);
            moveNext(D);
         }
      }
      while(index(C)>=0){
         E = get(C);
         changeEntry(M, i, E->j, E->data);
         moveNext(C);
      }
      while(index(D)>=0){
         F = get(D);
         changeEntry(M, i, F->j, F->data * -1);
         moveNext(D);
      }
   }
   return M;
}

double vectorDot(List P, List Q){
   double d = 0;
   Entry E, F;
   moveFront(P);
   moveFront(Q);
   while( index(P)>=0 && index(Q)>=0 ){
      E = get(P);
      F = get(Q);
      if( E->j == F->j ){
         d += E->data * F->data;
         moveNext(P);
         moveNext(Q);
      }
      else if( E->j < F->j ){
         moveNext(P);
      }
      else{
         moveNext(Q);
      }
   }
   return d;
}

Matrix product(Matrix A, Matrix B){
   if( A==NULL || B==NULL ){
      fprintf(stderr,"Matrix Error: calling product() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   if( size(A)!=size(B) ){
      fprintf(stderr,"Matrix Error: calling product() on different sized Matrices\n");
      exit(EXIT_FAILURE);
   }
   Matrix M = newMatrix(A->size);
   Matrix N = transpose(B);
   List C, D;
   for( int i = 1; i <= A->size; i++){
      C = A->L[i-1];
      if( length(C) == 0 ){
         continue;
      }
      for( int j = 1; j <= A->size; j++){
         D = N->L[j-1];
         if( length(D) == 0 ) {
            continue;
         }
         changeEntry(M, i, j-1, vectorDot(C, D));
      }
   }
   return M;
}

void printMatrix(FILE* out, Matrix M){
   if( M==NULL ){
      fprintf(stderr,"Matrix Error: calling printMatrix() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   List C;
   Entry E;
   for( int i = 1; i <= M->size; i++){
      C = M->L[i-1];
      if( length(C) != 0){
         fprintf(out, "%d: ", i);
         moveFront(C);
         while( index(C)>=0 ){
            E = get(C);
            fprintf(out, "(%d, %0.1f) ", E->j, E->data);
            moveNext(C);
         }
         fprintf(out, "\n");
      } 
   }
}  
