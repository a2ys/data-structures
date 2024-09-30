#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *createNode(int data) {
  Node *newNode = (Node *) malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void insertAtFirst(Node **head, int data) {
  Node *newNode = createNode(data);
  newNode->next = *head;
  *head = newNode;
}

void insertAtLast(Node **head, int data) {
  Node *newNode = createNode(data);

  if (*head == NULL) {
    *head = newNode;
    return;
  }

  Node *temp = *head;
  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = newNode;
}

void insertAtPosition(Node **head, int data, int position) {
  Node *newNode = createNode(data);

  if (position == 0) {
    insertAtFirst(head, data);
    return;
  }

  Node *temp = *head;
  for (int i = 0; temp->next != NULL && i < position - 1; i++) {
    temp = temp->next;
  }

  if (temp == NULL) {
    printf("Index out of bounds.");
    free(newNode);
    return;
  }

  newNode->next = temp->next;
  temp->next = newNode;
}

void deleteFromFirst(Node **head) {
  if (head == NULL) {
    printf("List is empty!");
    return;
  }

  Node *temp = *head;
  *head = temp->next;
  free(temp);
}

void deleteFromLast(Node **head) {
  if (head == NULL) {
    printf("List is empty!");
    return;
  }

  Node *temp = *head;
  if (temp->next == NULL) {
    free(temp);
    *head = NULL;
    return;
  }

  while (temp->next->next != NULL) {
    temp = temp->next;
  }

  free(temp->next);
  temp->next = NULL;
}

void deleteFromPosition(Node **head, int position) {
  if (head == NULL) {
    printf("List is empty!");
    return;
  }

  if (position == 0) {
    deleteFromFirst(head);
    return;
  }

  Node *temp = *head;

  for (int i = 0; temp->next != NULL && i < position - 1; i++) {
    temp = temp->next;
  }

  if (temp == NULL || temp->next == NULL) {
    printf("Index out of bounds.");
    return;
  }

  Node *next = temp->next->next;
  free(temp->next);
  temp->next = next;
}

void print(Node *head) {
  Node *temp = head;
  while (temp != NULL) {
    printf("%d -> ", temp->data);
    temp = temp->next;
  }

  printf("NULL \n");
}

int main() {
  Node *head = NULL;

  insertAtFirst(&head, 10);
  printf("Linked list after inserting the node:10 at the beginning \n");
  print(head);

  printf("Linked list after inserting the node:20 at the end \n");
  insertAtLast(&head, 20);
  print(head);

  printf("Linked list after inserting the node:5 at the end \n");
  insertAtLast(&head, 5);
  print(head);

  printf("Linked list after inserting the node:30 at the end \n");
  insertAtLast(&head, 30);
  print(head);

  printf("Linked list after inserting the node:15 at position 2 \n");
  insertAtPosition(&head, 15, 2);
  print(head);

  printf("Linked list after deleting the first node: \n");
  deleteFromFirst(&head);
  print(head);

  printf("Linked list after deleting the last node: \n");
  deleteFromLast(&head);
  print(head);

  printf("Linked list after deleting the node at position 1: \n");
  deleteFromPosition(&head, 1);
  print(head);

  return 0;
}
