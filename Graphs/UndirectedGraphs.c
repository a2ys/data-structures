#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 5
#define INF 0 // 0 to represent no edge between two vertices

typedef struct Graph
{
  int numVertices;
  int **adjMatrix;
} Graph;

// Creating a graph
struct Graph *createGraph(int V)
{
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->numVertices = V;

  graph->adjMatrix = (int **)malloc(V * sizeof(int *));

  for (int i = 0; i < V; i++)
  {
    graph->adjMatrix[i] = (int *)malloc(V * sizeof(int));
    for (int j = 0; j < V; j++)
    {
      graph->adjMatrix[i][j] = 0;
    }
  }

  return graph;
}

// Adding an edge
void addEdge(Graph *graph, int source, int destination)
{
  graph->adjMatrix[source][destination] = 1;
  graph->adjMatrix[destination][source] = 1;
}

// Depth-first Search
void DFS(Graph *graph, int vertex, bool visited[])
{
  visited[vertex] = true;
  printf("%d ", vertex);

  for (int i = 0; i < graph->numVertices; i++)
  {
    if (graph->adjMatrix[vertex][i] == 1 && !visited[i])
    {
      DFS(graph, i, visited);
    }
  }
}

// Breadth-first search
void BFS(Graph *graph, int startVertex)
{
  bool visited[MAX_VERTICES] = {false};
  int queue[graph->numVertices];
  int front = 0, rear = 0;

  visited[startVertex] = true;
  queue[rear++] = startVertex;

  while (front < rear)
  {
    int currentVertex = queue[front++];
    printf("%d ", currentVertex);

    for (int i = 0; i < graph->numVertices; i++)
    {
      if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i])
      {
        queue[rear++] = i;
        visited[i] = true;
      }
    }
  }
}

// Parts of Dijkstra's Algorithm
int findMinDistance(int distance[], int visited[])
{
  int min = INT_MAX, minIndex;

  for (int v = 0; v < MAX_VERTICES; v++)
  {
    if (!visited[v] && distance[v] <= min)
    {
      min = distance[v];
      minIndex = v;
    }
  }

  return minIndex;
}

// Dijkstra's Algorithm for weighted graphs
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int source)
{
  int distance[MAX_VERTICES];
  int visited[MAX_VERTICES];

  for (int i = 0; i < MAX_VERTICES; i++)
  {
    distance[i] = INT_MAX;
    visited[i] = false;
  }

  distance[source] = 0;

  for (int i = 0; i < MAX_VERTICES - 1; i++)
  {
    int u = findMinDistance(distance, visited);
    visited[u] = true;

    for (int v = 0; v < MAX_VERTICES; v++)
    {
      if (!visited[v] && graph[u][v] && distance[u] != INT_MAX &&
          distance[u] + graph[u][v] < distance[v])
      {
        distance[v] = distance[u] + graph[u][v];
      }
    }
  }

  printf("Vertex\tDistance From Source\n");
  for (int i = 0; i < MAX_VERTICES; i++)
  {
    printf("%d\t%d\n", i, distance[i]);
  }
}

// Part of Prim's Algorithm
int findMinKey(int key[], bool inMST[])
{
  int min = INT_MAX, minIndex;

  for (int v = 0; v < MAX_VERTICES; v++)
  {
    if (!inMST[v] && key[v] < min)
    {
      min = key[v];
      minIndex = v;
    }
  }

  return minIndex;
}

void primMST(int graph[MAX_VERTICES][MAX_VERTICES])
{
  int parent[MAX_VERTICES];
  int key[MAX_VERTICES];
  bool inMST[MAX_VERTICES];

  for (int i = 0; i < MAX_VERTICES; i++)
  {
    key[i] = INT_MAX;
    inMST[i] = false;
  }

  key[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < MAX_VERTICES - 1; count++)
  {
    int u = findMinKey(key, inMST);
    inMST[u] = true;

    for (int v = 0; v < MAX_VERTICES; v++)
    {
      if (graph[u][v] && !inMST[v] && graph[u][v] < key[v])
      {
        parent[v] = u;
        key[v] = graph[u][v];
      }
    }
  }

  printMST(parent, graph);
}

void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES])
{
  printf("Edge\tWeight\n");
  for (int i = 1; i < MAX_VERTICES; i++)
  {
    printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
  }
}

