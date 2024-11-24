#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM_VERTICES 5
#define LARGE_NUMBER 100

void DFS(int startVertex, int graph[NUM_VERTICES][NUM_VERTICES], bool visited[NUM_VERTICES]) {
  visited[startVertex] = true;
  printf("%d ", startVertex);

  for (int i = 0; i < NUM_VERTICES; i++) {
    if (graph[startVertex][i] > 0 && !visited[i]) {
      DFS(i, graph, visited);
    }
  }
}

void BFS(int startVertex, int graph[NUM_VERTICES][NUM_VERTICES], bool visited[NUM_VERTICES]) {
  int queue[LARGE_NUMBER];
  int front = 0, rear = 0;
  
  queue[rear++] = startVertex;
  visited[startVertex] = true;

  while (front < rear) {
    int currentVertex = queue[front++];
    printf("%d ", currentVertex);

    for (int i = 0; i < NUM_VERTICES; i++) {
      if (graph[currentVertex][i] > 0 && !visited[i]) {
        queue[rear++] = i;
        visited[i] = true;
      }
    }
  }
}

void dijkstra(int startVertex, int graph[NUM_VERTICES][NUM_VERTICES], bool visited[NUM_VERTICES], int parent[NUM_VERTICES], int distance[NUM_VERTICES]) {
  // Initialization
  for (int i = 0; i < NUM_VERTICES; i++) {
    visited[i] = false;
    parent[i] = -1;
    distance[i] = INT_MAX;
  }

  // Distance Calculation
  distance[startVertex] = 0;
  
  for (int i = 0; i < NUM_VERTICES - 1; i++) {
    // Closest Vertex and Distance Selection
    int minimumDistance = INT_MAX, minimumIndex = -1;

    for (int j = 0; j < NUM_VERTICES; j++) {
      if (!visited[j] && distance[j] < minimumDistance) {
        minimumDistance = distance[j];
        minimumIndex = j;
      }
    }

    // If no vertex is reachable, break out of the loop
    if (minimumIndex == -1) break;

    printf("Visited: %d, Distance: %d\n", minimumIndex, minimumDistance);
    visited[minimumIndex] = true;

    // Update distances of adjacent vertices
    for (int j = 0; j < NUM_VERTICES; j++) {
      // Check adjacency and unvisited
      if (graph[minimumIndex][j] > 0 && !visited[j]) {
        int weight = graph[minimumIndex][j];
        if (distance[minimumIndex] + weight < distance[j]) {
          distance[j] = distance[minimumIndex] + weight;
          parent[j] = minimumIndex;
        }
      }
    }
  }
}

int main() {
  bool visited[NUM_VERTICES];
  int graph[NUM_VERTICES][NUM_VERTICES] = {
    {0, 10, 3, 0, 0},
    {0, 0, 1, 2, 0},
    {0, 4, 0, 8, 2},
    {0, 0, 0, 0, 7},
    {0, 0, 0, 9, 0}
  };

  for (int i = 0; i < NUM_VERTICES; i++) {
    visited[i] = false;
  }

  DFS(0, graph, visited);
  printf("\n");
  
  for (int i = 0; i < NUM_VERTICES; i++) {
    visited[i] = false;
  }

  BFS(0, graph, visited);
  printf("\n");

  int parent[NUM_VERTICES], distance[NUM_VERTICES];
  dijkstra(0, graph, visited, parent, distance);

  return 0;
}

