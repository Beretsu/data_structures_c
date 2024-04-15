#include <stdio.h>
#include <stdlib.h>

typedef struct adjListNode{
    int dest;
    struct adjListNode* next;
}adjListNode;

typedef struct adjList{
    adjListNode* head;
}adjList;

typedef struct{
    int numVertices;
    adjList* array;
}Graph;

adjListNode* getNewAdjListNode(int dest){
    adjListNode* node = malloc(sizeof(adjListNode));
    node->dest = dest;
    return node;
}

Graph* getNewGraph(int numVertices){
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->array = malloc(sizeof(adjList)*numVertices);
    for(int i = 0; i < numVertices; i++){
        graph->array[i].head = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest){
    adjListNode* node = getNewAdjListNode(dest);
    node->next = graph->array[src].head;
    graph->array[src].head = node;

    adjListNode* node2 = getNewAdjListNode(src);
    node2->next = graph->array[dest].head;
    graph->array[dest].head = node2;
}

void printGraph(Graph* graph){
    int n = graph->numVertices;
    for(int i = 0; i < n; i++){
        adjListNode* iterator = graph->array[i].head;
        printf("vertex %d's root", i);
        while(iterator){
            printf("-> %d", iterator->dest);
            iterator = iterator->next;
        }
        printf("\n");
    }
}

int main(){
    int numVertices = 5;
    Graph* graph = getNewGraph(numVertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    printGraph(graph);
    return 0;
}