void printAdjMatrix(Graph *graph)
{
  for (int i = 0; i < graph->numVertices; i++)
  {
    for (int j = 0; j < graph->numVertices; j++)
    {
      printf("%d ", graph->adjMatrix[i][j]);
    }

    printf("\n");
  }
}

int main()
{
  struct Graph *graph = createGraph(MAX_VERTICES);
  addEdge(graph, 0, 1);
  addEdge(graph, 0, 4);
  addEdge(graph, 1, 2);
  addEdge(graph, 1, 3);
  addEdge(graph, 1, 4);
  addEdge(graph, 2, 3);
  addEdge(graph, 3, 4);

  bool visited[MAX_VERTICES] = {false};
  int vertex = 0;

  printf("DFS starting from vertex 0:\n");
  DFS(graph, 0, visited);

  printf("\n");

  printf("BFS starting from vertex 0:\n");
  BFS(graph, 0);

  // Example directed graph represented with an adjacency matrix
  int newGraph[MAX_VERTICES][MAX_VERTICES] = {
      {0, 10, 3, 0, 0},
      {0, 0, 1, 2, 0},
      {0, 4, 0, 8, 2},
      {0, 0, 0, 0, 7},
      {0, 0, 0, 9, 0}};

  int source = 0;
  printf("\nDijkstra's Shortest Path for Directed Graph starting from vertex %d:\n", source);
  dijkstra(newGraph, source);

  int newGraph2[MAX_VERTICES][MAX_VERTICES] = {
      {0, 2, 0, 6, 0},
      {2, 0, 3, 8, 5},
      {0, 3, 0, 0, 7},
      {6, 8, 0, 0, 9},
      {0, 5, 7, 9, 0}};

  printf("Prim's Minimum Spanning Tree:\n");
  primMST(newGraph2);

  return 0;
}

// Path printing Dijkstra's Algorithm

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int dist[MAX], prev[MAX], visited[MAX];
int graph[MAX][MAX]; // Adjacency matrix to represent the graph

void addEdge(int u, int v, int w)
{
  graph[u][v] = w;
  graph[v][u] = w; // Assuming undirected graph
}

void dijkstra(int source, int n)
{
  for (int i = 0; i < n; i++)
  {
    dist[i] = INT_MAX;
    visited[i] = 0;
    prev[i] = -1;
  }
  dist[source] = 0;

  for (int i = 0; i < n - 1; i++)
  {
    int minDist = INT_MAX, minIndex = -1;
    for (int j = 0; j < n; j++)
    {
      if (!visited[j] && dist[j] < minDist)
      {
        minDist = dist[j];
        minIndex = j;
      }
    }
    visited[minIndex] = 1;

    for (int j = 0; j < n; j++)
    {
      if (graph[minIndex][j] != 0 && !visited[j])
      { // Check for edges
        int weight = graph[minIndex][j];
        if (dist[minIndex] + weight < dist[j])
        {
          dist[j] = dist[minIndex] + weight;
          prev[j] = minIndex;
        }
      }
    }
  }
}

void printPath(int destination)
{
  if (prev[destination] == -1)
  {
    printf("No path found\n");
    return;
  }
  int path[MAX], pathIndex = 0;
  for (int v = destination; v != -1; v = prev[v])
  {
    path[pathIndex++] = v;
  }
  printf("Shortest path: ");
  for (int i = pathIndex - 1; i > 0; i--)
  {
    printf("%d -> ", path[i]);
  }
  printf("%d\n", path[0]);
  printf("Shortest distance: %d\n", dist[destination]);
}

int main()
{
  int n, m, u, v, w, s, d;
  scanf("%d", &n);
  scanf("%d", &m);

  // Initialize the graph with 0s
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      graph[i][j] = 0;
    }
  }

  for (int i = 0; i < m; i++)
  {
    scanf("%d %d %d", &u, &v, &w);
    addEdge(u, v, w);
  }

  scanf("%d", &s);
  scanf("%d", &d);

  dijkstra(s, n);
  printPath(d);

  return 0;
}

// Cycle detection
#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 5
#define INF INT_MAX

int adjMatrix[MAX_VERTICES][MAX_VERTICES];

