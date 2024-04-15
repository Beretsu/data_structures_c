#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
    int height;
};

struct node* getNewNode(int data){
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;
    return newNode;
}

int height(struct node* root){
    if(!root){
        return -1;
    }
    return root->height;
}

int max(int a, int b){
    return (a > b) ? a:b;
}

int findMin(struct node* root){
    while(root->left){
        root = root->left;
    }
    return root->data;
}

int getBalance(struct node* root){
    return height(root->left) - height(root->right);
}

struct node* leftRotate(struct node* root){
    struct node* right = root->right;
    struct node* rightsleft = right->left;
    right->left = root;
    root->right = rightsleft;
    root->height = 1 + max(height(root->left), height(root->right));
    right->height = 1 + max(height(right->left), height(right->right));
    return right;
}

struct node* rightRotate(struct node* root){
    struct node* left = root->left;
    struct node* leftsright = left->right;
    left->right = root;
    root->left = leftsright;
    root->height = 1 + max(height(root->left), height(root->right));
    left->height = 1 + max(height(left->left), height(left->right));
    return left;
}

struct node* insertNode(struct node *root, int data){
    //regular insertion
    if(!root){
        return getNewNode(data);
    }
    if(data <= root->data){
        root->left = insertNode(root->left, data);
    }else{
        root->right = insertNode(root->right, data);
    }
    //update height
    root->height = 1 + max(height(root->left), height(root->right));
    //calculate balance factor
    int balance = getBalance(root);
    // If this node becomes unbalanced, then
    // there are 4 cases
    if(balance > 1){
        if(data < root->left->data){
            //left left case
            return rightRotate(root);
        }else{
            //left right case
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if(balance < -1){
        if(data > root->right->data){
            //right right case
            return leftRotate(root);
        }else{
            //right left case
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    /* return the (unchanged) node pointer */
    return root;
}

struct node* deleteNode(struct node* root, int key){
    if(!root){
        return NULL;
    }
    if(key < root->data){
        root->left = deleteNode(root->left, key);
    }else if(key > root->data){
        root->right = deleteNode(root->right, key);
    }else{
        if(!root->left && !root->right){
            free(root);
            return NULL;
        }
        if(!root->left){
            struct node* temp = root->right;
            free(root);
            root = temp;
        }else if(!root->right){
            struct node* temp = root->left;
            free(root);
            root = temp;
        }else{
            int temp = findMin(root->right);
            root->data = temp;
            root->right = deleteNode(root->right, temp);
        }
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    if(balance > 1){
        if(getBalance(root->left) < 0){
            //left right case
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        //left left case
        return rightRotate(root);
    }else if(balance < -1){
        if(getBalance(root->right) > 0){
            //right left case
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        //right right case
        return leftRotate(root);
    }
    return root;
}

void inOrder(struct node *root){
    if(root){
        inOrder(root->left);
        printf("%d;h:%d, ", root->data, root->height);
        inOrder(root->right);
    }
}

int main(){
    struct node* root = NULL;
    root = insertNode(root, 30);
    root = insertNode(root, 50);
    root = insertNode(root, 35); // makes a right left rotation
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 15); // makes a left left rotation
    root = insertNode(root, 37); // makes a left left rotation
    root = insertNode(root, 60);
    root = insertNode(root, 70); // makes a right right rotation
    root = insertNode(root, 10);
    root = insertNode(root, 13); // makes a left right rotation
    root = deleteNode(root, 37); // makes a right right rotation
    root = deleteNode(root, 70); // makes a left rightrotation
    root = deleteNode(root, 15);
    root = deleteNode(root, 30); // makes a left left rotation
    root = insertNode(root, 55);
    root = deleteNode(root, 40); // makes a right left rotation
    root = insertNode(root, 40);
    root = insertNode(root, 57);
    root = insertNode(root, 70);
    root = insertNode(root, 5);
    root = insertNode(root, 90);
    root = deleteNode(root, 20); // makes a left left ratation, and the moves upwards to the root that's also imbalanced and does a right right rotation
    inOrder(root); // prints values and its height in order of value
    return 0;
}
