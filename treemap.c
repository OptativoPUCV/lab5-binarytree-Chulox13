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
    //new->lower_than = lower_than;
    
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    if (tree == NULL)
        return;

    TreeNode *newNode = createTreeNode(key, value);
    if (newNode == NULL)
        return; // Error al crear el nodo

    if (tree->root == NULL) {
        // Árbol vacío, el nuevo nodo se convierte en la raíz
        tree->root = newNode;
        return;
    }

    TreeNode *currentNode = tree->root;
    TreeNode *parent = NULL;

    while (currentNode != NULL) {
        parent = currentNode;
        if (tree->lower_than(key, currentNode->pair->key)) {
            // Si la clave es menor, ve a la izquierda
            currentNode = currentNode->left;
        } else if (tree->lower_than(currentNode->pair->key, key)) {
            // Si la clave es mayor, ve a la derecha
            currentNode = currentNode->right;
        } else {
            // Clave ya existe, actualiza el valor
            currentNode->pair->value = value;
            free(newNode); // Liberar el nodo creado
            return;
        }
    }

    // Insertar el nuevo nodo
    newNode->parent = parent;
    if (tree->lower_than(key, parent->pair->key)) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
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
