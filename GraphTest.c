/****************************************************************************************
*  GraphTest.c
*  Melanie Wong
*  melywong
*  pa4
*  Thoroughly tests functions of Graph ADT by getting vertices from input file
*  
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
	int n = 0;
	int i = 0;
	FILE *in, *out;

	if(argc != 3) {
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
   fscanf(in, "%d", &n);
   printf("n = %d\n", n);

   Graph G = newGraph(n);

   printf("printing empty Graph here:\n");
   printGraph(stdout, G);

   printf("order(vertices) = %d\n", getOrder(G));
   printf("size(edges) = %d\n", getSize(G));


    while (!feof (in)) {  
      //printf ("%d ", n);
      fscanf (in, "%d", &n); 
      fscanf (in, "%d", &i);
      printf("n = %d , i = %d\n", n, i);
      if(n == 0 || i == 0)
      	break;
      addEdge(G, n, i);       
    }

    printf("all edges added. Printing graph:\n");
    printGraph(stdout, G);
    printf("\n"); 

   
    while (!feof (in)) {  
   		 //printf ("%d ", n);
    	
    	fscanf (in, "%d", &n); 
    	fscanf (in, "%d", &i);
    	printf("n = %d , i = %d\n\n", n, i);
    	if(n == 0 || i == 0)
     		break;
    	BFS(G, n);

    	printf("order(vertices) = %d\n", getOrder(G));
    	printf("size(edges) = %d\n", getSize(G));
    	printf("source = %d\n", getSource(G)); 

    	for(int i = 1; i < getOrder(G)+1; i++) {
    		printf("parent of %d is %d\n", i, getParent(G, i));
    		printf("dist. from %d to src %d is %d\n", i, n, getDist(G, i));
    	}

    	List L = newList();
    	getPath(L, G, i);
      
    	if(getDist(G, i) < 0) {
    		printf("The distance from %d to %d is infinity\n", n, i);
    		printf("No %d-%d path exists\n", n, i);
    		printf("\n"); 
    	}
    	else {
    		printf("The distance from %d to %d is %d\n", n, i, getDist(G, i));    
    		printf("The shortest %d-%d path is: ", n, i); 
    		printList(stdout, L);    
    		printf("\n"); 
    		printf("\n"); 
		}
		freeList(&L);
    }
    // empty edges from List
    makeNull(G);
    printf("called makeNull; Graph should have no edges: \n");
    printGraph(stdout, G);
    printf("\n");

    freeGraph(&G);
    fclose(in);
    fclose(out);

	return(0);
}