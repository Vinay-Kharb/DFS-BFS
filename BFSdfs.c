#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Node 
{
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph 
{
    int numVertices;
    Node* adjList[MAX];
} Graph;

Node* createNode(int v) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) 
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    
    for (int i = 0; i < vertices; i++) 
    {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) 
{
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void bfs(Graph* graph, int startVertex) 
{
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    
    visited[startVertex] = 1;
    queue[rear++] = startVertex;
    
    printf("BFS Traversal: ");
    while (front < rear) 
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);
        
        Node* temp = graph->adjList[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) 
            {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

void dfsUtil(Graph* graph, int vertex, int visited[]) 
{
    visited[vertex] = 1;
    printf("%d ", vertex);
    
    Node* temp = graph->adjList[vertex];
    while (temp) 
    {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) 
        {
            dfsUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void dfs(Graph* graph, int startVertex) 
{
    int visited[MAX] = {0};
    printf("DFS Traversal: ");
    dfsUtil(graph, startVertex, visited);
    printf("\n");
}

int main() 
{
    int vertices, edges, src, dest, startVertex;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    
    Graph* graph = createGraph(vertices);
    
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter edges (source destination):\n");
    for (int i = 0; i < edges; i++) 
    {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
    
    printf("Enter the starting vertex for BFS and DFS: ");
    scanf("%d", &startVertex);
    
    bfs(graph, startVertex);
    dfs(graph, startVertex);
    
    return 0;
}