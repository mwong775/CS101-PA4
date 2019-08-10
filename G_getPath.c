#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include "Graph.h"
#include "List.h"
#define FIRST_TEST DG_getSize
#define MAXSCORE 40

int main(int argc, char* argv[]) {
		Graph A = newGraph(100);
		List L = newList();
		List C = newList();
		// DIRECTED
		addArc(A, 64, 4);

        addArc(A, 64, 3);

        addArc(A, 42, 2);

        addArc(A, 2, 64);

        addArc(A, 4, 2);

        addArc(A, 3, 42);

        BFS(A, 3);

        getPath(L, A, 64);

        append(C, 3);

        append(C, 42);

        append(C, 2);

        append(C, 64);

       // if (!equals(L, C)) return 1;
        //clear(L);
        //clear(C);

        moveFront(L);

        BFS(A, 2);

        getPath(L, A, 2);

        append(C, 2);
	
	// UNDIRECTED
		/* addEdge(A, 64, 4);

        addEdge(A, 64, 3);

        addEdge(A, 42, 2);

        addEdge(A, 2, 64);

        addEdge(A, 4, 2);

        addEdge(A, 3, 42);

        BFS(A, 3);

        getPath(L, A, 64);

        append(C, 3);

        append(C, 64);

       // if (!equals(L, C)) return 1;
        clear(L);
        clear(C);

        moveFront(L);

        BFS(A, 2); // 

        getPath(L, A, 2); //

        append(C, 2);*/
        //printGraph(stdout, A);
        printf("manual list: ");
        printList(stdout, C);
        printf("\n");
        printf("Graph list: ");
        printList(stdout, L);
        printf("\n");

        if (!equals(L, C)) //return 2;
        	printf("test 2 :(");

        freeGraph(&A);
        freeList(&L);
        freeList(&C);	
}	