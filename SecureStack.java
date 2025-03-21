import java.util.NoSuchElementException;

public class SecureStack {
    private String[] data; // Array to store stack elements
    private int top;       // Index of the top element
    private int capacity;  // Maximum capacity before expansion

    // Constructor: Initialize stack with a given size
    public SecureStack(int initialSize) {
        if (initialSize <= 0) {
            throw new IllegalArgumentException("Stack size must be greater than 0");
        }
        this.data = new String[initialSize];
        this.top = -1;
        this.capacity = initialSize;
    }

    // Expands the stack capacity when full
    private void expand() {
        int newCapacity = capacity * 2;
        String[] newData = new String[newCapacity];

        // Copy old elements to new array
        System.arraycopy(data, 0, newData, 0, capacity);

        data = newData;
        capacity = newCapacity;
        System.out.println("Stack expanded to new capacity: " + capacity);
    }

    // Push: Adds a string to the stack
    public void push(String str) {
        if (str == null) {
            throw new IllegalArgumentException("Cannot push null value onto the stack");
        }
        if (top + 1 >= capacity) {
            expand();
        }
        data[++top] = str;
        System.out.println("Pushed: " + str + " (Stack size: " + (top + 1) + ")");
    }

    // Pop: Removes and returns the top string
    public String pop() {
        if (top == -1) {
            throw new NoSuchElementException("Stack underflow: Cannot pop from an empty stack");
        }
        String value = data[top];
        data[top--] = null; // Avoid memory leak
        System.out.println("Popped: " + value + " (Stack size: " + (top + 1) + ")");
        return value;
    }

    // Peek: Returns the top string without removing it
    public String peek() {
        if (top == -1) {
            throw new NoSuchElementException("Stack underflow: Cannot peek in an empty stack");
        }
        return data[top];
    }

    // Check if stack is empty
    public boolean isEmpty() {
        return top == -1;
    }

    // Get the current size of the stack
    public int size() {
        return top + 1;
    }

    // Get the current capacity of the stack
    public int getCapacity() {
        return capacity;
    }

    // Test the stack
    public static void main(String[] args) {
        try {
            System.out.println("Starting SecureStack test...\n");

            SecureStack stack = new SecureStack(2);  // Start with a small stack

            stack.push("Hello");
            stack.push("World");

            System.out.println("\nTop of stack (peek): " + stack.peek());

            stack.push("Expandable");
            stack.push("Stack");

            stack.pop();
            stack.pop();
            stack.pop();
            stack.pop();

            System.out.println("Trying to pop from empty stack...");
            stack.pop(); // Should throw exception

        } catch (Exception e) {
            System.err.println("Exception caught: " + e.getMessage());
        }
    }
}
