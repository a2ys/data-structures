#include <stdio.h>
#define MAX 100

int stack[MAX];
int top = -1;

int isStackFull() {
  return top == MAX - 1;
}

int isStackEmpty() {
  return top == -1;
}

void push(int value) {
  if (isStackFull()) {
    printf("Stack Overflow\n");
    return;
  }
  stack[++top] = value;
}

int pop() {
  if (isStackEmpty()) {
    printf("Stack Underflow\n");
    return -1;
  }
  return stack[top--];
}

void displayStack() {
  if (isStackEmpty()) {
    printf("Stack is empty\n");
    return;
  }
  for (int i = top; i >= 0; i--) {
    printf("%d ", stack[i]);
  }
  printf("\n");
}

int main() {
  push(10);
  push(20);
  displayStack();
  pop();
  displayStack();

  return 0;
}

