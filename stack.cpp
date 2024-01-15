//
// Created by meongju0o0 on 2024-01-16.
//

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

#define MAX_ITEMS 50
#define FULL_STACK "stack is full"
#define EMPTY_STACK "stack is empty"
typedef int ItemType;
class StackType;

class StackType {
public:
    StackType();
    [[nodiscard]] bool IsFull() const;
    [[nodiscard]] bool IsEmpty() const;
    void Push(ItemType newItem);
    ItemType Pop();
    ItemType Top();

private:
    int top;
    ItemType items[MAX_ITEMS]{};
};

StackType::StackType() {
    top = -1;
}

bool StackType::IsEmpty() const {
    return top == -1;
}

bool StackType::IsFull() const {
    return top == (MAX_ITEMS - 1);
}

void StackType::Push(ItemType newItem) {
    if(IsFull()) {
        throw runtime_error(FULL_STACK);
    }
    items[++top] = newItem;
}

ItemType StackType::Pop() {
    if(IsEmpty()) {
        throw runtime_error(EMPTY_STACK);
    }
    return items[top--];
}

ItemType StackType::Top() {
    if(IsEmpty()) {
        throw runtime_error(EMPTY_STACK);
    }
    return items[top];
}

int main() {
    StackType myStack;

    // 푸시
    try {
        for (int i = 1; i <= 5; i++) {
            cout << "Pushing " << i << " onto the stack." << endl;
            myStack.Push(i);
        }
    } catch (const runtime_error& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    // 탑
    try {
        cout << "Top item of the stack: " << myStack.Top() << endl;
    } catch (const runtime_error& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    // 팝
    cout << "Popping items: ";
    try {
        while (!myStack.IsEmpty()) {
            cout << myStack.Pop() << " ";
        }
        cout << endl;
    } catch (const runtime_error& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    return EXIT_SUCCESS;
}