// Function to find the shortest cycle in the graph
int findShortestCycle(int v)
{
  int shortestCycle = INF;

  // Iterate over each vertex as the starting point
  for (int start = 0; start < v; ++start)
  {
    int distance[MAX_VERTICES];
    int queue[MAX_VERTICES], front = 0, back = 0;

    // Initialize distances to INF and queue
    for (int i = 0; i < v; ++i)
    {
      distance[i] = INF;
    }
    distance[start] = 0;
    queue[back++] = start;

    // Perform BFS from the start vertex
    while (front < back)
    {
      int u = queue[front++];
      for (int dest = 0; dest < v; ++dest)
      {
        if (adjMatrix[u][dest] > 0)
        { // Check for an edge
          // If dest is not visited yet
          if (distance[dest] == INF)
          {
            distance[dest] = distance[u] + adjMatrix[u][dest];
            queue[back++] = dest;
          }
          // If a cycle is found (back to start)
          else if (distance[u] + adjMatrix[u][dest] < shortestCycle)
          {
            shortestCycle = distance[u] + adjMatrix[u][dest];
          }
        }
      }
    }
  }

  return (shortestCycle == INF) ? -1 : shortestCycle;
}

int main()
{
  int v, e;
  printf("Enter the number of vertices: ");
  scanf("%d", &v);
  printf("Enter the number of edges: ");
  scanf("%d", &e);

  // Initialize adjacency matrix with 0 (no edges)
  for (int i = 0; i < v; i++)
  {
    for (int j = 0; j < v; j++)
    {
      adjMatrix[i][j] = 0;
    }
  }

  // Read edges
  printf("Enter edges in format (source destination weight):\n");
  for (int i = 0; i < e; i++)
  {
    int src, dest, weight;
    scanf("%d %d %d", &src, &dest, &weight);
    adjMatrix[src][dest] = weight;
  }

  int result = findShortestCycle(v);
  if (result == -1)
  {
    printf("No cycle found in the graph.\n");
  }
  else
  {
    printf("Length of the shortest cycle: %d\n", result);
  }

  return 0;
}

// Connected Components

#include <stdio.h>
#include <stdbool.h>

#define MAX_V 10

// Global variables for adjacency matrix and visited array
bool adjMatrix[MAX_V][MAX_V] = {false};
bool visited[MAX_V] = {false};

// DFS function to explore all nodes connected to 'v'
void dfs(int v, int V, int *component, int *count)
{
  visited[v] = true;
  component[(*count)++] = v;
  for (int i = 0; i < V; i++)
  {
    if (adjMatrix[v][i] && !visited[i])
    {
      dfs(i, V, component, count);
    }
  }
}

int main()
{
  int V;
  printf("Enter the number of vertices: ");
  scanf("%d", &V);

  // Read edges and fill the adjacency matrix
  printf("Enter edges (enter -1 -1 to end):\n");
  while (1)
  {
    int u, v;
    scanf("%d %d", &u, &v);
    if (u == -1 && v == -1)
      break;
    adjMatrix[u][v] = true;
    adjMatrix[v][u] = true;
  }

  printf("Following are connected components:\n");
  // Iterate over each vertex to find connected components
  for (int i = 0; i < V; i++)
  {
    if (!visited[i])
    {
      int component[MAX_V], count = 0;
      dfs(i, V, component, &count);
      // Print the component
      for (int j = 0; j < count; j++)
      {
        printf("%d ", component[j]);
      }
      printf("\n");
    }
  }

  return 0;
}

// Bipartite Graph

#include <stdio.h>
#include <stdbool.h>

#define MAX 6
#define UNCOLORED -1
#define RED 0
#define BLUE 1

// Function to check if the graph is bipartite using BFS
bool isBipartite(int G[MAX][MAX], int n, int src)
{
  int color[MAX];
  for (int i = 0; i < n; i++)
  {
    color[i] = UNCOLORED; // Initially, all vertices are uncolored
  }

  // Start BFS from the source vertex
  color[src] = RED;
  int queue[MAX];
  int front = 0, rear = 0;
  queue[rear++] = src;

  while (front != rear)
  {
    int u = queue[front++];

    for (int v = 0; v < n; v++)
    {
      // Check for self-loop
      if (G[u][v] == 1 && u == v)
      {
        return false; // Self-loop means not bipartite
      }

      // If an adjacent vertex is uncolored, assign an alternate color and add to queue
      if (G[u][v] == 1 && color[v] == UNCOLORED)
      {
        color[v] = (color[u] == RED) ? BLUE : RED;
        queue[rear++] = v;
      }
      // If an adjacent vertex has the same color, then the graph is not bipartite
      else if (G[u][v] == 1 && color[v] == color[u])
      {
        return false;
      }
    }
  }

  return true;
}

