#include "btree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_node *Insert(int x, struct tree_node *t) {
    if (t == NULL) {
        // Root insert
        t = (struct tree_node *)malloc(sizeof(struct tree_node));
        t->item = x;
        t->left = NULL;
        t->right = NULL;
        return t;
    }
    // The recursive steps, if the value we wish to insert is greater than the
    // current node, i go to the right, if smaller i go left.
    if (x > t->item) {
        t->right = Insert(x, t->right);
    }
    if (x < t->item) {
        t->left = Insert(x, t->left);
    }
    // The edge case: if the value we wish to insert is equal the nodes item,
    // its inserted right underneath to the left
    if (x == t->item) {
        struct tree_node *newNode = malloc(sizeof(struct tree_node));
        newNode->item = x;
        newNode->left = t->left;
        newNode->right = NULL;
        t->left = newNode;
    }
  return t;
}

struct tree_node *Remove(int x, struct tree_node *t) {
  // Remove one item from the tree t
     // If the tree is empty return empty tree
    if (t == NULL) {
        return t;
    }
    // If the tree doesnt contain the value x we just return the root
    if (!Contains(x, t)) {
        return t;
    } else if (x == t->item) {
        // We have found the node, we have two cases:
        // First up, if the node has one or zero branches

        if (t->left == NULL) {
            // if it doesnt have a left node, we grab the node to the right and
            // return it, as we can "shuffle" it up

            struct tree_node *newInPlace = t->right;
            free(t);
            return newInPlace;
        } else if (t->right == NULL) {
            // Same principle for an empty right child, i shuffle the node to
            // the left and shuffle it up

            struct tree_node *newInPlace = t->left;
            free(t);
            return newInPlace;
        } else {
            // If it has two children i set a temporary pointer equal to one
            // step to the right of the current tree node, and then i run it as
            // far left as possible

            struct tree_node *temp = t->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            // I give the node we wish to swap out, the smallest of the bigger
            // numbers of the current tree node, and afterwards i remove the
            // temporary pointer. This effectivly swaps the two nodes
            t->item = temp->item;
            Remove(x, temp);
            return t;
        }
    }
    // the recursive step, if the number we wish to remove is greater, we
    // traverse to the right, and likewise if x is smaller than the current
    // node, we traverse left
    else if (x > t->item) {
        t->right = Remove(x, t->right);

    } else if (x < t->item) {
        t->left = Remove(x, t->left);
    }

    return t;
}

int Contains(int x, struct tree_node *t) {

  // Return true if the tree t contains item x. Return false otherwise.
    // Returns true if the tree t contains item x. Returns false otherwise.
    // If the tree is empty, its false
    if (Empty(t)) {
        return 0;
    }
    // Base case
    if (x == t->item) {
        return 1;
    }
    // Recursive step
    else if (x > t->item) {
        return Contains(x, t->right);
    } else if (x < t->item) {
        return Contains(x, t->left);
    }
    return 0;
}

struct tree_node *Initialize(struct tree_node *t) {
  // Create an empty tree
  t = NULL;
  return t;
}

int Empty(struct tree_node *t) {
  // Test if empty
  if(t != NULL){
    return 0;
  }
  else

  return 1;
}

int Full(struct tree_node *t) {
  // Can't be full
  return 0;
}
