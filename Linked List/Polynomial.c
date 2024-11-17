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

int comparePolynomials(Node* polynomial1, Node* polynomial2) {
  while (polynomial1 != NULL && polynomial2 != NULL) {
    if (polynomial1->term->exponent != polynomial2->term->exponent) {
      return 0;
    }
    if (polynomial1->term->coefficient != polynomial2->term->coefficient) {
      return 0;
    }

    polynomial1 = polynomial1->next;
    polynomial2 = polynomial2->next;
  }

  return polynomial1 == NULL && polynomial2 == NULL;
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

Node* multiply(Node* poly1, Node* poly2) {
  Node* result = NULL;
  Node* p1 = poly1;

  while (p1 != NULL) {
    Node* p2 = poly2;
    
    while (p2 != NULL) {
      int coeff = p1->term->coefficient * p2->term->coefficient;
      int exp = p1->term->exponent + p2->term->exponent;
      
      result = insertAtEnd(result, coeff, exp);
      
      p2 = p2->next;
    }
    
    p1 = p1->next;
  }

  Node* simplified = NULL;
  Node* current = result;

  while (current != NULL) {
    Node* temp = simplified;
    int coefficient = current->term->coefficient;
    int exponent = current->term->exponent;
    
    Node* prev = NULL;
    
    while (temp != NULL) {
      if (temp->term->exponent == exponent) {
        temp->term->coefficient += coefficient;
        break;
      }
      prev = temp;
      temp = temp->next;
    }

    if (temp == NULL) {
      simplified = insertAtEnd(simplified, coefficient, exponent);
    }

    current = current->next;
  }

  freePolynomial(result);

  return simplified;
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

  Node* result2 = multiply(poly1, poly2);
  printf("Resultant Polynomial (Multiplication): ");
  printPolynomial(result2);

  printf("\n");

  printf("Polynomials are: ");
  if (comparePolynomials(poly1, poly2)) {
    printf("EQUAL\n");
  } else {
    printf("NOT EQUAL\n");
  }

  Node* poly3 = NULL;
  Node* poly4 = NULL;

  poly3 = insertAtEnd(poly3, 2, 2);
  poly3 = insertAtEnd(poly3, 1, 1);
  poly3 = insertAtEnd(poly3, 3, 0);

  poly4 = insertAtEnd(poly4, 2, 2);
  poly4 = insertAtEnd(poly4, 1, 1);
  poly4 = insertAtEnd(poly4, 3, 0);

  printf("Polynomials are: ");
  if (comparePolynomials(poly3, poly4)) {
    printf("EQUAL\n");
  } else {
    printf("NOT EQUAL\n");
  }

  freePolynomial(poly1);
  freePolynomial(poly2);
  freePolynomial(result);

  return 0;
}

