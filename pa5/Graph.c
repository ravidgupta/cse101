//Ravi Gupta
//radgupta
//pa5
//
//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

#define UNDEF -1
#define NIL 0
#define WHITE 1
#define GRAY 2
#define BLACK 3

/*** Constructors-Destructors ***/

typedef struct GraphObj{
   List* L;
   int order;
   int size;
   int* color;
   int* parent;
   int* discover;
   int* finish;
} GraphObj;

typedef struct GraphObj* Graph;

Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   G->L = calloc(n+1, sizeof(List));
   for( int i = 1; i <= n; i++ ){
      List L = newList();
      G->L[i] = L;
   }
   G->color = calloc(n+1, sizeof(int));
   for( int i = 1; i <= n; i++ ){
      G->color[i] = WHITE;
   }
   G->parent = calloc(n+1, sizeof(int));
   for( int i = 1; i <= n; i++ ){
      G->parent[i] = NIL;
   }
   G->discover = calloc(n+1, sizeof(int));
   for( int i = 1; i <= n; i++ ){
      G->discover[i] = UNDEF;
   }
   G->finish = calloc(n+1, sizeof(int));
   for( int i = 1; i <= n; i++ ){
      G->finish[i] = UNDEF;
   }
   G->order = n;
   G->size = 0;
   return G;
}

void freeGraph(Graph* pG){
   if(pG!=NULL && *pG!=NULL){
      for( int i = 1; i <= (*pG)->order; i++){
         freeList(&((*pG)->L[i]));
      }
      free((*pG)->L);
      free((*pG)->color);
      free((*pG)->parent);
      free((*pG)->discover);
      free((*pG)->finish);
      free(*pG);
      *pG = NULL;
   }
}

/*** Access functions ***/
int getOrder(Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->order);
}

int getSize(Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling getSize() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->size);
}

int getParent(Graph G, int u){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr,"Graph Error: calling getParent() on out of bounds u reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->parent[u]);
}

int getDiscover(Graph G, int u){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr,"Graph Error: calling getDiscover() on out of bounds u reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->discover[u]);
}

int getFinish(Graph G, int u){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling getFinish() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr,"Graph Error: calling getFinish() on out of bounds u reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->finish[u]);
}

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr,"Graph Error: calling addEdge() on out of bounds u reference\n");
      exit(EXIT_FAILURE);
   }
   if( v < 1 || v > getOrder(G)){
      fprintf(stderr,"Graph Error: calling addEdge() on out of bounds v reference\n");
      exit(EXIT_FAILURE);
   }
   addArc(G, u, v);
   addArc(G, v, u);
   G->size--;
}
void addArc(Graph G, int u, int v){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling addArc() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr,"Graph Error: calling addArc() on out of bounds u reference\n");
      exit(EXIT_FAILURE);
   }
   if( v < 1 || v > getOrder(G)){
      fprintf(stderr,"Graph Error: calling addArc() on out of bounds v reference\n");
      exit(EXIT_FAILURE);
   }
   List L = G->L[u];
   if( length(L) == 0 ){
      append(L, v);
      G->size++;
      return;
   }
   moveFront(L);
   while( index(L) >= 0 ){
      if( v < get(L) ){
         insertBefore(L, v);
         G->size++;
         return;
      }
      moveNext(L);
   }
   append(L, v);
   G->size++;
}

void visit(Graph G, int i, int *time, List L){
   G->discover[i] = ++*time;
   G->color[i] = GRAY;
   List M = G->L[i];
   moveFront(M);
   int y;
   while( index(M) >= 0 ){
      y = get(M);
      if( G->color[y] == WHITE ){
         G->parent[y] = i;
         visit(G, y, time, L);
      }
      moveNext(M);
   }
   G->color[i] = BLACK;
   G->finish[i] = ++*time;
   prepend(L, i);
}
    
void DFS(Graph G, List S){ 
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling DFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(S) != getOrder(G)){
      fprintf(stderr,"Graph Error: calling DFS() with different sized references\n");
      exit(EXIT_FAILURE);
   }
   List L = copyList(S);
   clear(S);
   for( int i = 1; i <= getOrder(G); i++ ){
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }
   int time = 0;
   moveFront(L);
   while( index(L) >= 0 ){
      int i = get(L);
      if( G->color[i] == WHITE ){
         visit(G, i, &time, S);
      }
      moveNext(L);
   }
   freeList(&L);
}


/*** Other operations ***/

Graph transpose(Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling transpose() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   Graph H = newGraph(G->order);
   List L;
   for( int i = 1; i <= G->order; i++){
     L = G->L[i];
     moveFront(L);
     while( index(L) >= 0 ){
        addArc(H, get(L), i);
        moveNext(L);
     }
   }
   return H;
}

Graph copyGraph(Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling copyGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   Graph H = newGraph(G->order);
   List L;
   for( int i = 1; i <= G->order; i++){
     L = G->L[i];
     moveFront(L);
     while( index(L) >= 0 ){
        addArc(H, i, get(L));
        moveNext(L);
     }
   }
   return H;
}


void printGraph(FILE* out, Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   List L;
   for( int i = 1; i <= getOrder(G); i++ ){
      fprintf(out, "%d: ", i);
      L = G->L[i];
      printList(out, L);
      fprintf(out, "\n");
   }
} 

