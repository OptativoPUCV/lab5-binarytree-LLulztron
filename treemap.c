#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
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
    //new->lower_than = lower_than;
    TreeMap * new = (TreeMap *) malloc(sizeof(TreeMap));
    new -> root = NULL;
    new -> current = NULL;
    new -> lower_than = lower_than;
    return new;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    if (tree == NULL || key == NULL || value == NULL) return;
    TreeNode * aux = tree -> root;
    TreeNode * parent = NULL;
    while (aux != NULL) {
        parent = aux;
        if (is_equal(tree, key, aux -> pair -> key)) return;
        if (tree -> lower_than(key, aux -> pair -> key) == 1) {
            aux = aux -> left;
        } else {
            aux = aux -> right;
        }
    }
    TreeNode * new = createTreeNode(key, value);
    new -> parent = parent;
    if (parent == NULL) {
        tree -> root = new;
    } else {
        if (tree -> lower_than(key, parent -> pair -> key) == 1) {
            parent -> left = new;
        } else {
            parent -> right = new;
        }
    }
}

TreeNode * minimum(TreeNode * x) {
    while (x -> left != NULL) {
        x = x -> left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (node == NULL) return;
    TreeNode * parent = node -> parent;
    if (node -> left == NULL && node -> right == NULL) {
        if (parent == NULL) {
            tree -> root = NULL;
        } else {
            if (parent -> left == node) {
                parent -> left = NULL;
            } else {
                parent -> right = NULL;
            }
        }
    } else {
        if (node -> left != NULL && node -> right != NULL) {
            TreeNode * min = minimum(node -> right);
            node -> pair = min -> pair;
            removeNode(tree, min);
        } else {
            TreeNode * child = (node -> left != NULL) ? node -> left : node -> right;
            if (parent == NULL) {
                tree -> root = child;
            } else {
                if (parent -> left == node) {
                    parent -> left = child;
                } else {
                    parent -> right = child;
                }
            }
            child -> parent = parent;
        }
    }
    free(node -> pair -> key);
    free(node -> pair -> value);
    free(node -> pair);
    free(node);
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * aux = tree -> root;
    while(aux != NULL)
    {
        if(is_equal(tree, key, aux -> pair -> key))
        {
            tree -> current = aux;
            return aux -> pair;
        }
        else
        {
            if(tree -> lower_than(key, aux -> pair -> key) == 1)
            {
                aux = aux -> left;
            }
            else
            {
                aux = aux -> right;
            }
        }
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
