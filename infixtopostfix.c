
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

int top = -1;
char stack[MAX_SIZE];

void push(char item) {
    if (top >= MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = item;
}

char pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}

int isEmpty() {
    return (top == -1);
}

char peek() {
    if (top == -1) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack[top];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int precedence(char operator) {
    if (operator == '+' || operator == '-')
        return 1;
    else if (operator == '*' || operator == '/')
        return 2;
    else if (operator == '^')
        return 3;
    else
        return 0;
}

void infixToPostfix(const char* infix, char* postfix) {
    int i, j;
    char token;
    
    j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        token = infix[i];
        
        if (isalnum(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(token);
        } else if (token == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            if (!isEmpty() && peek() != '(') {
                printf("Invalid infix expression\n");
                exit(EXIT_FAILURE);
            }
            pop(); // Discard '(' from the stack
        } else if (isOperator(token)) {
            while (!isEmpty() && precedence(token) <= precedence(peek())) {
                postfix[j++] = pop();
            }
            push(token);
        } else {
            printf("Invalid character in the infix expression\n");
            exit(EXIT_FAILURE);
        }
    }
    
    while (!isEmpty()) {
        if (stack[top] == '(') {
            printf("Invalid infix expression\n");
            exit(EXIT_FAILURE);
        }
        postfix[j++] = pop();
    }
    
    postfix[j] = '\0';
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    
    printf("Enter an infix expression: ");

    scanf("%s", infix);

    
    infixToPostfix(infix, postfix);
    
    printf("Postfix expression: %s\n", postfix);
    
    return 0;
}

