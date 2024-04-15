#include <stdio.h>
#include <stdlib.h>
/*binary search trees are trees where numbers from the left are always lesser than numbers to the right. this way if we
choose to insert, search, or perform other operations, we can do it efficiently by only looking at one side of the tree.
efectively cutting each step in halve.*/
//we use a queue for the printLevelOrder function
//binary Search Tree node
typedef struct BstNode{
    int data;
    struct BstNode *left;
    struct BstNode *right;
}BstNode;
//queue node
typedef struct node{
    BstNode *data;
    struct node *next;
}node;
//queue ponters
node *front = NULL;
node *rear = NULL;

int isEmpty(){
    if(front){
        return 0;
    }
    return 1;
}

void enqueue(BstNode* x){
    node *temp = malloc(sizeof(node));
    temp->data = x;
    temp->next = NULL;
    if(isEmpty()){
        front = temp;
        rear = temp;
    }else{
        rear->next = temp;
        rear = temp;
    }
}

BstNode* dequeue(){
    if(isEmpty()){
        printf("The queue is empty, the operation cant be done\n");
        return 0;
    }
    node *temp = front;
    BstNode *re = front->data;
    front = front->next;
    free(temp);
    return re;
}

BstNode* Front(){
    if(isEmpty()){
        printf("The queue is empty, the operation cant be done\n");
        return 0;
    }
    return front->data;
}
//create new binary search tree node
BstNode* getNewNode(int data){
    BstNode * temp = malloc(sizeof(BstNode));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
//if the number is lesser or equal to the root node, we go to the left of the tree else we go to the right. we do so until
//we reach null, then we create the new node and insert it to the previous call of the function
BstNode* insert(BstNode *root, int data){
    if(!root){//we reach null
        root = getNewNode(data); // we return the newly created node
    }else if(data <= root->data){
        root->left = insert(root->left, data); //after we have created the new node we link it to the last root that we passed to the function
    }else{
        root->right = insert(root->right, data);// same as above
    }
    return root;
}
//returns if the data exists in the list or not. we search to the right of the tree if the data is greater than the root's data
//else we go to the left. we do so until we find the element, or we find null, in wich case we return 0.
int search(BstNode *root, int data){
    if(!root){
        return 0;//doesent exist in the list
    }else if(data == root->data){
        return 1;//does exist
    }else if(data < root->data){
        return search(root->left, data);
    }else{
        return search(root->right, data);
    }
}
//we return the leftmost node's data
int findMin(BstNode* root){
    if(!root){
        printf("the tree is empty\n");
        return -1;
    }
    while(root->left){
        root = root->left;
    }
    return root->data;
}
//we return the rightmost node's data
int findMax(BstNode* root){
    if(!root){
        printf("the tree is Empty\n");
        return -1;
    }
    if(!root->right){
        return root->data;
    }
    return findMax(root->right);
}
//same as before, but done recursevly
int recursiveFindMin(BstNode *root){
    if(!root){
        printf("the tree is empty\n");
        return -1;
    }
    if(!root->left){
        return root->data;
    }
    return recursiveFindMin(root->left);
}
//we return -1 when the bottom of the tree has been reached, since we add 1 to the variable that goes further at the end we can find wich is the
//longest rout. its hard to explaing, grab a piece of paper and visualize it.
int findHeight(BstNode *root){
    if(!root){
        return -1;
    }
    int left = findHeight(root->left);
    int right = findHeight(root->right);
    if(left >= right){
        return left + 1;
    }
    return right + 1;
}
//this is a breadth-first traversal alorithm. we visit each node with same level first, the we move to lesser level(depth)
//we trverse the tree from top to bottom and from left to right, just like when reading a book
//we use a queue to store the next data to print.
//we first add the root to the queue, then we print the data of the top of the queue,
//then we add the left child(if it exist) to the queue, and then the right child(if it exist)
//we then deque, and then we repeat the proces, starting by printing the top of the queue.
//this is pretty clever, grab a sheet of paper a visualize it.
void printLevelOrder(BstNode *root){
    if(!root){
        printf("the tree is empty\n");
    }else{
        enqueue(root);
        while(!isEmpty()){
            printf("%d, ", Front()->data);
            if(Front()->left){
                enqueue(Front()->left);
            }
            if(Front()->right){
                enqueue(Front()->right);
            }
            dequeue();
        }
    }
}
//this is a Depth-fist traversal algorithm. we fist visit the children.
//prints the data in the tree in the order of: root, left, right.
void preOrder(BstNode *root){
    if(root){
        printf("%d, ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}
//this is a Depth-fist traversal algorithm. we fist visit the children.
//prints the data in the tree in the order of: left, root, right. this prints the elements in order of greatness
void inOrder(BstNode *root){
    if(root){
        inOrder(root->left);
        printf("%d, ", root->data);
        inOrder(root->right);
    }
}
//this is a Depth-fist traversal algorithm. we fist visit the children.
//prints the data in the tree in the order of: left, right, root
void postOrder(BstNode *root){
    if(root){
        postOrder(root->left);
        postOrder(root->right);
        printf("%d, ", root->data);
    }
}
//used for inefficientIsBinarySearchTree
//compares the value of the root node to all its pregenitors
int isSubTreeLesser(BstNode *root, int value){
    if(!root){
        return 1;
    }
    if(root->data <= value
        && isSubTreeLesser(root->left, value)
        && isSubTreeLesser(root->right, value)){
            return 1;
    }
    return 0;
}
//used for inefficientIsBinarySearchTree
//compares the value of the root node to all its pregenitors
int isSubTreeGreater(BstNode *root, int value){
    if(!root){
        return 1;
    }
    if(root->data > value
        && isSubTreeGreater(root->left, value)
        && isSubTreeGreater(root->right, value)){
            return 1;
    }
    return 0;
}
//it determines if the tree is a binary search tree or not
//it calles the above methods to know if the left subtree only contains lesser values to the root, and if the right subtree only
//contains greater values than the root. then it repeats the proces for both the left subtree and the right subtree.
//this is very inefficient because it visits a node several times until that node becomes the root.
int inefficientIsBinarySearchTree(BstNode *root){
    if(!root){
        return 1;
    }
    if(isSubTreeLesser(root->left, root->data)
        && isSubTreeGreater(root->right, root->data)
        && inefficientIsBinarySearchTree(root->left)
        && inefficientIsBinarySearchTree(root->right)){
            return 1;
        }
    return 0;
}

//it is used for the "isBinarySearchTree" function
//it determines if the tree is a binary search tree or not. this is done efficiently unlike the inefficientIsBinarySearchTree function
//we have a range to compare, this way we do not have to repetedly visit the same node.
//our initial range is (-32767, 32767)the limits of the int data type.
//then if we are checking the left subtree, we diminish the maxVale to the root-data(the data of the root),
//and if we are checking the right subtree, we increse the minValue to be the root->data.
int isBstUtil(BstNode *root, int minValue, int maxValue){
    if(!root){
        return 1;
    }
    if(root->data > minValue && root->data <= maxValue
        && isBstUtil(root->left, minValue, root->data)
        && isBstUtil(root->right, root->data, maxValue)){
            return 1;
    }
    return 0;
}
//it determines if the tree is a binary search tree or not. this is done efficiently unlike the inefficientIsBinarySearchTree function
//we just call the isBstUtil function with specific parameters to make the calling of the function simpler.
int isBinarySearchTree(BstNode *root){
    return isBstUtil(root, -32767, 32767);
}
//this deletes a node in a binary search tree.
//we fist navigate to the node to delete recursevly, similar to what we did in the search function
//there are 3 cases.
//case 1: if the node doesnt have any children, then we simply free the node, and we set node to NULL so that when the function returns to the previous function call,
//it updates the link to NULL.
//case 2: if the node has only one child. then we create a BstNode pointer and set it = root, then we set root = root's child, so that the link is updated when the function ends
//then we free the created bstNode pointer.
//case 3: when the node has to children. we have 2 choices. to select the greatest value in the left subtree or to select the lesser value in the right subtree
//once we have made our choice, we set the node's data that we want to eliminate = the the value we selected previously.
//then we repeat the process recursevly but this time to eliminate the node we selected to replace the original node to delete
//we repeat the proces until we reach one of the other too cases.
BstNode* Delete(BstNode *root, int data){
    if(!root){
        return NULL;
    }
    if(root->data > data){
        root->left = Delete(root->left, data);
    }else if(root->data < data){
        root->right = Delete(root->right, data);
    }else{
        if(!root->right && !root->left){
            free(root);
            root = NULL;
        }else if(!root->left && root->right){
            BstNode *temp = root;
            root = root->right;
            free(temp);
        }else if(!root->right && root->left){
            BstNode *temp = root;
            root = root->left;
            free(temp);
        }else{
            int min = findMin(root->right);
            root->data = min;
            root->right = Delete(root->right, min);
        }
    }
    return root;
}
//searches the tree and returns the node
BstNode* Find(BstNode *root, int data){
    if(root){
        if(data < root->data){
            root = Find(root->left, data);
        }else if(data > root->data){
            root = Find(root->right, data);
        }
        return root;
    }else{
        return NULL;
    }
}
//it return the next value(in order of greatness) to the value input as parameter.
//we first search the tree for the node containing the input data. then we act depending on the case
//there are 2 cases.
//case 1: when the input node has a right subtree, we simply return the smalles value in that subtree, since its grater than the input node, and leeser than all the other greater nodes
//case 2: if the node doesent have a right subtree. we want to localize the most proximal parent node that is greater than the input node
//visualizing that would be localizing the parent node which makes a right turn going upwards(if there is any).
//since we cant traverse the tree from the bottom up, we trverse the tree from the top down. we create a variable that will contain the the succesor node and we initialize it to NULL
//while the visited node is greater than the input node we move to the left of the tree and we store it in the variable "succesor".
//else if the visited node is lesser than the input node, we move to the right, and continue the while loop
//if the visited node is equal the input node, we know that there is no succesor.
//that way will end up with the succesor node in the variable. then we simply return it.
int findSuccesor(BstNode *root, int data){
    BstNode* curr = Find(root, data);
    if(!curr){
        return data;
    }
    if(curr->right){
        return findMin(curr->right);
    }
    int succesor = data;
    while(root != curr){
        if(root->data > data){
            succesor = root->data;
            root = root->left;
        }else{
            root = root->right;
        }
    }
    return succesor;
}
//same thing as the above method but instead of returning the succesor, this returns the predecesor
int findPredecesor(BstNode *root, int data){
    BstNode* curr = Find(root, data);
    if(!curr){
        return data;
    }
    if(curr->left){
        return findMax(curr->left);
    }
    int predecesor = data;
    while(root != curr){
        if(root->data < data){
            predecesor = root->data;
            root = root->right;
        }else{
            root = root->left;
        }
    }
    return predecesor;
}

int main(){
    BstNode* root = NULL;  // Creating an empty tree
	/*Code to test the logic*/
	root = insert(root, 15);
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 25);
	root = insert(root, 8);
	root = insert(root, 12);
	root = insert(root, 11);
	root = insert(root, 13);
	if(isBinarySearchTree(root)){
        printf("the tree is a binary search tree\n");
	}else{
        printf("the tree is not a binary search tree\n");
	}
	printf("the minimal value in the binary search tree is: %d\n", findMin(root));
	printf("the height of the tree is: %d\n", findHeight(root));
	printf("level order print of the tree: ");
	printLevelOrder(root);
	printf("\npreorder print of the tree: ");
	preOrder(root);
	printf("\ninorder print of the tree: ");
	inOrder(root);
	printf("\npost order print of the tree: ");
	postOrder(root);
	int deletee = 15;
	root = Delete(root, deletee);
	printf("\nprint of the tree after deletion of %d: ", deletee);
	inOrder(root);
	int succesor = 13;
	printf("\nsuccesor of %d is: %d\n", succesor, findSuccesor(root, succesor));
	int predecesor = 25;
	printf("predecesor of %d is: %d\n", predecesor, findPredecesor(root, 25));
	printf("enter a number to be searched: ");
	int num;
	scanf("%d", &num);
	if(search(root, num)){
        printf("found it\n");
    }else{
        printf("not found\n");
    }
    return 0;
}
