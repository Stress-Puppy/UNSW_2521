// isBST.c ... implementation of isBST function

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"
static int doisBST(Node t);

/*
    You will submit only this one file.

    Implement the function "isBST" below. Read the exam paper for a
    detailed specification and description of your task.

    - DO NOT modify the code in any other files except for debugging
      purposes.
    - If you wish, you can add static variables and/or helper functions
      to this file.
    - DO NOT add a "main" function to this file.
*/

int isBST(Tree t) {
    // TODO
    // Implement this function

    if (t == NULL) {
        return 1;
    }
    return doisBST(t->root);
}

static int doisBST(Node t) {
    // TODO
    // Implement this function

    Node new = t;
    if (new->left != NULL) {
        if (RecordGetZid(new->left->rec) >= RecordGetZid(new->rec)) {
            return 0;
        }
        if (doisBST(new->left) == 0) {
            return 0;
        }
    }
    if (new->right != NULL) {
        if (RecordGetZid(new->right->rec) <= RecordGetZid(new->rec)) {
            return 0;
        }
        if (doisBST(new->right) == 0) {
            return 0;
        }
    }

    // change the return value below!
    return 1;
    
}

