#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct BstNode{
    void *data;
    struct BstNode *left;
    struct BstNode *right;
};

struct BstNode* getNewNode(void *data, size_t size){
    struct BstNode *temp = malloc(sizeof(struct BstNode));
    temp->data = malloc(sizeof(struct BstNode));
    for(int i = 0; i < size; i++){
        *(char*)(temp->data+i) = *(char*)(data+i);
    }
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct BstNode* insertNode(struct BstNode *root, void *data, size_t size, int (*cmp)(void*, void*)){
    if(!root){
        return getNewNode(data, size);
    }
    if(cmp(data, root->data) <= 0){
        root->left = insertNode(root->left, data, size, cmp);
    }else{
        root->right = insertNode(root->right, data, size, cmp);
    }
    return root;
}

void* findMin(struct BstNode *root){
    if(!root){
        printf("the tree is Empty\n");
        return NULL;
    }
    if(!root->left){
        return root->data;
    }
    return findMin(root->left);
}

void* findMax(struct BstNode *root){
    if(!root){
        printf("the tree is Empty\n");
        return NULL;
    }
    if(!root->right){
        return root->data;
    }
    return findMax(root->right);
}

struct BstNode* search(struct BstNode *root, void *data, int (*cmp)(void*, void*)){
    if(!root){
        return 0;
    }
    if(cmp(data, root->data) < 0){
        root = search(root->left, data, cmp);
    }else if(cmp(data, root->data) < 0){
        root = search(root->right, data, cmp);
    }
    return root;
}

int findHeight(struct BstNode *root){
    if(!root){
        return -1;
    }
    int left = findHeight(root->left);
    int right = findHeight(root->right);
    return (left >= right) ? left + 1: right+ 1;
}

void printLevelOrder(struct BstNode *root, void (*print)(void*)){
    if(!root){
        printf("the tree is empty");
    }else{
        enqueue(root, sizeof(struct BstNode));
        while(!isEmpty()){
            struct BstNode *temp = (struct BstNode*)Front();
            print(temp->data);
            if(temp->left){
                enqueue(temp->left, sizeof(struct BstNode));
            }
            if(temp->right){
                enqueue(temp->right, sizeof(struct BstNode));
            }
            dequeue();
        }
    }
}

void preOrder(struct BstNode *root, void (*print)(void*)){
    if(root){
        print(root->data);
        preOrder(root->left, print);
        preOrder(root->right, print);
    }
}

void inOrder(struct BstNode *root, void (*print)(void*)){
    if(root){
        inOrder(root->left, print);
        print(root->data);
        inOrder(root->right, print);
    }
}

void postOrder(struct BstNode *root, void (*print)(void*)){
    if(root){
        postOrder(root->left, print);
        postOrder(root->right, print);
        print(root->data);
    }
}

struct BstNode* deleteNode(struct BstNode *root, void *data, int (*cmp)(void*, void*)){
    if(!root){
        return NULL;
    }
    if(cmp(data, root->data) < 0){
        root->left = deleteNode(root->left, data, cmp);
    }else if(cmp(data, root->data) > 0){
        root->right = deleteNode(root->right, data, cmp);
    }else{
        if(!root->left && !root->right){
            free(root->data);
            free(root);
            root = NULL;
        }else if(!root->left && root->right){
            struct BstNode *temp = root;
            root = root->right;
            free(temp->data);
            free(temp);
        }else if(root->left && !root->right){
            struct BstNode *temp = root;
            root = root->left;
            free(temp->data);
            free(temp);
        }else{
            void* value = findMin(root->right);
            free(root->data);
            root->data = value;
            deleteNode(root->right, value, cmp);
        }
    }
    return root;
}

int isBinarySearchTree(struct BstNode *root, void* min, void* max, int (*func)(void*, void*, void*)){
    if(!root){
        return 1;
    }
    if(func(root->data, min, max)
    && isBinarySearchTree(root->left, min, root->data, func)
    && isBinarySearchTree(root->right, root->data, max, func)){
        return 1;
    }
    return 0;
}

void* findSuccesor(struct BstNode *root, void* data, int (*func)(void*, void*)){
    struct BstNode *current = search(root, data, func);
    if(!current){
        return NULL; //the element is not in the tree
    }
    if(current->right){
        return findMin(current->right);
    }
    void* succesor = NULL;
    while(root!=current){
        if(func(data, root->data) < 0){
            succesor = root->data;
            root = root->left;
        }else{
            root->right;
        }
    }
    return succesor;
}

void* findPredecessor(struct BstNode *root, void* data, int (*func)(void*, void*)){
    struct BstNode *current = search(root, data, func);
    if(!current){
        return NULL; //the element is not in the tree
    }
    if(current->left){
        return findMax(current->left);
    }
    void* predecessor = NULL;
    while(root!=current){
        if(func(data, root->data) > 0){
            predecessor = root->data;
            root = root->right;
        }else{
            root->left;
        }
    }
    return predecessor;
}

int main()
{
    return 0;
}
