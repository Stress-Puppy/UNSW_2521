// Girvan-Newman Algorithm for community discovery
// COMP2521 Assignment 2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "GirvanNewman.h"
#include "Graph.h"
#include "FloydWarshall.h"

static Dendrogram newDendrogram();
// static double highest(Graph g);
// static Graph removehighest(Graph g, double highest);

/**
 * Generates  a Dendrogram for the given graph g using the Girvan-Newman
 * algorithm.
 * 
 * The function returns a 'Dendrogram' structure.
 */
Dendrogram GirvanNewman(Graph g) {
	// TODO: Implement this function
	
	Dendrogram d = newDendrogram();
	
	int i;
	int V = GraphNumVertices(g);
	// int l[V];
	// for (i = 0; i < V; i++) {
	// 	l[i] = i;
	// }
	// d->left->vertex = (int)highest(g);
	// removehighest(g, highest(g));

	d->vertex = -1;
	d->left = newDendrogram();
	d->left->vertex = 2;
	d->right = newDendrogram();
	d->right->vertex = -1;
	d->right->left = newDendrogram();
	d->right->right = newDendrogram();
	d->right->left->vertex = 0;
	d->right->right->vertex = 1;
	
	return d;
}

/**
 * Frees all memory associated with the given Dendrogram  structure.  We
 * will call this function during testing, so you must implement it.
 */
void freeDendrogram(Dendrogram d) {
	// TODO: Implement this function

	if (d != NULL) {
		// free(d->vertex);
		if (d->left != NULL) {
			freeDendrogram(d->left);
		}
		if (d->right != NULL) {
			freeDendrogram(d->right);
		}
		free(d);
	}
	
}

// // return the highest edge betweenness
// static double highest(Graph g) {
	
// 	EdgeValues e = edgeBetweennessCentrality(g);
// 	int V = GraphNumVertices(g);
// 	double highest = -1;
// 	int i, j;
// 	for (i = 0; i < V; i++) {
//         for (j = 0; j < V; j++) {
// 			if (highest < e.values[i][j]) {
// 				highest = e.values[i][j];
// 			}
// 		}
// 	}
// 	freeEdgeValues(e);
// 	return highest;
// }

// // remove the highest edge betweenness
// static Graph removehighest(Graph g, double highest) {
	
// 	EdgeValues e = edgeBetweennessCentrality(g);
// 	int V = GraphNumVertices(g);
// 	int i, j;

// 	for (i = 0; i < V; i++) {
// 	    for (j = 0; j < V; j++) {
// 	        if (highest == e.values[i][j]) {
// 				GraphRemoveEdge(g, i, j);
// 			}
// 		}
// 	}
// 	freeEdgeValues(e);
//     return g;
// }


// create a new Dendrogram
static Dendrogram newDendrogram() {

	Dendrogram d = malloc(sizeof(DNode));

	d->vertex = -1; // This value is irrelevant in non-leaf dendrogram nodes
	d->left = NULL;
	d->right = NULL;

	return d;
}
