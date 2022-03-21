//Ravi Gupta
//radgupta
//pa4
//
//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

#define INF -1
#define NIL -2
#define WHITE 1
#define GRAY 2
#define BLACK 3

/*** Constructors-Destructors ***/

typedef struct GraphObj{
   List* L;
   int vertices;
   int edges;
   int source;
   int* color;
   int* parent;
   int* dist;
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
   G->dist = calloc(n+1, sizeof(int));
   for( int i = 1; i <= n; i++ ){
      G->dist[i] = INF;
   }

   G->vertices = n;
   G->edges = 0;
   G->source = NIL;
   return G;
}

void freeGraph(Graph* pG){
   if(pG!=NULL && *pG!=NULL){
      makeNull(*pG);
      for( int i = 1; i <= (*pG)->vertices; i++){
         freeList(&((*pG)->L[i]));
      }
      free((*pG)->L);
      free((*pG)->color);
      free((*pG)->parent);
      free((*pG)->dist);
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
   return(G->vertices);
}

int getSize(Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling getSize() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->edges);
}

int getSource(Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling getSource() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->source);
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

int getDist(Graph G, int u){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling getDist() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr,"Graph Error: calling getDist() on out of bounds u reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->dist[u]);
}

void getPath(List L, Graph G, int u){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling getPath() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( u < 1 || u > getOrder(G)){
      fprintf(stderr,"Graph Error: calling getPath() on out of bounds u reference\n");
      exit(EXIT_FAILURE);
   }
   if( getSource(G)==NIL ){
      fprintf(stderr,"Graph Error: calling getPath() on NIL source reference\n");
      exit(EXIT_FAILURE);
   }
   int s = G->source;
   int p = G->parent[u];
   if( u == s){
      append(L, s);
   }
   else if( p == NIL ){
      append(L, NIL);
   }
   else{
      getPath(L, G, p);
      append(L, u);
   }
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   for (int i = 1; i <= G->vertices; i++) {
      clear(G->L[i]);
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->dist[i] = INF;
   }
   G->edges = 0;
   G->source = NIL;
   
}
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
   G->edges--;
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
      G->edges++;
      return;
   }
   moveFront(L);
   while( index(L) >= 0 ){
      if( v < get(L) ){
         insertBefore(L, v);
         G->edges++;
         return;
      }
      moveNext(L);
   }
   append(L, v);
   G->edges++;
}
    
void BFS(Graph G, int s){ 
   if( G==NULL ){
      fprintf(stderr,"Graph Error: calling BFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( s < 1 || s > getOrder(G)){
      fprintf(stderr,"Graph Error: calling BFS() on out of bounds s reference\n");
      exit(EXIT_FAILURE);
   }
   for( int i = 1; i <= getOrder(G); i++ ){
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->dist[i] = INF;
   }
   G->source = s;
   G->color[s] = GRAY;
   G->dist[s] = 0;
   G->parent[s] = NIL;
   List Q = newList();
   append(Q, s);
   int x, y;
   List L;
   while( length(Q) > 0 ){
      x = front(Q);
      deleteFront(Q);
      L = G->L[x];
      moveFront(L);
      while( index(L) >= 0 ){
         y = get(L);
         if( G->color[y] == WHITE ){
            G->color[y] = GRAY;
            G->dist[y] = G->dist[x] + 1;
            G->parent[y] = x;
            append(Q, y);
         }
         moveNext(L);
      }
      G->color[x] = BLACK;
   }
   freeList(&Q);           
}


/*** Other operations ***/

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

