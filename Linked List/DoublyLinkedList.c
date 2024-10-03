#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *prev;
  struct Node *next;
} Node;

Node *createNode(int data) {
  Node *newNode = (Node *) malloc(sizeof(Node));
  newNode->data = data;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

void insertAtFirst(Node **head, int data) {
  Node *newNode = createNode(data);

  newNode->next = *head;

  if (*head != NULL) {
    (*head)->prev = newNode;
  }

  *head = newNode;
}

void insertAtEnd(Node **head, int data) {
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
  newNode->prev = temp;
}

void insertAtPosition(Node **head, int data, int position) {
  if (position == 0) {
    insertAtFirst(head, data);
    return;
  }

  Node *newNode = createNode(data);
  Node *temp = *head;

  for (int i = 0; temp->next != NULL && i < position - 1; i++) {
    temp = temp->next;
  }

  if (temp == NULL) {
    printf("Index out of bounds!");
    free(newNode);
    return;
  }

  newNode->next = temp->next;
  newNode->prev = temp;

  if (temp->next != NULL) {
    temp->next->prev = newNode;
  }

  temp->next = newNode;
}

void print(Node **head) {
  if (*head == NULL) {
    printf("List is empty!\n");
    return;
  }

  printf("HEAD <-> ");
  Node *temp = *head;

  while (temp != NULL) {
    printf("%d <-> ", temp->data);
    temp = temp->next;
  }

  printf("NULL\n");
}

Node *deleteFromFirst(Node **head) {
  if (head == NULL) {
    printf("List is empty!\n");
    return NULL;
  }

  Node *temp = *head;
  *head = temp->next;

  if (head != NULL) {
    (*head)->prev = NULL;
  }

  free(temp);
  return *head;
}

Node *deleteFromLast(Node **head) {
  if (head == NULL) {
    printf("List is empty!\n");
    return NULL;
  }

  Node *temp = *head;

  if (temp->next == NULL) {
    *head = NULL;
    free(temp);
    return NULL;
  }

  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->prev->next = NULL;
  free(temp);
  return *head;
}

Node *deleteFromPosition(Node **head, int position) {
  if (*head == NULL) {
    printf("List is empty!\n");
    return NULL;
  }

  if (position == 0) {
    return deleteFromFirst(head);
  }

  Node *temp = *head;

  for (int i = 0; temp->next != NULL && i < position; i++) {
    temp = temp->next;
  }

  if (temp == NULL) {
    printf("Index out of bounds!");
    return NULL;
  }

  if (temp->next != NULL) {
    temp->next->prev = temp->prev;
  }

  if (temp->prev != NULL) {
    temp->prev->next = temp->next;
  }

  free(temp);
  return *head;
}

int main() {
  Node *head = NULL;
  print(&head);

  insertAtFirst(&head, 10);
  print(&head);

  insertAtEnd(&head, 9);
  print(&head);

  insertAtFirst(&head, 11);
  print(&head);

  insertAtPosition(&head, 10, 2);
  print(&head);

  insertAtPosition(&head, 15, 0);
  print(&head);

  deleteFromFirst(&head);
  print(&head);

  deleteFromLast(&head);
  print(&head);

  deleteFromPosition(&head, 1);
  print(&head);

  return 0;
}
