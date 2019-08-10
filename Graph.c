/****************************************************************************************
*  Graph.c
*  Melanie Wong
*  melywong
*  pa4
*  Graph ADT using an array of Lists and involving vertices and edges,  
*  with BFS and path functions. Print function produces adjacency list representation.
*
*****************************************************************************************/
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

#define INF -1
#define NIL 0

typedef struct GraphObj {
	// array of Lists, element i contains neighbors of vertex i
	List* adj;
	//array of ints(or chars, strings), element i = color of vertex i
	int* color;
	//array of ints, element i = parent of vertex i
	int* p;
	// array of ints, element i = dist. from (most recent) source to vertex i
	int* d;
	// order = # of vertices
	int order;
	// size = # of edges
	int size;
	// most recent source vertex for BFS
	int source;
} GraphObj;

/*** Constructors-Destructors ***/
typedef GraphObj* Graph;

Graph newGraph(int n) {
	// n vertices, no edges
	Graph G = malloc(sizeof(GraphObj));
	G->adj = malloc((n+1)*sizeof(List));
	for(int i = 1; i < n+1; i++) {
		G->adj[i] = newList();
	}
	G->color = malloc((n+1)*sizeof(int));
	G->p = malloc((n+1)*sizeof(int));
	G->d = malloc((n+1)*sizeof(int));

	G->order = n;
	G->size = 0;

	G->source = NIL;

	return(G);
}

void freeGraph(Graph* pG) {
	if((*pG)->color != NULL) {
		free((*pG)->color);
		(*pG)->color = NULL;
	}	
	if((*pG)->p != NULL) {
		free((*pG)->p);
		(*pG)->p = NULL;
	}
	if((*pG)->d != NULL) {
		free((*pG)->d);
		(*pG)->d = NULL;
	}
	for(int i = 1; i < getOrder(*pG)+1; i++) {
		freeList(&((*pG)->adj[i]));
	}
	if((*pG)->adj != NULL) {
		free((*pG)->adj);
		(*pG)->adj = NULL;
	}

	if(pG != NULL && *pG != NULL) {
		free(*pG);
		*pG = NULL;
	}
}

/*** Access functions ***/
int getOrder(Graph G) {
	return(G->order);
}

int getSize(Graph G) {
	return(G->size);
}

int getSource(Graph G) {
	return(G->source);
}

int getParent(Graph G, int u) {
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: invalid vertex u in getParent()");
		exit(1);
	}
	if(G->p[u] > 0) // assigned parent from calling BFS
		return G->p[u];
	else 
		return NIL;
}

int getDist(Graph G, int u) {
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: invalid vertex u in getDist()");
		exit(1);
	}
	if(G->d[u] > 0) // assigned dist. from calling BFS
		return G->d[u];
	else if(u == getSource(G))
		return 0;
	else
		return INF;
}

void getPath(List L, Graph G, int u) {
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: invalid vertex u in getPath()");
		exit(1);
	}
	if(getSource(G) == NIL) {
		printf("Graph Error: BFS(G, s) must be called before getPath()");
		exit(1);
	}
	if(getParent(G, u) == NIL && u == G->source) { // completed path
		append(L, u);
		return;
	}
	else if(getParent(G, u) == NIL && u != G->source) { //non-existent path
		clear(L);
		prepend(L, NIL);
		return;
	}
	else {
		getPath(L, G, getParent(G, u));
		append(L, u);
	} 
}

/*** Manipulation procedures ***/
void makeNull(Graph G) {
	// deletes all edges of G
	for(int i = 1; i < getOrder(G)+1; i++) {
		clear(G->adj[i]);
		G->color[i] = 0;
		G->d[i] = INF;
		G->p[i] = NIL;
	}
}

void addEdge(Graph G, int u, int v) {
	// inserts new edge, joining u to v
	// (add to each other's adj List)
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: invalid vertex u/v in addEdge()");
		exit(1);
	}
	moveFront(G->adj[u]);
	while(index(G->adj[u]) != -1 && v > get(G->adj[u])) {
		moveNext(G->adj[u]);
	}
	if(index(G->adj[u]) == -1) {
		append(G->adj[u], v);
	}
	else {
		insertBefore(G->adj[u], v);
	}

	moveFront(G->adj[v]);
	while(index(G->adj[v]) != -1 && u > get(G->adj[v])) {
		moveNext(G->adj[v]);
	}
	if(index(G->adj[v]) == -1) {
		append(G->adj[v], u);
	}
	else {
		insertBefore(G->adj[v], u);
	}

	G->size++;
}

void addArc(Graph G, int u, int v) {
	// inserts directed edge u to v
	// (adds v to adj List of u)
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: invalid vertex u/v in addArc()");
		exit(1);
	}
	moveFront(G->adj[u]);
	while(index(G->adj[u]) != -1 && v > get(G->adj[u])) {
		moveNext(G->adj[u]);
	}
	if(index(G->adj[u]) == -1) {
		append(G->adj[u], v);
	}
	else {
		insertBefore(G->adj[u], v);
	}
	G->size++;
}

void BFS(Graph G, int s) { // 0 = WHITE, 1 = GREY, 2 = BLACK
	G->source = s;
	int i = 1;
	while(i < G->order + 1) {
		if(i != s) {
			G->color[i] = 0;
			G->d[i] = INF;
			G->p[i] = NIL;
		}
		i++;
	}
	G->color[s] = 1;
	G->d[s] = 0;
	G->p[s] = NIL;

	List Q = newList(); // empty Queue

	append(Q, s);

	while(length(Q) != 0) {
		i = front(Q);
		deleteFront(Q); 
		moveFront(G->adj[i]);
		while(index(G->adj[i]) != -1) {
			int v = get(G->adj[i]);
			if(G->color[v] == 0) {
				G->color[v] = 1; // GREY
				G->d[v] = G->d[i] + 1;
				G->p[v] = i;
				append(Q, v);
			}
			moveNext(G->adj[i]);
		}
		G->color[i] = 2; // BLACK

		}
	freeList(&Q);
}


/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
	for(int i = 1; i < G->order+1; i++) {
		fprintf(out, "%d: ", i);
		moveFront(G->adj[i]);
		while(index(G->adj[i]) != -1) {
			fprintf(out, "%d ", get(G->adj[i]));
			moveNext(G->adj[i]);
		}
		fprintf(out, "\n");
	}
}


