#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure
struct Stack {
    int top;
    char* items[MAX];
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, char* item) {
    if (isFull(stack))
        return;
    stack->items[++stack->top] = item;
}

char* pop(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->items[stack->top--];
}

char* peek(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->items[stack->top];
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

char* strrev(char* str) {
    int i, j;
    char temp;
    int len = strlen(str);
    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    return str;
}

void prefixToPostfix(char* prefix) {
    int length = strlen(prefix);
    struct Stack* stack = createStack();

    // Reverse the prefix expression
    strrev(prefix);

    for (int i = 0; i < length; i++) {
        // If the character is an operator
        if (isOperator(prefix[i])) {
            char* op1 = pop(stack);
            char* op2 = pop(stack);

            // Create a new string with the operator and operands
            char* temp = (char*)malloc(strlen(op1) + strlen(op2) + 2);
            sprintf(temp, "%s%s%c", op1, op2, prefix[i]);

            // Push the resulting string back to the stack
            push(stack, temp);
        }
        // If the character is an operand
        else if (isalnum(prefix[i])) {
            char* operand = (char*)malloc(2);
            operand[0] = prefix[i];
            operand[1] = '\0';
            push(stack, operand);
        }
    }

    // The final postfix expression is at the top of the stack
    char* result = pop(stack);
    printf("Postfix Expression: %s\n", result);

    free(stack);
}

int main() {
    char prefix[MAX];
    printf("Enter a prefix expression: ");
    scanf("%s", prefix);

    prefixToPostfix(prefix);

    return 0;
}
