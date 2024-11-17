#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
  int coefficient;
  int exponent;
} Term;

typedef struct Node {
  Term* term;
  struct Node* next;
} Node;

Term* createTerm(int coefficient, int exponent) {
  Term* temp = (Term*) malloc(sizeof(Term));
  temp->coefficient = coefficient;
  temp->exponent = exponent;

  return temp;
}

Node* createNode(int coefficient, int exponent) {
  Term* term = createTerm(coefficient, exponent);
  Node* newNode = (Node*) malloc(sizeof(Node));

  newNode->term = term;
  newNode->next = NULL;

  return newNode;
}


Node* insertAtEnd(Node* head, int coefficient, int exponent) {
  if (head == NULL) return createNode(coefficient, exponent);

  Node* temp = head;

  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = createNode(coefficient, exponent);
  
  return head;
}

void printPolynomial(Node* head) {
  Node* temp = head;

  while (temp != NULL) {
    printf("%dx^%d", temp->term->coefficient, temp->term->exponent);
    if (temp->next != NULL) {
      printf(" + ");
    }
    temp = temp->next;
  }

  printf("\n");
}

void freePolynomial(Node* head) {
  Node* temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp->term);
    free(temp);
  }
}

Node* add(Node* polynomial1, Node* polynomial2) {
  Node* result = NULL;

  Node* p1 = polynomial1;
  Node* p2 = polynomial2;

  while (p1 != NULL && p2 != NULL) {
    if (p1->term->exponent == p2->term->exponent) {
      int sumCoeff = p1->term->coefficient + p2->term->coefficient;
      if (sumCoeff != 0) {
        result = insertAtEnd(result, sumCoeff, p1->term->exponent);
      }
      p1 = p1->next;
      p2 = p2->next;
    } else if (p1->term->exponent > p2->term->exponent) {
      result = insertAtEnd(result, p1->term->coefficient, p1->term->exponent);
      p1 = p1->next;
    } else {
      result = insertAtEnd(result, p2->term->coefficient, p2->term->exponent);
      p2 = p2->next;
    }
  }

  while (p1 != NULL) {
    result = insertAtEnd(result, p1->term->coefficient, p1->term->exponent);
    p1 = p1->next;
  }

  while (p2 != NULL) {
    result = insertAtEnd(result, p2->term->coefficient, p2->term->exponent);
    p2 = p2->next;
  }

  return result;
}

int main() {
  Node* poly1 = NULL;
  Node* poly2 = NULL;

  poly1 = insertAtEnd(poly1, 5, 3);
  poly1 = insertAtEnd(poly1, 3, 2);
  poly1 = insertAtEnd(poly1, 1, 0);

  poly2 = insertAtEnd(poly2, 4, 3);
  poly2 = insertAtEnd(poly2, 2, 1);

  printf("Polynomial 1: ");
  printPolynomial(poly1);

  printf("Polynomial 2: ");
  printPolynomial(poly2);

  Node* result = add(poly1, poly2);

  printf("Resultant Polynomial: ");
  printPolynomial(result);

  freePolynomial(poly1);
  freePolynomial(poly2);
  freePolynomial(result);

  return 0;
}
