// Floyd Warshall ADT interface
// COMP2521 Assignment 2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "FloydWarshall.h"
#include "Graph.h"

static ShortestPaths newShortestPaths(Graph g);

/**
 * Finds all shortest paths between all pairs of nodes.
 * 
 * The  function  returns  a 'ShortestPaths' structure with the required
 * information:
 * - the number of vertices in the graph
 * - distance matrix
 * - matrix of intermediates (see description above)
 */
ShortestPaths FloydWarshall(Graph g) {
	// TODO: Implement this function
	
	// ShortestPaths sps = {0};
	
	ShortestPaths sps = newShortestPaths(g);
	
	int i, j, k;
	int V = GraphNumVertices(g);
	// add the weight to each edge (from l->v to i)
	for (i = 0; i < V; i++) {
		AdjList l = GraphInIncident(g, i);
		while (l != NULL) {
			sps.dist[l->v][i] = l->weight;
			sps.next[l->v][i] = i;
			l = l->next;
		}
	}

    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (sps.dist[i][k] + sps.dist[k][j] < sps.dist[i][j] &&
				    sps.dist[i][k] != INFINITY && sps.dist[k][j] != INFINITY) {
                    sps.dist[i][j] = sps.dist[i][k] + sps.dist[k][j];
					sps.next[i][j] = sps.next[i][k]; 
				}
            }
        }
    }
	
	// let dist be a |V| × |V| array of minimum distances initialized to ∞ (infinity)
	// for each edge (u, v) do
	// 	dist[u][v] ← w(u, v)  // The weight of the edge (u, v)
	// for each vertex v do
	// 	dist[v][v] ← 0
	// for k from 1 to |V|
	// 	for i from 1 to |V|
	// 		for j from 1 to |V|
	// 			if dist[i][j] > dist[i][k] + dist[k][j] 
	// 				dist[i][j] ← dist[i][k] + dist[k][j]
	// 			end if

	return sps;
}

/**
 * This  function  is  for  you to print out the ShortestPaths structure
 * while you are debugging/testing your implementation. 
 * 
 * We will not call this function during testing, so you may  print  out
 * the  given  ShortestPaths  structure in whatever format you want. You
 * may choose not to implement this function.
 */
void showShortestPaths(ShortestPaths sps) {
	// int i = 0;
	// int j = 0;

	// for (i = 0; i < sps.numNodes; i++) {
	// 	for (j = 0; j < sps.numNodes; j++) {
	// 		printf("    %d, %d : ", i, j);
	// 		if (sps.dist[i][j] == INFINITY) {
	// 			printf("INF\n");		
	// 		} else {
	// 			printf("%d\n", sps.dist[i][j]);
	// 		}
	// 	}
	// }

	// for (i = 0; i < sps.numNodes; i++) {
	// 	for (j = 0; j < sps.numNodes; j++) {
	// 		printf("    %d, %d : ", i, j);
	// 		if (sps.next[i][j] == -1) {
	// 			printf("X\n");
	// 		} else {			
	// 			printf("%d\n", sps.next[i][j]);
	// 		}
	// 	}
	// }
}

/**
 * Frees  all  memory associated with the given ShortestPaths structure.
 * We will call this function during testing, so you must implement it.
 */
void freeShortestPaths(ShortestPaths sps) {
	// TODO: Implement this function

	for (int i = 0; i < sps.numNodes; i++) {
		free(sps.dist[i]);
		free(sps.next[i]);
	}
	free(sps.dist);
	free(sps.next);
}



// create a new ShortestPaths
static ShortestPaths newShortestPaths(Graph g) {

	ShortestPaths sps;
	int V = GraphNumVertices(g);
	sps.numNodes = V;
	sps.dist = (int**)malloc(V * sizeof(int*));
	sps.next = (int**)malloc(V * sizeof(int*));

	int i, j;
    for (i = 0; i < V; i++) {
		sps.dist[i] = (int*)malloc(V * sizeof(int));
		sps.next[i] = (int*)malloc(V * sizeof(int));
        for (j = 0; j < V; j++) {
			// for each vertex v do
			// 	dist[v][v] ← 0
			if (i == j) {
				sps.dist[i][j] = 0;
			}
			// let dist be a |V| × |V| array of minimum distances initialized to ∞ (infinity)
			else {
				sps.dist[i][j] = INFINITY;
			}
            sps.next[i][j] = -1;
		}			
	}
	return sps;
}