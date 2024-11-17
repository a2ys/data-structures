#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
        exit(1);
    }
    stack[++top] = value;
}

int pop() {
    if (isStackEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

int peek() {
    if (isStackEmpty()) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack[top];
}

int evaluatePostfix(char *expression) {
    for (int i = 0; expression[i]; i++) {
        if (isdigit(expression[i])) {
            push(expression[i] - '0');
        } else {
            int b = pop();
            int a = pop();
            switch (expression[i]) {
                case '+': push(a + b); break;
                case '-': push(a - b); break;
                case '*': push(a * b); break;
                case '/': push(a / b); break;
            }
        }
    }
    return pop();
}

int evaluatePrefix(char *expression) {
    int length = strlen(expression);
    for (int i = length - 1; i >= 0; i--) {
        if (isdigit(expression[i])) {
            push(expression[i] - '0');
        } else {
            int a = pop();
            int b = pop();
            switch (expression[i]) {
                case '+': push(a + b); break;
                case '-': push(a - b); break;
                case '*': push(a * b); break;
                case '/': push(a / b); break;
            }
        }
    }
    return pop();
}

int main() {
    char postfix[] = "231*+9-";
    printf("Postfix Evaluation of %s = %d\n", postfix, evaluatePostfix(postfix));
    char prefix[] = "-+2319";
    printf("Prefix Evaluation of %s = %d\n", prefix, evaluatePrefix(prefix));
    return 0;
}

