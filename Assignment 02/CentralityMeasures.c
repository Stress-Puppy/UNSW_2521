// Centrality Measures ADT interface
// COMP2521 Assignment 2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "FloydWarshall.h"
#include "Graph.h"

static EdgeValues newEdgeValues(Graph g);

/**
 * Finds  the  edge  betweenness  centrality  for each edge in the given
 * graph and returns the results in a  EdgeValues  structure.  The  edge
 * betweenness centrality of a non-existant edge should be set to -1.0.
 */
EdgeValues edgeBetweennessCentrality(Graph g) {
	// TODO: Implement this function
	EdgeValues e = newEdgeValues(g);
	ShortestPaths sps = FloydWarshall(g);

	int i, j;
	int V = GraphNumVertices(g);
	for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
			// if there is a shortest path
            if (sps.next[i][j] != -1) {
				int record = i;
				// if the shortest path is not from i to j directly
				while (sps.next[i][j] != j) {
					e.values[i][sps.next[i][j]] += 1;
					i = sps.next[i][j];
				}
				e.values[i][j] += 1;
				i = record;

			}
		}			
	}
	freeShortestPaths(sps);
	return e;
}

/**
 * Prints  the  values in the given EdgeValues structure to stdout. This
 * function is purely for debugging purposes and will NOT be marked.
 */
void showEdgeValues(EdgeValues evs) {

}

/**
 * Frees all memory associated with the given EdgeValues  structure.  We
 * will call this function during testing, so you must implement it.
 */
void freeEdgeValues(EdgeValues evs) {
	// TODO: Implement this function

	for (int i = 0; i < evs.numNodes; i++) {
		free(evs.values[i]);
	}
	free(evs.values);
}

// create a new EdgeValues
static EdgeValues newEdgeValues(Graph g) {

	EdgeValues e;
	int V = GraphNumVertices(g);
	e.numNodes = V;    // The number of vertices in the graph
	e.values = (double**)malloc(V * sizeof(double*));

	int i, j;
    for (i = 0; i < V; i++) {
		e.values[i] = (double*)malloc(V * sizeof(double));
		// all edges betweenness initialized to 0.0
        for (j = 0; j < V; j++) {
            e.values[i][j] = -1.0;
		}			
	}

	// the edge betweenness from l->v to i (the edges read in graph) initialized to 0.0
	for (i = 0; i < V; i++) {
		AdjList l = GraphInIncident(g, i);
		while (l != NULL) {
			e.values[l->v][i] = 0.0;
			l = l->next;
		}
	}
	return e;
}

