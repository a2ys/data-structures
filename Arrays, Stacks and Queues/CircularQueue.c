#include <stdio.h>
#define MAX 100

int circularQueue[MAX];
int front = -1, rear = -1;

int isCircularQueueFull() {
  return (rear + 1) % MAX == front;
}

int isCircularQueueEmpty() {
  return front == -1;
}

void enqueueCircular(int value) {
  if (isCircularQueueFull()) {
    printf("Circular Queue Overflow\n");
    return;
  }
  if (isCircularQueueEmpty()) {
    front = 0;
    rear = 0;
  } else {
    rear = (rear + 1) % MAX;
  }
  circularQueue[rear] = value;
}

int dequeueCircular() {
  if (isCircularQueueEmpty()) {
    printf("Circular Queue Underflow\n");
    return -1;
  }
  int value = circularQueue[front];
  if (front == rear) {
    front = -1;
    rear = -1;
  } else {
    front = (front + 1) % MAX;
  }
  return value;
}

void displayCircularQueue() {
  if (isCircularQueueEmpty()) {
    printf("Circular Queue is empty\n");
    return;
  }
  int i = front;
  while (1) {
    printf("%d ", circularQueue[i]);
    if (i == rear) break;
    i = (i + 1) % MAX;
  }
  printf("\n");
}

int main() {
  enqueueCircular(70);
  enqueueCircular(80);
  displayCircularQueue();
  dequeueCircular();
  displayCircularQueue();

  return 0;
}

