#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair; //valor
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root; //raiz
    TreeNode * current; //nodo actual
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    
    new->pair = (Pair *)malloc(sizeof(Pair));
    if (new->pair == NULL)
    {
        free(new);
        return NULL;
    }
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{    
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    
    return new;
    
    
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    TreeNode * newNode = createTreeNode(key, value);
    if (newNode == NULL) {
        // Memory allocation failed
        return;
    }

    if (tree->root == NULL) {
        // If the tree is empty, make the new node the root
        tree->root = newNode;
        return;
    }

    TreeNode * current = tree->root;
    TreeNode * parent;

    // Traverse the tree to find the appropriate position for the new node
    while (current != NULL) {
        parent = current;
        if (tree->lower_than(key, current->pair->key)) {
            // If key is less than current node's key, go left
            if (current->left == NULL) {
                current->left = newNode;
                newNode->parent = current;
                return;
            }
            current = current->left;
        } else if (tree->lower_than(current->pair->key, key)) {
            // If key is greater than current node's key, go right
            if (current->right == NULL) {
                current->right = newNode;
                newNode->parent = current;
                return;
            }
            current = current->right;
        } else {
            // If key already exists, update the value and return
            current->pair->value = value;
            free(newNode->pair); // Free the Pair struct of newNode
            free(newNode);       // Free the newNode itself
            return;
        }
    }
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * aux = tree->root;
    while (aux != NULL)
        {
            if (is_equal(tree,key,aux->pair->key))
            {
                tree->current = aux;
                return aux->pair;
                
            }
            if (tree->lower_than(key,aux->pair->key) == 1)
                aux = aux->left;
            else
                aux =  aux->right;
        }
    
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
