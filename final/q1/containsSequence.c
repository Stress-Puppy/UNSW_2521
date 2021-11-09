// containsSequence.c ... implementation of containsSequence function

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/*
    You will submit only this one file.

    Implement the function "containsSequence" below. Read the exam paper
    for a detailed specification and description of your task.

    - DO NOT modify the code in any other files except for debugging
      purposes.
    - If you wish, you can add static variables and/or helper functions
      to this file.
    - DO NOT add a "main" function to this file.
*/

int containsSequence(List seq1, List seq2) {
    // TODO
    // Implement this function
    
    Node first = seq1->first;
    Node second = seq2->first;

    // m + n
    while (second != NULL && first != NULL) {
        if (second->value != first->value) {
            first = first->next;
        }
        else {
            first = first->next;
            second = second->next;
        }
    }
    if (second == NULL) {
        return 1;
    }

    // change the return value below!
    return 0;
}


