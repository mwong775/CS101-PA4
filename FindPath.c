/****************************************************************************************
*  FindPath.c
*  Melanie Wong
*  melywong
*  pa4
*  Prints adjacency list of Graph from input file, as well as distances and shortest
*  paths involving given vertices to an output file
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
    Graph G = newGraph(n);

    while (!feof (in)) {  
      fscanf (in, "%d", &n); 
      fscanf (in, "%d", &i);
      if(n == 0 || i == 0)
      	break;
      addEdge(G, n, i);       
    }
    //printGraph(stdout, G);
    printGraph(out, G);
    printf("\n");
    fprintf(out, "\n"); 

    while (!feof (in)) {  
      	
    	fscanf (in, "%d", &n); 
    	fscanf (in, "%d", &i);
    	if(n == 0 || i == 0)
     		break;
    	BFS(G, n); 

    	List L = newList();
    	getPath(L, G, i);

    	if(getDist(G, i) < 0) {
    		fprintf(out, "The distance from %d to %d is infinity\n", n, i);
    		fprintf(out, "No %d-%d path exists\n", n, i);
    		fprintf(out, "\n"); 
    	}
    	else {
    		fprintf(out, "The distance from %d to %d is %d\n", n, i, getDist(G, i));    
    		fprintf(out, "A shortest %d-%d path is: ", n, i); 
    		printList(out, L);    
    		fprintf(out, "\n"); 
    		fprintf(out,"\n");     		
		  }
		freeList(&L);
    }

    
    freeGraph(&G);
    fclose(in);
    fclose(out);

	return(0);
}