#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *prev;
  struct Node *next;
} Node;

Node *createNode(int data) {
  Node *newNode = (Node *) malloc(sizeof(Node));
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

void insertAtFirst(Node **head, int data) {
  Node *newNode = createNode(data);

  newNode->next = head;

  if (head != NULL) {
    head->prev = *newNode;
  }

  *head = newNode;
}

int main() {
  return 0;
}

