#include <stdio.h>
#define MAX 100

int deque[MAX];
int front = -1, rear = -1;

int isDequeFull() {
  return rear == MAX - 1;
}

int isDequeEmpty() {
  return front == -1 || front > rear;
}

void insertFront(int value) {
  if (front == 0) {
    printf("Deque Overflow at Front\n");
    return;
  }
  if (isDequeEmpty()) {
    front = 0;
    rear = 0;
  } else {
    front--;
  }
  deque[front] = value;
}

void insertRear(int value) {
  if (isDequeFull()) {
    printf("Deque Overflow at Rear\n");
    return;
  }
  if (isDequeEmpty()) {
    front = 0;
    rear = 0;
  } else {
    rear++;
  }
  deque[rear] = value;
}

int deleteFront() {
  if (isDequeEmpty()) {
    printf("Deque Underflow at Front\n");
    return -1;
  }
  int value = deque[front++];
  if (front > rear) front = rear = -1;
  return value;
}

int deleteRear() {
  if (isDequeEmpty()) {
    printf("Deque Underflow at Rear\n");
    return -1;
  }
  int value = deque[rear--];
  if (rear < front) front = rear = -1;
  return value;
}

void displayDeque() {
  if (isDequeEmpty()) {
    printf("Deque is empty\n");
    return;
  }
  for (int i = front; i <= rear; i++) {
    printf("%d ", deque[i]);
  }
  printf("\n");
}

int main() {
  insertFront(50);
  insertRear(60);
  displayDeque();
  deleteFront();
  displayDeque();
  deleteRear();
  displayDeque();

  return 0;
}

