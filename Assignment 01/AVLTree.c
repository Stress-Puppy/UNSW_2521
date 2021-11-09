
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Record.h"
#include "AVLTree.h"

typedef struct node *Node;
struct node {
    Record rec;
    Node   left;
    Node   right;
    int    height;
};

struct tree {
    Node    root;
    int     (*compare)(Record, Record);
};

////////////////////////////////////////////////////////////////////////
// Auxiliary functions

static void doTreeFree(Node n, bool freeRecords);
static Node newNode(Record rec);
static Record doTreeSearch(Tree t, Node n, Record rec);
static Node doTreeInsert(Tree t, Node n, Record rec, bool *r);
static Node rightRotate(Node y);
static Node leftRotate(Node x);
static int max(int a, int b);
static int GetHeight(Node n);
static void doTreeSearchBetween(Tree t, Node n, Record lower,
                                Record upper, List l);
static Record doTreeNext(Tree t, Node n, Record r);

////////////////////////////////////////////////////////////////////////

static Node newNode(Record rec) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    n->rec = rec;
    n->left = NULL;
    n->right = NULL;
    n->height = 0;
    return n;
}

////////////////////////////////////////////////////////////////////////

Tree TreeNew(int (*compare)(Record, Record)) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    t->root = NULL;
    t->compare = compare;
    return t;
}

////////////////////////////////////////////////////////////////////////

void TreeFree(Tree t, bool freeRecords) {
    doTreeFree(t->root, freeRecords);
    free(t);
}

static void doTreeFree(Node n, bool freeRecords) {
    if (n != NULL) {
        doTreeFree(n->left, freeRecords);
        doTreeFree(n->right, freeRecords);
        if (freeRecords) {
            RecordFree(n->rec);
        }
        free(n);
    }
}

////////////////////////////////////////////////////////////////////////

Record TreeSearch(Tree t, Record rec) {
    return doTreeSearch(t, t->root, rec);
}

static Record doTreeSearch(Tree t, Node n, Record rec) {
    if (n == NULL) {
        return NULL;
    }

    int cmp = t->compare(rec, n->rec);
    if (cmp < 0) {
        return doTreeSearch(t, n->left, rec);
    } else if (cmp > 0) {
        return doTreeSearch(t, n->right, rec);
    } else {
        return n->rec;
    }
}


////////////////////////////////////////////////////////////////////////
/* IMPORTANT: 
   Do NOT modify the code above this line. 
   You must not modify the 'node' and 'tree' structures defined above.
   You must not modify the functions defined above.
*/
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////


bool TreeInsert(Tree t, Record rec) {
    // TODO: Complete this function

    bool success = false;
    t->root = doTreeInsert(t, t->root, rec, &success);
    return success;
}

static Node doTreeInsert(Tree t, Node n, Record rec, bool *success) {
    
    // if tree is empty then create a new node containing item return true
    if (n == NULL) {
       *success = true;
       return newNode(rec);
    }

    int cmp = t->compare(rec, n->rec);
    if (cmp < 0) {
        n->left = doTreeInsert(t, n->left, rec, success);
        n->height = n->left->height +1;
    }
    else if (cmp > 0) {
        n->right = doTreeInsert(t, n->right, rec, success);
        n->height = n->right->height +1;
    }
    // else if item = data(tree) then return false
    else {
        *success = false;
    }

    // unbalance tree
    int LHeight = GetHeight(n->left);
    int RHeight = GetHeight(n->right);
    if ((LHeight - RHeight) > 1) {
        if (t->compare(rec, n->left->rec) > 0) {
            n->left = leftRotate(n->left);
        }
        n = rightRotate(n);
    }
    else if ((RHeight - LHeight) > 1) {
        if (t->compare(rec, n->right->rec) < 0) {
            n->right = rightRotate(n->right);
        }
        n = leftRotate(n);
    }
    return n;
}

static Node rightRotate(Node y) {
    Node x = y->left;
    y->left= x->right;
    x->right = y;


    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return x;
}


static Node leftRotate(Node x) {
    Node y = x->right;
    x->right = y->left;
    y->left = x;

    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

    return y;
}

static int GetHeight(Node n) {
   if (n == NULL) return 0;
   if (n->left == NULL && n->right == NULL) return 1;
   return max(GetHeight(n->left), GetHeight(n->right)) + 1;
}

static int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

////////////////////////////////////////////////////////////////////////

List TreeSearchBetween(Tree t, Record lower, Record upper) {
    // TODO: Complete this function
    List l = ListNew();
    doTreeSearchBetween(t, t->root, lower, upper, l);
    return l;
}

static void doTreeSearchBetween(Tree t, Node n, Record lower,
                                Record upper, List l) {
   
    if (n == NULL) {
        return;
    }

    int low = t->compare(lower, n->rec);
    int up  = t->compare(upper, n->rec);

    // find the range (avoid unnecessarily visiting nodes)
    if (low > 0) {
        doTreeSearchBetween(t, n->right, lower, upper, l);
    }
   
    if (up < 0) {
        doTreeSearchBetween(t, n->left, lower, upper, l);
    }

    // find list the data in the range
    if (low <= 0 && up >= 0) {
        doTreeSearchBetween(t, n->left, lower, n->rec, l);
        ListAppend(l, n->rec);
        doTreeSearchBetween(t, n->right, n->rec, upper, l);
    }
}
////////////////////////////////////////////////////////////////////////

Record TreeNext(Tree t, Record r) {
    // TODO: Complete this function
    return doTreeNext(t, t->root, r);
}

static Record doTreeNext(Tree t, Node n, Record r) {
    if (n == NULL) {
        return NULL;
    }
    int cmp = t->compare(n->rec, r);
    if (cmp <= 0) return doTreeNext(t, n->right, r);
    else {
        Record temp = doTreeNext(t, n->left, r);
        if (temp == NULL) {
            temp = n->rec;
        }
        return temp;
    }
}
