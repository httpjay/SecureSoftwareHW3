#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4
#define SUCCESS 0
#define STACK_OVERFLOW 1
#define STACK_UNDERFLOW 2
#define MEMORY_ALLOCATION_FAILURE 3
#define NULL_INPUT 4

// Stack structure
typedef struct {
    char **data;   // Array of string pointers
    int top;       // Index of top element
    int capacity;  // Current max size
} Stack;

// Function to initialize the stack
Stack *stack_init() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->data = (char **)malloc(sizeof(char *) * INITIAL_CAPACITY);
    if (!stack->data) {
        free(stack);
        return NULL;
    }

    stack->top = -1;
    stack->capacity = INITIAL_CAPACITY;
    return stack;
}

// Function to manually expand the stack
int stack_expand(Stack *stack) {
    int new_capacity = stack->capacity * 2;
    char **new_data = (char **)malloc(sizeof(char *) * new_capacity);

    if (!new_data) return MEMORY_ALLOCATION_FAILURE;

    // Copy old data to new array
    for (int i = 0; i <= stack->top; i++) {
        new_data[i] = stack->data[i]; // Copy pointers (shallow copy)
    }

    free(stack->data);  // Free old memory
    stack->data = new_data;
    stack->capacity = new_capacity;
    return SUCCESS;
}

// Function to push a string onto the stack
int stack_push(Stack *stack, const char *str) {
    if (!stack || !str) return NULL_INPUT;

    // Expand stack if full
    if (stack->top + 1 >= stack->capacity) {
        int expand_status = stack_expand(stack);
        if (expand_status != SUCCESS) return MEMORY_ALLOCATION_FAILURE;
    }

    // Allocate memory for new string and copy
    stack->data[++stack->top] = (char *)malloc(strlen(str) + 1);
    if (!stack->data[stack->top]) return MEMORY_ALLOCATION_FAILURE;

    strcpy(stack->data[stack->top], str);  // Copy string safely
    return SUCCESS;
}

// Function to pop a string from the stack
int stack_pop(Stack *stack, char **out) {
    if (!stack || stack->top == -1) return STACK_UNDERFLOW;

    *out = stack->data[stack->top];  // Return popped value
    stack->data[stack->top--] = NULL;
    return SUCCESS;
}

// Function to peek at the top string without removing it
int stack_peek(Stack *stack, char **out) {
    if (!stack || stack->top == -1) return STACK_UNDERFLOW;

    *out = stack->data[stack->top];
    return SUCCESS;
}

// Function to check if the stack is empty
int stack_is_empty(Stack *stack) {
    return (stack && stack->top == -1);
}

// Function to free the stack memory
void stack_free(Stack *stack) {
    if (!stack) return;

    for (int i = 0; i <= stack->top; i++) {
        free(stack->data[i]); // Free each string
    }
    free(stack->data);  // Free array
    free(stack);        // Free stack struct
}

// Test the stack
int main() {
    Stack *stack = stack_init();
    if (!stack) {
        printf("Failed to initialize stack.\n");
        return EXIT_FAILURE;
    }

    // Push values
    if (stack_push(stack, "Hello") != SUCCESS) printf("Push failed.\n");
    if (stack_push(stack, "World") != SUCCESS) printf("Push failed.\n");

    // Peek value
    char *peeked;
    if (stack_peek(stack, &peeked) == SUCCESS) {
        printf("Peek: %s\n", peeked);
    }

    // Pop values
    char *popped;
    if (stack_pop(stack, &popped) == SUCCESS) {
        printf("Popped: %s\n", popped);
        free(popped); // Free popped string
    }

    if (stack_pop(stack, &popped) == SUCCESS) {
        printf("Popped: %s\n", popped);
        free(popped); // Free popped string
    }

    // Check underflow
    if (stack_pop(stack, &popped) == STACK_UNDERFLOW) {
        printf("Stack underflow occurred.\n");
    }

    // Free stack memory
    stack_free(stack);
    return EXIT_SUCCESS;
}
