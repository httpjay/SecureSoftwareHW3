#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class SecureStack {
private:
    std::unique_ptr<std::string[]> data;
    int top;
    int capacity;

    void expand() {
        int newCapacity = capacity * 2;
        auto newData = std::make_unique<std::string[]>(newCapacity);

        for (int i = 0; i <= top; i++) {
            newData[i] = std::move(data[i]); 
        }

        data = std::move(newData);
        capacity = newCapacity;
        std::cout << "Stack expanded to new capacity: " << newCapacity << std::endl;
    }

public:
    SecureStack(int initialSize = 4)
        : data(std::make_unique<std::string[]>(initialSize)), top(-1), capacity(initialSize) {
        std::cout << "Stack initialized with capacity: " << capacity << std::endl;
    }

    void push(const std::string& str) {
        if (top + 1 >= capacity) {
            expand();
        }
        data[++top] = str;
        std::cout << "Pushed: " << str << " (Stack size: " << top + 1 << ")" << std::endl;
    }

    std::string pop() {
        if (top == -1) {
            throw std::underflow_error("Stack underflow: Cannot pop from an empty stack");
        }
        std::string value = std::move(data[top--]);
        std::cout << "Popped: " << value << " (Stack size: " << top + 1 << ")" << std::endl;
        return value;
    }

    std::string peek() const {
        if (top == -1) {
            throw std::underflow_error("Stack underflow: Cannot peek in an empty stack");
        }
        return data[top];
    }

    bool isEmpty() const {
        return top == -1;
    }
};

int main() {
    try {
        std::cout << "Starting SecureStack test...\n" << std::endl;
        SecureStack stack(2);  

        stack.push("Hello");
        stack.push("World");

        std::cout << "\nTop of stack (peek): " << stack.peek() << std::endl;

        stack.push("Expandable");
        stack.push("Stack");

        stack.pop();
        stack.pop();
        stack.pop();
        stack.pop();

        std::cout << "Trying to pop from empty stack..." << std::endl;
        stack.pop();

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
