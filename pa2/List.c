//Ravi Gupta
//radgupta
//pa2
//
//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   void* data;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = NULL;
   N->next = NULL;
   return(N);
}

void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

void freeList(List* pQ){
   if(pQ!=NULL && *pQ!=NULL) { 
      while( (*pQ)->length > 0 ){
         deleteFront(*pQ);
      }
      free(*pQ);
      *pQ = NULL;  
   }
}

// Access functions -----------------------------------------------------------
int length(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

int index(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->index);
}

void* front(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 ){
      fprintf(stderr,"List Error: calling front() on empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

void* back(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: callin back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 ){
      fprintf(stderr,"List Error: calling back() on empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}

void* get(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->cursor == NULL ){
      fprintf(stderr,"List Error: calling get() on undefined cursor reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data);
}

void clear(List L){
   Node N=NULL;
   if( L==NULL ){
      fprintf(stderr,"List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   while( L->length > 0 ){
      L->index = -1;
      N = L->front;
      L->front = L->front->next;
      N->next = NULL;
      freeNode(&N);
      L->length--;
   }
}

void moveFront(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length !=0 ){
      L->cursor = L->front;
      L->index = 0;
   }
}

void moveBack(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length != 0 ){
      L->cursor = L->back;
      L->index = L->length - 1;
   }
}

void movePrev(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->index >= 1 ){
      L->cursor = L->cursor->prev;
      L->index--;
   }
   else if( L->index == 0 ){
      L->cursor = NULL;
      L->index = -1;
   }
}

void moveNext(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->index != -1 ){
      if ( L->index + 1 < L->length ){
         L->cursor = L->cursor->next;
         L->index++;
      }
      else{
         L->cursor = NULL;
         L->index = -1;
      }
   }
}


void prepend(List L, void* data){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node N = newNode(data);
   if( L->length == 0 ){
      L->front = N;
      L->back = N;
   }
   else if( L->length > 0 ){
      L->front->prev = N;
      N->next = L->front;
      L->front = N;
   }
   L->length++;
   if( L->index != -1 ){
      L->index++;
   }
}

void append(List L, void* data){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node N = newNode(data);
   if( L->length == 0 ){
      L->front = N;
      L->back = N;
   }
   else if( L->length > 0 ){
      L->back->next = N;
      N->prev = L->back;
      L->back = N;
   }
   L->length++;
}

void insertBefore(List L, void* data){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->cursor == NULL ){
      fprintf(stderr,"Cursor Error: calling insertBefore() with undefined Cursor reference\n");
   }
   Node N = newNode(data);
   if( L->cursor->prev != NULL ){
      L->cursor->prev->next = N;
      N->prev = L->cursor->prev;
   }
   L->cursor->prev = N;
   N->next = L->cursor;
   if ( L->index == 0 ){
      L->front = N;
   }
   L->length++;
   L->index++;
}

void insertAfter(List L, void* data){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->cursor == NULL ){
      fprintf(stderr,"Cursor Error: calling insertAfter() with undefined Cursor reference\n");
   }
   Node N = newNode(data);
   if( L->cursor->next != NULL ){
      L->cursor->next->prev = N;
      N->next = L->cursor->next;
   }
   L->cursor->next = N;
   N->prev = L->cursor;
   if ( L->index + 1 == L->length ){
      L->back = N;
   }
   L->length++;
}

void deleteFront(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 ){
      fprintf(stderr,"List Error: calling deleteFront() on empty List\n");
      exit(EXIT_FAILURE);
   }
   Node N = L->front;
   L->front = N->next;
   N->next = NULL;
   if( L->length > 1){
      L->front->prev = NULL;
   }
   if( L->index == 0 ){
      L->cursor = NULL;
      L->index = -1;
   }
   freeNode(&N);
   L->length--;
   if( L->index != -1 ){
      L->index--;
   }
}

void deleteBack(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 ){
      fprintf(stderr,"List Error: calling deleteBack() on empty List\n");
      exit(EXIT_FAILURE);
   }
   Node N = L->back;
   L->back = N->prev;
   N->prev = NULL;
   if ( L->length > 1 ){
      L->back->next = NULL;
   }
   if( L->index + 1 == L->length ){
      L->cursor = NULL;
      L->index = -1;
   }
   freeNode(&N);
   L->length--;
}

void delete(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 ){
      fprintf(stderr,"List Error: calling delete() on empty List\n");
      exit(EXIT_FAILURE);
   }
   Node N = L->cursor;
   if( L->length == 1 ){
      L->front = NULL;
      L->back = NULL;
   }
   else if( L->index == 0 ){
      L->front = N->next;
      N->next = NULL;
      L->front->prev = NULL;
   }
   else if ( L->index + 1 == L->length ){
      L->back = N->prev;
      N->prev = NULL;
      L->back->next = NULL;
   }
   else{ 
      N->prev->next = N->next;
      N->next->prev = N->prev;
      N->prev = NULL;
      N->next = NULL;
   }
   L->cursor = NULL;
   L->index = -1;
   freeNode(&N);
   L->length--;
}

void printList(FILE* out, List L){
   Node N=NULL;
   if( L==NULL ){
      fprintf(stderr, 
         "List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   N = L->front;
   while( N!=NULL ){
      fprintf(out, "%p ", N->data);
      N = N->next;
   }
}


 
