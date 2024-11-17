#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode;
    return newNode;
}

Node* insert(Node* tail, int data) {
    Node* newNode = createNode(data);
    if (tail == NULL) {
        return newNode;
    }
    newNode->next = tail->next;
    tail->next = newNode;
    return newNode;
}

Node* delete(Node* tail, int key) {
    if (tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }

    Node* current = tail->next;
    Node* prev = tail;

    do {
        if (current->data == key) {
            if (current == tail && current->next == tail) {
                free(current);
                return NULL;
            }
            if (current == tail->next) {
                tail->next = current->next;
            }
            if (current == tail) {
                tail = prev;
            }
            prev->next = current->next;
            free(current);
            return tail;
        }
        prev = current;
        current = current->next;
    } while (current != tail->next);

    printf("Key not found in the list.\n");
    return tail;
}

void traverse(Node* tail) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* current = tail->next;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != tail->next);
    printf("\n");
}

int main() {
    Node* tail = NULL;

    tail = insert(tail, 1);
    tail = insert(tail, 2);
    tail = insert(tail, 3);
    tail = insert(tail, 4);

    printf("Circular Linked List after insertion: ");
    traverse(tail);

    tail = delete(tail, 2);
    printf("Circular Linked List after deleting 2: ");
    traverse(tail);

    tail = delete(tail, 4);
    printf("Circular Linked List after deleting 4: ");
    traverse(tail);

    return 0;
}

