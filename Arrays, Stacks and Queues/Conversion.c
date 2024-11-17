#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

char stack[MAX][MAX];
int top = -1;

int isStackFull() {
    return top == MAX - 1;
}

int isStackEmpty() {
    return top == -1;
}

void push(char *value) {
    if (isStackFull()) {
        printf("Stack Overflow\n");
        exit(1);
    }
    strcpy(stack[++top], value);
}

char *pop() {
    if (isStackEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

char *peek() {
    if (isStackEmpty()) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack[top];
}

int precedence(char operator) {
    if (operator == '+' || operator == '-') return 1;
    if (operator == '*' || operator == '/') return 2;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    char stack[MAX];
    int top = -1, k = 0;

    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            stack[++top] = infix[i];
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = stack[top--];
            top--; // Pop '('
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i]))
                postfix[k++] = stack[top--];
            stack[++top] = infix[i];
        }
    }
    while (top != -1) {
        postfix[k++] = stack[top--];
    }
    postfix[k] = '\0';
}

void reverseString(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void infixToPrefix(char *infix, char *prefix) {
    char reversedInfix[MAX], postfix[MAX];
    strcpy(reversedInfix, infix);

    reverseString(reversedInfix);

    for (int i = 0; reversedInfix[i]; i++) {
        if (reversedInfix[i] == '(') reversedInfix[i] = ')';
        else if (reversedInfix[i] == ')') reversedInfix[i] = '(';
    }

    infixToPostfix(reversedInfix, postfix);
    reverseString(postfix);

    strcpy(prefix, postfix);
}

void postfixToPrefix(char *postfix, char *prefix) {
    char stack[MAX][MAX];
    int top = -1;

    for (int i = 0; postfix[i]; i++) {
        if (isalnum(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            strcpy(stack[++top], operand);
        } else {
            char op1[MAX], op2[MAX];
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);

            char temp[MAX];
            sprintf(temp, "%c%s%s", postfix[i], op1, op2);

            strcpy(stack[++top], temp);
        }
    }
    strcpy(prefix, stack[top]);
}

void prefixToPostfix(char *prefix, char *postfix) {
    int length = strlen(prefix);

    for (int i = length - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) {
            char operand[2] = {prefix[i], '\0'};
            push(operand);
        } else {
            char op1[MAX], op2[MAX];
            strcpy(op1, pop());
            strcpy(op2, pop());

            char temp[MAX];
            sprintf(temp, "%s%s%c", op1, op2, prefix[i]);

            push(temp);
        }
    }
    strcpy(postfix, pop());
}

void prefixToInfix(char *prefix, char *infix) {
    int length = strlen(prefix);

    for (int i = length - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) {
            char operand[2] = {prefix[i], '\0'};
            push(operand);
        } else {
            char op1[MAX], op2[MAX];
            strcpy(op1, pop());
            strcpy(op2, pop());

            char temp[MAX];
            sprintf(temp, "(%s%c%s)", op1, prefix[i], op2);

            push(temp);
        }
    }
    strcpy(infix, pop());
}

void postfixToInfix(char *postfix, char *infix) {
    for (int i = 0; postfix[i]; i++) {
        if (isalnum(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            push(operand);
        } else {
            char op1[MAX], op2[MAX];
            strcpy(op2, pop());
            strcpy(op1, pop());

            char temp[MAX];
            sprintf(temp, "(%s%c%s)", op1, postfix[i], op2);

            push(temp);
        }
    }
    strcpy(infix, pop());
}

int main() {
    char prefix[] = "-+ABC";
    char postfixFromPrefix[MAX], infixFromPrefix[MAX], infixFromPostfix[MAX];
    char postfix[] = "AB+C-";

    prefixToPostfix(prefix, postfixFromPrefix);
    prefixToInfix(prefix, infixFromPrefix);
    postfixToInfix(postfix, infixFromPostfix);

    printf("Prefix: %s\n", prefix);
    printf("Postfix from Prefix: %s\n", postfixFromPrefix);
    printf("Infix from Prefix: %s\n", infixFromPrefix);

    printf("\nPostfix: %s\n", postfix);
    printf("Infix from Postfix: %s\n", infixFromPostfix);

    return 0;
}

