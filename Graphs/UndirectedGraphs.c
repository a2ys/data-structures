// General Program : BFS, DFS, Dijkstra's, Prim's (use Prim's for Kruskal's also)
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 5
#define INF 0

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
int graph[MAX][MAX];

void addEdge(int u, int v, int w)
{
  graph[u][v] = w;
  graph[v][u] = w;
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
      {
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

int findShortestCycle(int v)
{
  int shortestCycle = INF;

  for (int start = 0; start < v; ++start)
  {
    int distance[MAX_VERTICES];
    int queue[MAX_VERTICES], front = 0, back = 0;

    for (int i = 0; i < v; ++i)
    {
      distance[i] = INF;
    }
    distance[start] = 0;
    queue[back++] = start;

    while (front < back)
    {
      int u = queue[front++];
      for (int dest = 0; dest < v; ++dest)
      {
        if (adjMatrix[u][dest] > 0)
        {
          if (distance[dest] == INF)
          {
            distance[dest] = distance[u] + adjMatrix[u][dest];
            queue[back++] = dest;
          }
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

  for (int i = 0; i < v; i++)
  {
    for (int j = 0; j < v; j++)
    {
      adjMatrix[i][j] = 0;
    }
  }

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

bool adjMatrix[MAX_V][MAX_V] = {false};
bool visited[MAX_V] = {false};

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
  for (int i = 0; i < V; i++)
  {
    if (!visited[i])
    {
      int component[MAX_V], count = 0;
      dfs(i, V, component, &count);
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

bool isBipartite(int G[MAX][MAX], int n, int src)
{
  int color[MAX];
  for (int i = 0; i < n; i++)
  {
    color[i] = UNCOLORED;
  }

  color[src] = RED;
  int queue[MAX];
  int front = 0, rear = 0;
  queue[rear++] = src;

  while (front != rear)
  {
    int u = queue[front++];

    for (int v = 0; v < n; v++)
    {
      if (G[u][v] == 1 && u == v)
      {
        return false;
      }

      if (G[u][v] == 1 && color[v] == UNCOLORED)
      {
        color[v] = (color[u] == RED) ? BLUE : RED;
        queue[rear++] = v;
      }
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

int isValid(int x, int y, int n, int m)
{
  return x >= 0 && x < n && y >= 0 && y < m;
}

int dfs(char matrix[MAX][MAX], int x, int y, int n, int m, char prevChar)
{
  int maxLength = 1;

  for (int i = 0; i < 8; i++)
  {
    int newX = x + directions[i][0];
    int newY = y + directions[i][1];

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

int findLongestPath(char matrix[MAX][MAX], int n, int m, char startChar)
{
  int longestPath = 0;

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

#define MAX_NODES 100'

int bfs(int V, int adj_matrix[MAX_NODES][MAX_NODES], int X)
{
  int visited[MAX_NODES] = {0};
  int level[MAX_NODES] = {-1};
  int queue[MAX_NODES], front = 0, rear = 0;

  visited[0] = 1;
  level[0] = 0;
  queue[rear++] = 0;

  while (front < rear)
  {
    int node = queue[front++];

    for (int i = 0; i < V; i++)
    {
      if (adj_matrix[node][i] == 1 && !visited[i])
      {
        visited[i] = 1;
        level[i] = level[node] + 1;
        queue[rear++] = i;

        if (i == X)
        {
          return level[i];
        }
      }
    }
  }

  return -1;
}

int main()
{
  int V, E;
  scanf("%d %d", &V, &E);

  int adj_matrix[MAX_NODES][MAX_NODES] = {0};

  for (int i = 0; i < E; i++)
  {
    int u, v;
    scanf("%d %d", &u, &v);
    adj_matrix[u][v] = 1;
    adj_matrix[v][u] = 1;
  }

  int X;
  scanf("%d", &X);

  int result = bfs(V, adj_matrix, X);

  printf("%d\n", result);

  return 0;
}

// Cycle checking with adjacency list

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node
{
  int vertex;
  struct Node *next;
} Node;

typedef struct Graph
{
  int numVertices;
  Node **adjList;
} Graph;

typedef struct Queue
{
  int items[MAX_VERTICES];
  int front;
  int rear;
} Queue;

Queue *createQueue()
{
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

int isEmpty(Queue *q)
{
  return q->rear == -1;
}

void enqueue(Queue *q, int value)
{
  if (q->rear == MAX_VERTICES - 1)
    return;
  if (q->front == -1)
    q->front = 0;
  q->rear++;
  q->items[q->rear] = value;
}

int dequeue(Queue *q)
{
  int item;
  if (isEmpty(q))
  {
    return -1;
  }
  else
  {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
    {
      q->front = q->rear = -1;
    }
  }
  return item;
}

Node *createNode(int vertex)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->vertex = vertex;
  newNode->next = NULL;
  return newNode;
}

Graph *createGraph(int vertices)
{
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->numVertices = vertices;

  graph->adjList = (Node **)malloc(vertices * sizeof(Node *));

  for (int i = 0; i < vertices; i++)
    graph->adjList[i] = NULL;

  return graph;
}

void addEdge(Graph *graph, int src, int dest)
{
  Node *newNode = createNode(dest);
  newNode->next = graph->adjList[src];
  graph->adjList[src] = newNode;

  newNode = createNode(src);
  newNode->next = graph->adjList[dest];
  graph->adjList[dest] = newNode;
}

int hasCycle(Graph *graph)
{
  int visited[MAX_VERTICES] = {0};

  for (int i = 0; i < graph->numVertices; i++)
  {
    if (!visited[i])
    {
      Queue *q = createQueue();
      int parent[MAX_VERTICES] = {-1};

      visited[i] = 1;
      enqueue(q, i);

      while (!isEmpty(q))
      {
        int current = dequeue(q);

        Node *temp = graph->adjList[current];
        while (temp)
        {
          int adjVertex = temp->vertex;

          if (!visited[adjVertex])
          {
            visited[adjVertex] = 1;
            parent[adjVertex] = current;
            enqueue(q, adjVertex);
          }
          else if (parent[current] != adjVertex)
          {
            return 1;
          }
          temp = temp->next;
        }
      }
      free(q);
    }
  }
  return 0;
}

int main()
{
  int V, E;
  printf("Enter the number of vertices: ");
  scanf("%d", &V);
  printf("Enter the number of edges: ");
  scanf("%d", &E);

  Graph *graph = createGraph(V);

  printf("Enter the edges (start and end nodes):\n");
  for (int i = 0; i < E; i++)
  {
    int src, dest;
    scanf("%d %d", &src, &dest);
    addEdge(graph, src, dest);
  }

  if (hasCycle(graph))
    printf("1\n");
  else
    printf("0\n");

  for (int i = 0; i < V; i++)
  {
    Node *temp = graph->adjList[i];
    while (temp)
    {
      Node *toFree = temp;
      temp = temp->next;
      free(toFree);
    }
  }
  free(graph->adjList);
  free(graph);

  return 0;
}

// Shortest path using BFS

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 7

typedef struct Queue
{
  int items[MAX_VERTICES];
  int front, rear;
} Queue;

Queue *createQueue()
{
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

int isEmpty(Queue *q)
{
  return q->rear == -1;
}

void enqueue(Queue *q, int value)
{
  if (q->rear == MAX_VERTICES - 1)
    return;
  if (q->front == -1)
    q->front = 0;
  q->rear++;
  q->items[q->rear] = value;
}

int dequeue(Queue *q)
{
  int item;
  if (isEmpty(q))
  {
    return -1;
  }
  else
  {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
    {
      q->front = q->rear = -1;
    }
  }
  return item;
}

void findShortestPath(int n, int adjMatrix[MAX_VERTICES][MAX_VERTICES], int source, int goal)
{
  if (source < 0 || source >= n || goal < 0 || goal >= n)
  {
    printf("Not found\n");
    return;
  }

  int visited[MAX_VERTICES] = {0};
  int parent[MAX_VERTICES];
  for (int i = 0; i < n; i++)
  {
    parent[i] = -1;
  }

  Queue *q = createQueue();
  visited[source] = 1;
  enqueue(q, source);

  int found = 0;

  while (!isEmpty(q) && !found)
  {
    int current = dequeue(q);

    for (int i = 0; i < n; i++)
    {
      if (adjMatrix[current][i] == 1 && !visited[i])
      {
        visited[i] = 1;
        parent[i] = current;
        enqueue(q, i);

        if (i == goal)
        {
          found = 1;
          break;
        }
      }
    }
  }

  if (!found)
  {
    printf("Not found\n");
    return;
  }

  int path[MAX_VERTICES];
  int pathLength = 0;
  for (int v = goal; v != -1; v = parent[v])
  {
    path[pathLength++] = v;
  }

  printf("%d\n", pathLength - 1);
  for (int i = pathLength - 1; i >= 0; i--)
  {
    printf("%d ", path[i]);
  }
  printf("\n");

  free(q);
}

int main()
{
  int n;
  printf("Enter the number of vertices: ");
  scanf("%d", &n);

  int adjMatrix[MAX_VERTICES][MAX_VERTICES];

  printf("Enter the adjacency matrix:\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      scanf("%d", &adjMatrix[i][j]);
    }
  }

  int source, goal;
  printf("Enter the source and goal vertices: ");
  scanf("%d %d", &source, &goal);

  findShortestPath(n, adjMatrix, source, goal);

  return 0;
}

// Minimum cost to connect all cities

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 100
#define INF INT_MAX

int minKey(int key[], int inMST[], int numCities)
{
  int min = INF, minIndex;
  for (int v = 0; v < numCities; v++)
  {
    if (inMST[v] == 0 && key[v] < min)
    {
      min = key[v];
      minIndex = v;
    }
  }
  return minIndex;
}

int primMST(int graph[MAX_CITIES][MAX_CITIES], int numCities)
{
  int parent[MAX_CITIES];
  int key[MAX_CITIES];
  int inMST[MAX_CITIES];

  for (int i = 0; i < numCities; i++)
  {
    key[i] = INF;
    inMST[i] = 0;
  }

  key[0] = 0;
  parent[0] = -1;

  int totalCost = 0;

  for (int count = 0; count < numCities - 1; count++)
  {
    int u = minKey(key, inMST, numCities);
    inMST[u] = 1;

    for (int v = 0; v < numCities; v++)
    {
      if (graph[u][v] != 0 && inMST[v] == 0 && graph[u][v] < key[v])
      {
        parent[v] = u;
        key[v] = graph[u][v];
      }
    }
  }

  for (int i = 1; i < numCities; i++)
  {
    totalCost += graph[i][parent[i]];
  }

  return totalCost;
}

int main()
{
  int numCities, numConnections;
  scanf("%d %d", &numCities, &numConnections);

  int graph[MAX_CITIES][MAX_CITIES];
  for (int i = 0; i < numCities; i++)
  {
    for (int j = 0; j < numCities; j++)
    {
      graph[i][j] = 0;
    }
  }

  for (int i = 0; i < numConnections; i++)
  {
    int src, dest, cost;
    scanf("%d %d %d", &src, &dest, &cost);
    graph[src][dest] = cost;
    graph[dest][src] = cost;
  }

  int result = primMST(graph, numCities);
  printf("%d\n", result);

  return 0;
}

// Prim's MST with arrows

#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

int minKey(int key[], int inMST[], int V)
{
  int min = INF, minIndex;
  for (int v = 0; v < V; v++)
  {
    if (inMST[v] == 0 && key[v] < min)
    {
      min = key[v];
      minIndex = v;
    }
  }
  return minIndex;
}

void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int V)
{
  int parent[MAX_VERTICES];
  int key[MAX_VERTICES];
  int inMST[MAX_VERTICES];

  for (int i = 0; i < V; i++)
  {
    key[i] = INF;
    inMST[i] = 0;
  }

  key[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < V - 1; count++)
  {
    int u = minKey(key, inMST, V);
    inMST[u] = 1;

    for (int v = 0; v < V; v++)
    {
      if (graph[u][v] && inMST[v] == 0 && graph[u][v] < key[v])
      {
        parent[v] = u;
        key[v] = graph[u][v];
      }
    }
  }

  int totalCost = 0;
  printf("Edges in the constructed MST:\n");
  for (int i = 1; i < V; i++)
  {
    printf("%d -- %d == %d\n", parent[i], i, graph[i][parent[i]]);
    totalCost += graph[i][parent[i]];
  }
  printf("Minimum Spanning Tree cost: %d\n", totalCost);
}

int main()
{
  int V, E;
  scanf("%d %d", &V, &E);

  int graph[MAX_VERTICES][MAX_VERTICES];
  for (int i = 0; i < V; i++)
  {
    for (int j = 0; j < V; j++)
    {
      graph[i][j] = INF;
    }
  }

  for (int i = 0; i < E; i++)
  {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    graph[u][v] = w;
    graph[v][u] = w;
  }

  primMST(graph, V);

  return 0;
}

// Kruskal's MST with arrows

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 999999

typedef struct
{
  int u, v, weight;
} Edge;

int parent[MAX_VERTICES], rank[MAX_VERTICES];

int find(int i)
{
  if (parent[i] == i)
    return i;
  return parent[i] = find(parent[i]);
}

void unionSets(int u, int v)
{
  int rootU = find(u);
  int rootV = find(v);

  if (rootU != rootV)
  {
    if (rank[rootU] > rank[rootV])
    {
      parent[rootV] = rootU;
    }
    else if (rank[rootU] < rank[rootV])
    {
      parent[rootU] = rootV;
    }
    else
    {
      parent[rootV] = rootU;
      rank[rootU]++;
    }
  }
}

void kruskalMST(int graph[MAX_VERTICES][MAX_VERTICES], int V, int E)
{
  Edge edges[E];
  int edgeCount = 0;

  for (int i = 0; i < V; i++)
  {
    for (int j = i + 1; j < V; j++)
    {
      if (graph[i][j] != INF)
      {
        edges[edgeCount].u = i;
        edges[edgeCount].v = j;
        edges[edgeCount].weight = graph[i][j];
        edgeCount++;
      }
    }
  }

  for (int i = 0; i < edgeCount - 1; i++)
  {
    for (int j = i + 1; j < edgeCount; j++)
    {
      if (edges[i].weight > edges[j].weight)
      {
        Edge temp = edges[i];
        edges[i] = edges[j];
        edges[j] = temp;
      }
    }
  }

  for (int i = 0; i < V; i++)
  {
    parent[i] = i;
    rank[i] = 0;
  }

  int mstWeight = 0;
  printf("Edges in the constructed MST:\n");
  for (int i = 0; i < edgeCount; i++)
  {
    int u = edges[i].u;
    int v = edges[i].v;
    int weight = edges[i].weight;

    if (find(u) != find(v))
    {
      unionSets(u, v);
      printf("%d -- %d == %d\n", u, v, weight);
      mstWeight += weight;
    }
  }

  printf("Minimum Spanning Tree cost: %d\n", mstWeight);
}

int main()
{
  int V, E;
  scanf("%d %d", &V, &E);

  int graph[MAX_VERTICES][MAX_VERTICES];

  for (int i = 0; i < V; i++)
  {
    for (int j = 0; j < V; j++)
    {
      graph[i][j] = INF;
    }
  }

  for (int i = 0; i < E; i++)
  {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    graph[u][v] = w;
    graph[v][u] = w;
  }

  kruskalMST(graph, V, E);

  return 0;
}

// Kruskal's MST ALL PATHS

#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 20
#define INF 9999

typedef struct
{
  int u, v, weight;
} Edge;

typedef struct
{
  int parent[MAX_CITIES];
  int rank[MAX_CITIES];
} DisjointSet;

void initializeDSU(DisjointSet *dsu, int N)
{
  for (int i = 0; i < N; i++)
  {
    dsu->parent[i] = i;
    dsu->rank[i] = 0;
  }
}

int find(DisjointSet *dsu, int i)
{
  if (dsu->parent[i] != i)
  {
    dsu->parent[i] = find(dsu, dsu->parent[i]);
  }
  return dsu->parent[i];
}

void unionSets(DisjointSet *dsu, int u, int v)
{
  int rootU = find(dsu, u);
  int rootV = find(dsu, v);

  if (rootU != rootV)
  {
    if (dsu->rank[rootU] < dsu->rank[rootV])
    {
      dsu->parent[rootU] = rootV;
    }
    else if (dsu->rank[rootU] > dsu->rank[rootV])
    {
      dsu->parent[rootV] = rootU;
    }
    else
    {
      dsu->parent[rootV] = rootU;
      dsu->rank[rootU]++;
    }
  }
}

void kruskalMST(int cost[MAX_CITIES][MAX_CITIES], int N)
{
  Edge edges[MAX_CITIES * (MAX_CITIES - 1) / 2];
  int edgeCount = 0;

  for (int i = 0; i < N; i++)
  {
    for (int j = i + 1; j < N; j++)
    {
      if (cost[i][j] != INF)
      {
        edges[edgeCount].u = i;
        edges[edgeCount].v = j;
        edges[edgeCount].weight = cost[i][j];
        edgeCount++;
      }
    }
  }

  for (int i = 0; i < edgeCount - 1; i++)
  {
    for (int j = i + 1; j < edgeCount; j++)
    {
      if (edges[i].weight > edges[j].weight)
      {
        Edge temp = edges[i];
        edges[i] = edges[j];
        edges[j] = temp;
      }
    }
  }

  DisjointSet dsu;
  initializeDSU(&dsu, N);

  int mstCost = 0;
  int mstEdges = 0;

  printf("Edges in the Minimum Spanning Tree:\n");

  for (int i = 0; i < edgeCount && mstEdges < N - 1; i++)
  {
    int u = edges[i].u;
    int v = edges[i].v;
    int weight = edges[i].weight;

    if (find(&dsu, u) != find(&dsu, v))
    {
      printf("%d -> %d\n", u + 1, v + 1);
      unionSets(&dsu, u, v);
      mstCost += weight;
      mstEdges++;
    }
  }

  printf("Minimum Spanning Tree cost: %d\n", mstCost);
}

int main()
{
  int N;
  scanf("%d", &N);

  int cost[MAX_CITIES][MAX_CITIES];

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      scanf("%d", &cost[i][j]);
      if (cost[i][j] == 0 && i != j)
      {
        cost[i][j] = INF;
      }
    }
  }

  kruskalMST(cost, N);

  return 0;
}

// Program to check if N - 1 edges were added

#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 10
#define INF 9999

typedef struct
{
  int u, v, weight;
} Edge;

typedef struct
{
  int parent[MAX_CITIES];
  int rank[MAX_CITIES];
} DisjointSet;

void initializeDSU(DisjointSet *dsu, int N)
{
  for (int i = 0; i < N; i++)
  {
    dsu->parent[i] = i;
    dsu->rank[i] = 0;
  }
}

int find(DisjointSet *dsu, int i)
{
  if (dsu->parent[i] != i)
  {
    dsu->parent[i] = find(dsu, dsu->parent[i]);
  }
  return dsu->parent[i];
}

void unionSets(DisjointSet *dsu, int u, int v)
{
  int rootU = find(dsu, u);
  int rootV = find(dsu, v);

  if (rootU != rootV)
  {
    if (dsu->rank[rootU] < dsu->rank[rootV])
    {
      dsu->parent[rootU] = rootV;
    }
    else if (dsu->rank[rootU] > dsu->rank[rootV])
    {
      dsu->parent[rootV] = rootU;
    }
    else
    {
      dsu->parent[rootV] = rootU;
      dsu->rank[rootU]++;
    }
  }
}

int compareEdges(const void *a, const void *b)
{
  Edge *edgeA = (Edge *)a;
  Edge *edgeB = (Edge *)b;
  return edgeA->weight - edgeB->weight;
}

int kruskalMST(Edge edges[], int N, int M)
{
  qsort(edges, M, sizeof(Edge), compareEdges);

  DisjointSet dsu;
  initializeDSU(&dsu, N);

  int mstCost = 0;
  int mstEdges = 0;

  for (int i = 0; i < M && mstEdges < N - 1; i++)
  {
    int u = edges[i].u;
    int v = edges[i].v;
    int weight = edges[i].weight;

    if (find(&dsu, u) != find(&dsu, v))
    {
      unionSets(&dsu, u, v);
      mstCost += weight;
      mstEdges++;
    }
  }

  if (mstEdges == N - 1)
  {
    return mstCost;
  }
  else
  {
    return -1;
  }
}

int main()
{
  int N, M;
  scanf("%d", &N);
  scanf("%d", &M);

  Edge edges[M];

  for (int i = 0; i < M; i++)
  {
    int u, v, weight;
    scanf("%d %d %d", &u, &v, &weight);
    edges[i].u = u;
    edges[i].v = v;
    edges[i].weight = weight;
  }

  int mstCost = kruskalMST(edges, N, M);

  if (mstCost == -1)
  {
    printf("It is not possible to connect all cities.\n");
  }
  else
  {
    printf("%d\n", mstCost);
  }

  return 0;
}

// Prims to display edges and weights

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_V 10

int minKey(int key[], bool mstSet[], int V)
{
  int min = INT_MAX, min_index;

  for (int v = 0; v < V; v++)
    if (!mstSet[v] && key[v] < min)
      min = key[v], min_index = v;

  return min_index;
}

void printMST(int parent[], int graph[MAX_V][MAX_V], int V)
{
  printf("Edge   Weight\n");
  for (int i = 1; i < V; i++)
    printf("%d - %d    %d\n", parent[i], i, graph[i][parent[i]]);
}

void primMST(int graph[MAX_V][MAX_V], int V)
{
  int parent[MAX_V];
  int key[MAX_V];
  bool mstSet[MAX_V];

  for (int i = 0; i < V; i++)
    key[i] = INT_MAX, mstSet[i] = false;

  key[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < V - 1; count++)
  {
    int u = minKey(key, mstSet, V);

    mstSet[u] = true;

    for (int v = 0; v < V; v++)
      if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
        parent[v] = u, key[v] = graph[u][v];
  }

  printMST(parent, graph, V);
}

int main()
{
  int V;
  scanf("%d", &V);

  int graph[MAX_V][MAX_V];

  for (int i = 0; i < V; i++)
  {
    for (int j = 0; j < V; j++)
    {
      scanf("%d", &graph[i][j]);
    }
  }

  primMST(graph, V);

  return 0;
}

// Kruskal's with minimum cost and all the paths

#include <stdio.h>
#include <stdlib.h>

#define MAX_ROADS 45

typedef struct
{
  int u, v, cost;
} Edge;

Edge edges[MAX_ROADS];
int parent[10];

int find(int i)
{
  if (parent[i] == i)
    return i;
  return parent[i] = find(parent[i]);
}

void unionSets(int u, int v)
{
  int rootU = find(u);
  int rootV = find(v);
  if (rootU != rootV)
  {
    parent[rootV] = rootU;
  }
}

int compareEdges(const void *a, const void *b)
{
  return ((Edge *)a)->cost - ((Edge *)b)->cost;
}

void kruskalMST(int N, int R)
{
  int totalCost = 0;
  int edgesInMST = 0;

  for (int i = 0; i < N; i++)
  {
    parent[i] = i;
  }

  qsort(edges, R, sizeof(Edge), compareEdges);

  printf("Minimum Spanning Tree:\n");

  for (int i = 0; i < R && edgesInMST < N - 1; i++)
  {
    Edge currentEdge = edges[i];
    int u = currentEdge.u;
    int v = currentEdge.v;
    int cost = currentEdge.cost;

    if (find(u) != find(v))
    {
      unionSets(u, v);
      printf("Building %d - Building %d: %d\n", u, v, cost);
      totalCost += cost;
      edgesInMST++;
    }
  }

  printf("Total Cost for Installation: %d\n", totalCost);
}

int main()
{
  int N, R;

  printf("Enter the number of buildings: ");
  scanf("%d", &N);

  printf("Enter the number of roads: ");
  scanf("%d", &R);

  printf("Enter the roads with their costs:\n");
  for (int i = 0; i < R; i++)
  {
    scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].cost);
  }

  kruskalMST(N, R);

  return 0;
}

// Prims with minimum cost and all the paths

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_CITIES 8

int findMinKey(int key[], bool mstSet[], int n)
{
  int min = INT_MAX, minIndex;

  for (int v = 0; v < n; v++)
  {
    if (!mstSet[v] && key[v] < min)
    {
      min = key[v];
      minIndex = v;
    }
  }
  return minIndex;
}

void primMST(int costMatrix[MAX_CITIES][MAX_CITIES], int n)
{
  int parent[MAX_CITIES];
  int key[MAX_CITIES];
  bool mstSet[MAX_CITIES];

  for (int i = 0; i < n; i++)
  {
    key[i] = INT_MAX;
    mstSet[i] = false;
  }

  key[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < n - 1; count++)
  {
    int u = findMinKey(key, mstSet, n);
    mstSet[u] = true; // Add the city to the MST set

    for (int v = 0; v < n; v++)
    {
      if (costMatrix[u][v] && !mstSet[v] && costMatrix[u][v] < key[v])
      {
        parent[v] = u;
        key[v] = costMatrix[u][v];
      }
    }
  }

  int totalCost = 0;
  printf("Minimum Spanning Tree:\n");

  for (int i = 1; i < n; i++)
  {
    printf("Edge %d:(%d %d) cost:%d\n", i, parent[i] + 1, i + 1, costMatrix[i][parent[i]]);
    totalCost += costMatrix[i][parent[i]];
  }

  printf("Minimum cost = %d\n", totalCost);
}

int main()
{
  int n;
  int costMatrix[MAX_CITIES][MAX_CITIES];

  printf("Enter the number of cities: ");
  scanf("%d", &n);

  printf("Enter the cost matrix:\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      scanf("%d", &costMatrix[i][j]);
    }
  }

  primMST(costMatrix, n);

  return 0;
}
