#include <stdio.h>
#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

int isQueueFull() {
  return rear == MAX - 1;
}

int isQueueEmpty() {
  return front == -1 || front > rear;
}

void enqueue(int value) {
  if (isQueueFull()) {
    printf("Queue Overflow\n");
    return;
  }
  if (front == -1) front = 0;
  queue[++rear] = value;
}

int dequeue() {
  if (isQueueEmpty()) {
    printf("Queue Underflow\n");
    return -1;
  }
  return queue[front++];
}

void displayQueue() {
  if (isQueueEmpty()) {
    printf("Queue is empty\n");
    return;
  }
  for (int i = front; i <= rear; i++) {
    printf("%d ", queue[i]);
  }
  printf("\n");
}

int main() {
  enqueue(30);
  enqueue(40);
  displayQueue();
  dequeue();
  displayQueue();

  return 0;
}

