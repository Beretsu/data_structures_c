#include <stdio.h>
#include <stdlib.h>
//tutorials https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
//https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
//https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
typedef enum {black, red} Color;
//RedBlack tree node
typedef struct Node
{
    int data;
    Color color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;
//queue node
typedef struct node
{
    Node *data;
    struct node *next;
} node;
//queue ponters
node *front = NULL;
node *rear = NULL;

int isEmpty()
{
    if(front)
    {
        return 0;
    }
    return 1;
}

void enqueue(Node* x)
{
    node *temp = malloc(sizeof(node));
    temp->data = x;
    temp->next = NULL;
    if(isEmpty())
    {
        front = temp;
        rear = temp;
    }
    else
    {
        rear->next = temp;
        rear = temp;
    }
}

Node* dequeue()
{
    if(isEmpty())
    {
        printf("The queue is empty, the operation cant be done\n");
        return 0;
    }
    node *temp = front;
    Node *re = front->data;
    front = front->next;
    free(temp);
    return re;
}

Node* Front()
{
    if(isEmpty())
    {
        printf("The queue is empty, the operation cant be done\n");
        return 0;
    }
    return front->data;
}
//creates a new RBnode
Node* getNewNode(int data)
{
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->color = red;
    node->left = node->right = node->parent = NULL;
    return node;
}
//BSTInsert. utility function to insert a node to a RBTree
Node* insertNodeUtil(Node* root, Node* node)
{
    if(!root)
    {
        return node;
    }
    if(node->data <= root->data)
    {
        root->left = insertNodeUtil(root->left, node);
        root->left->parent = root;
    }
    else
    {
        root->right = insertNodeUtil(root->right, node);
        root->right->parent = root;
    }
    return root;
}
//left rotates and fixes links
void leftRotate(Node* root, Node* node)
{
    Node* right = node->right;
    Node* rightsleft = right->left;
    if(!node->parent)
    {
        root = right;
    }
    else
    {
        right->parent = node->parent;
        if(node->parent->left == node)
        {
            node->parent->left = right;
        }
        else
        {
            node->parent->right = right;
        }
    }
    right->left = node;
    node->parent = right;
    node->right = rightsleft;
    if(rightsleft)
    {
        rightsleft->parent = node;
    }
}
//right rotates and fixes links
void rightRotate(Node* root, Node* node)
{
    Node* left = node->left;
    Node* leftsright = left->right;
    if(!node->parent)
    {
        root = left;
    }
    else
    {
        left->parent = node->parent;
        if(node->parent->left == node)
        {
            node->parent->left = left;
        }
        else
        {
            node->parent->right = left;
        }
    }
    left->right = node;
    node->parent = left;
    node->left = leftsright;
    if(leftsright)
    {
        leftsright->parent = node;
    }
}
//fixes violations caused by BST insertion
Node* fixViolation(Node* root, Node* node)
{
    while(node != root && node->parent->color == red)
    {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;
        //Parent of node is left child of Grand-parent of node
        if(grandparent->left == parent)
        {
            Node* uncle = grandparent->right;
            /* Case : 1
               The uncle of node is also red
               Only Recoloring required */
            if(uncle && uncle->color == red)
            {
                grandparent->color = red;
                parent->color = black;
                uncle->color = black;
                node = grandparent;
            }
            else
            {
                /* Case : 2
                   node is right child of its parent
                   Left-rotation required */
                if(node == parent->right)
                {
                    leftRotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                /* Case : 3
                   node is left child of its parent
                   Right-rotation required */
                rightRotate(root, grandparent);
                parent->color = black;
                grandparent->color = red;
                if(grandparent == root)
                {
                    return parent;// root has benn modified. we return new node
                }
                return root;
            }
        }
        /* Case : B
           Parent of node is right child of Grand-parent of pt */
        else //Parent of node is right child of Grand-parent of node.. mirror of above
        {
            Node* uncle = grandparent->left;
            if(uncle && uncle->color == red)
            {
                grandparent->color = red;
                parent->color = black;
                uncle->color = black;
                node = grandparent;
            }
            else
            {
                if(node == parent->left)
                {
                    rightRotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                leftRotate(root, grandparent);
                parent->color = black;
                grandparent->color = red;
                if(grandparent == root)
                {
                    return parent;
                }
                return root;
            }
        }
    }
    root->color = black;
    return root;
}
//Function to insert a new node with given data
Node* insertNode(Node* root, int data)
{
    Node* newNode = getNewNode(data);
    root = insertNodeUtil(root, newNode);
    return fixViolation(root, newNode);
}
// returns the node with the minimal value in a subtree
Node* findMin(Node* root)
{
    while(root->left)
    {
        root = root->left;
    }
    return root;
}
// find node that replaces a deleted node in BST
Node* getReplacer(Node* toReplace)
{
    // when leaf
    if(!toReplace->left && !toReplace->right)
    {
        return NULL;
    }
    //if node only has a right child
    if(!toReplace->left)
    {
        return toReplace->right;
    }
    //if node only has a left child
    if(!toReplace->right)
    {
        return toReplace->left;
    }
    // when node have 2 children
    else
    {
        return findMin(toReplace->right);
    }
}

Node* fixDoubleBlack(Node* root, Node* doubleBlack)
{
    // reached root
    if(doubleBlack == root)
    {
        return root;
    }
    Node* parent = doubleBlack->parent;
    Node* sibling;
    if(doubleBlack == parent->left)
    {
        sibling = parent->right;
        if(sibling->color == black)
        {
            if(sibling->right && sibling->right->color == red)
            {
                //right right case
                sibling->color = parent->color;
                parent->color = black;
                sibling->right->color = black;
                leftRotate(root, parent);
                if(parent == root)
                {
                    return sibling;
                }
                return root;
            }
            else if(sibling->left && sibling->left->color == red)
            {
                //right left case

                sibling->left->color = parent->color;
                parent->color = black;
                rightRotate(root, sibling);
                leftRotate(root, parent);
                if(parent == root)
                {
                    return sibling->parent;
                }
                return root;
            }
            else
            {
                //both children of sibling are black
                sibling->color = red;
                if(parent->color == black)
                {
                    return fixDoubleBlack(root, parent);
                }
                else
                {
                    parent->color = black;
                    return root;
                }
            }
        }
        else
        {
            //sibling is red
            sibling->color = black;
            parent->color = red;
            leftRotate(root, parent);
            if(root == parent){
                root = sibling;
            }
            return fixDoubleBlack(root, doubleBlack);
        }
    }
    else
    {
        sibling = parent->left;
        if(sibling->color == black)
        {
            if(sibling->left && sibling->left->color == red)
            {
                //left left case
                sibling->color = parent->color;
                parent->color = black;
                sibling->left->color = black;
                rightRotate(root, parent);
                if(parent == root){
                    return sibling;
                }
                return root;
            }
            else if(sibling->right && sibling->right->color == red)
            {
                //left right case
                sibling->right->color = parent->color;
                parent->color = black;
                leftRotate(root, sibling);
                rightRotate(root, parent);
                if(parent == root){
                    return sibling->parent;
                }
                return root;
            }
            else
            {
                //both children of sibling are black
                sibling->color = red;
                if(parent->color == black)
                {
                    return fixDoubleBlack(root, parent);
                }
                else
                {
                    parent->color = black;
                    return root;
                }
            }
        }
        else
        {
            //sibling is red
            sibling->color = black;
            parent->color = red;
            rightRotate(root, parent);
            if(root == parent){
                root = sibling;
            }
            return fixDoubleBlack(root, doubleBlack);
        }
    }
}
//utility function to delete a node forma a RBTree
Node* deleteNodeUtil(Node* root, Node* toDelete)
{
    //we get the replacer of deleted node in BSTDelete
    Node* replacer = getReplacer(toDelete);
    //toDelete is a leaf
    if(!replacer)
    {
        if(toDelete == root)
        {
            root = NULL;
        }
        else
        {
            if(toDelete->color == black)
            {
                //deleted a black node, we need to fix double black node
                root = fixDoubleBlack(root, toDelete);
            }
            if(toDelete == toDelete->parent->left)
            {
                //we fix the link of the parent
                toDelete->parent->left = NULL;
            }
            else
            {
                //we fix the link of the parent
                toDelete->parent->right = NULL;
            }
        }
    }
    //toDelete has 1 child
    else if(!toDelete->left || !toDelete->right)
    {
        if(toDelete == root)
        {
            replacer->color = black;
            replacer->parent = NULL;
            root = replacer;
        }
        else
        {
            if(toDelete == toDelete->parent->left)
            {
                //we fix parent's link to new child
                toDelete->parent->left = replacer;
            }
            else
            {
                //we fix parent's link to new child
                toDelete->parent->right = replacer;
            }
            //we fix new child's parent link
            replacer->parent = toDelete->parent;
            //if the node to delete and the replacing node are black
            if(toDelete->color == black && replacer->color == black)
            {
                //we fix double black
                root = fixDoubleBlack(root, replacer);
            }
            else
            {
                //we simply recolor
                replacer->color = black;
            }
        }
    }
    else
    {
        //toDelete has 2 children
        //operation of BSTDelete
        toDelete->data = replacer->data;
        //we recurse
        return deleteNodeUtil(root, replacer);
    }
    free(toDelete);
    return root;
}
// deletes the given node
//it searches the given node and calls the functions to delete
Node* deleteNode(Node* root, int data)
{
    Node* iterator = root;
    while(iterator)
    {
        if(data < iterator->data)
        {
            iterator = iterator->left;
        }
        else if(data > iterator->data)
        {
            iterator = iterator->right;
        }
        else
        {
            return deleteNodeUtil(root, iterator);
        }
    }
    return root;
}

void printLevelOrder(Node *root)
{
    if(!root)
    {
        printf("the tree is empty\n");
    }
    else
    {
        enqueue(root);
        while(!isEmpty())
        {
            printf("%d;%d, ", Front()->data, Front()->color);
            if(Front()->left)
            {
                enqueue(Front()->left);
            }
            if(Front()->right)
            {
                enqueue(Front()->right);
            }
            dequeue();
        }
    }
}

void inOrder(Node *root)
{
    if(root)
    {
        inOrder(root->left);
        printf("%d;%d, ", root->data, root->color);
        inOrder(root->right);
    }
}

int main()
{
    Node* root = NULL;
    root = insertNode(root, 15);
    root = insertNode(root, 10);
    root = insertNode(root, 17);
    root = insertNode(root, 5);
    root = insertNode(root, 7);
    root = insertNode(root, 50);
    root = insertNode(root, 24);
    root = insertNode(root, 31);
    root = insertNode(root, 60);
    root = insertNode(root, 30);
    root = insertNode(root, 3);
    root = insertNode(root, 6);
    root = insertNode(root, 1);
    root = deleteNode(root, 17);
    root = deleteNode(root, 24);
    root = deleteNode(root, 5);
    root = deleteNode(root, 10);
    root = deleteNode(root, 15);
    root = deleteNode(root, 6);
    root = deleteNode(root, 31);
    root = deleteNode(root, 50);
    root = deleteNode(root, 60);
    root = deleteNode(root, 1);
    root = deleteNode(root, 30);
    root = deleteNode(root, 7);
    root = deleteNode(root, 3);
    printLevelOrder(root);
    printf("\n");
    inOrder(root);
    return 0;
}
