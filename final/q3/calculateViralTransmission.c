// calculateViralTransmission.c ... implementation of
// calculateViralTransmission function

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

static int findPath(Graph g, int src, int dest);
/*
    You will submit only this one file.

    Implement the function "calculateViralTransmission" below.
    Read the exam paper for a detailed specification and
    description of your task.

    - DO NOT modify the code in any other files except for debugging
      purposes.
    - If you wish, you can add static variables and/or helper functions
      to this file.
    - DO NOT add a "main" function to this file.
*/

void calculateViralTransmission(Graph g, int src, int srcViralLoad,
                                double *trasmissionArray) {
	// TODO
	// Implement this function
    if (g == NULL) {
        return;
    }
    int V = GraphNumVertices(g);
    for (int i = 0; i < V; i++) {
        if (src == i) {
            trasmissionArray[i] = srcViralLoad * pow(0.6, 0);
        }
        else {
            int lon = findPath(g, src, i);
            if (lon != 0) {
                trasmissionArray[i] = srcViralLoad * pow(0.6, lon);
                if (trasmissionArray[i] < 10) {
                    trasmissionArray[i] = 0;
                }
            }
        }
    }
	
}


// the code is from my code of Lab 8
/**
 * Finds  the  shortest path (in terms of the number of hops) from `src`
 * to `dest` such that no edge on the path has weight larger than `max`.
 * Stores  the  path  in the given `path` array including both `src` and
 * `dest` and returns the number of vertices stored in the  path  array.
 * Returns 0 if there is no such path.
 */
static int findPath(Graph g, int src, int dest) {
    
    int V = GraphNumVertices(g);
	int visited[V];
	for (int i = 0; i < V; i++) {
		visited[i] = -1;
	}

	bool find_path = false;
	visited[src] = src;
	Queue q = QueueNew();
    QueueEnqueue(q, src);

	while (QueueIsEmpty(q) == false && find_path == false) {
		int v = QueueDequeue(q);
		if (v == dest) {
			find_path = true;
		}
		else {
			for (int w = 0; w < V; w++) {
				if (GraphIsAdjacent(g, v, w) == true && visited[w] == -1) {
                    visited[w] = v;
                    QueueEnqueue(q, w);
				}  
			} 
		} 
	} 
	QueueFree(q);
    int number = 0;
	if (find_path == true) {
        int first = visited[dest];
		while (first != src) {
			first = visited[first];
			number++;
		}
		if (src != dest) {
            return number + 1;
        }
		return number;
	}
	return 0;
}