int main()
{
  int n;
  printf("Enter the number of computers (nodes): ");
  scanf("%d", &n);

  int G[MAX][MAX];
  printf("Enter the adjacency matrix:\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      scanf("%d", &G[i][j]);
    }
  }

  int src;
  printf("Enter the source computer (starting node): ");
  scanf("%d", &src);

  if (isBipartite(G, n, src))
  {
    printf("Yes, the given graph is Bipartite\n");
  }
  else
  {
    printf("No, the given graph is not Bipartite\n");
  }

  return 0;
}

// Length of longest path

#include <stdio.h>

#define MAX 5

int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

// Function to check if a cell is within matrix bounds
int isValid(int x, int y, int n, int m)
{
  return x >= 0 && x < n && y >= 0 && y < m;
}

// Depth-First Search to find the longest consecutive path from a starting cell
int dfs(char matrix[MAX][MAX], int x, int y, int n, int m, char prevChar)
{
  int maxLength = 1;

  for (int i = 0; i < 8; i++)
  {
    int newX = x + directions[i][0];
    int newY = y + directions[i][1];

    // Check if the next cell has the consecutive character
    if (isValid(newX, newY, n, m) && matrix[newX][newY] == prevChar + 1)
    {
      int pathLength = 1 + dfs(matrix, newX, newY, n, m, matrix[newX][newY]);
      if (pathLength > maxLength)
      {
        maxLength = pathLength;
      }
    }
  }

  return maxLength;
}

// Function to find the longest path length starting from a specific character
int findLongestPath(char matrix[MAX][MAX], int n, int m, char startChar)
{
  int longestPath = 0;

  // Check each cell in the matrix for the starting character
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (matrix[i][j] == startChar)
      {
        int currentPathLength = dfs(matrix, i, j, n, m, startChar);
        if (currentPathLength > longestPath)
        {
          longestPath = currentPathLength;
        }
      }
    }
  }

  return longestPath;
}

int main()
{
  int n, m;
  printf("Enter the number of rows: ");
  scanf("%d", &n);
  printf("Enter the number of columns: ");
  scanf("%d", &m);

  char matrix[MAX][MAX];
  printf("Enter the matrix of characters:\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      scanf(" %c", &matrix[i][j]);
    }
  }

  char startChar;
  printf("Enter the starting character: ");
  scanf(" %c", &startChar);

  int longestPath = findLongestPath(matrix, n, m, startChar);
  printf("The length of the longest path with consecutive characters starting from character %c is %d\n", startChar, longestPath);

  return 0;
}

// Level of a node

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

// Function to perform BFS and find the level of node X
int bfs(int V, int adj_matrix[MAX_NODES][MAX_NODES], int X)
{
  int visited[MAX_NODES] = {0}; // visited array to keep track of visited nodes
  int level[MAX_NODES] = {-1};  // -1 means not reachable
  int queue[MAX_NODES], front = 0, rear = 0;

  // Start BFS from node 0
  visited[0] = 1;
  level[0] = 0;
  queue[rear++] = 0; // enqueue node 0

  while (front < rear)
  {
    int node = queue[front++]; // dequeue a node

    // Check all the neighbors of the current node
    for (int i = 0; i < V; i++)
    {
      if (adj_matrix[node][i] == 1 && !visited[i])
      {                             // if there is an edge
        visited[i] = 1;             // mark node as visited
        level[i] = level[node] + 1; // set the level of the neighbor node
        queue[rear++] = i;          // enqueue the neighbor node

        // If we reached the target node X, return the level
        if (i == X)
        {
          return level[i];
        }
      }
    }
  }

  return -1; // If the node X is not reachable
}

int main()
{
  int V, E;
  scanf("%d %d", &V, &E);

  // Initialize adjacency matrix
  int adj_matrix[MAX_NODES][MAX_NODES] = {0};

  // Read edges and fill the adjacency matrix
  for (int i = 0; i < E; i++)
  {
    int u, v;
    scanf("%d %d", &u, &v);
    adj_matrix[u][v] = 1;
    adj_matrix[v][u] = 1; // since it's an undirected graph
  }

  int X;
  scanf("%d", &X);

  // Call BFS function to find the level of node X
  int result = bfs(V, adj_matrix, X);

  // Output the result
  printf("%d\n", result);

  return 0;
}
