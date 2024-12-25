#include <iostream>
#include <stdexcept>
#include <string>

#define FULL_QUEUE "queue is full"
#define EMPTY_QUEUE "queue is empty"

using namespace std;

typedef int ItemType;
class QueueType;

class QueueType {
public:
    QueueType(int max);
    ~QueueType();
    [[nodiscard]] bool IsFull() const; //큐가 가득 차있는지 확인
    [[nodiscard]] bool IsEmpty() const; //큐가 비어있는지 확인
    void Enqueue(ItemType newItem); //큐 rear에 아이템 삽입
    ItemType Dequeue(); //큐 front의 아이템 삭제 및 반환

private:
    int front;
    int rear;
    int maxQue;
    ItemType* items;
};

QueueType::QueueType(int max) {
    maxQue = max + 1;
    front = maxQue - 1;
    rear = maxQue - 1;
    items = new ItemType[maxQue];
}

QueueType::~QueueType() {
    delete [] items;
}

bool QueueType::IsEmpty() const {
    return rear == front;
}

bool QueueType::IsFull() const {
    return (rear + 1) % maxQue == front;
}

void QueueType::Enqueue(ItemType newItem) {
    if (IsFull()) {
        throw runtime_error(FULL_QUEUE);
    }
    rear = (rear + 1) % maxQue;
    items[rear] = newItem;
}

ItemType QueueType::Dequeue() {
    if (IsEmpty()) {
        throw runtime_error(EMPTY_QUEUE);
    }
    front = (front + 1) % maxQue;
    return items[front];
}

int main() {
    QueueType myQueue(5);

    try {
        for (int i = 1; i <= 6; i++) {
            cout << "Enqueuing " << i << " onto the queue." << endl;
            myQueue.Enqueue(i);
        }
    } catch (const runtime_error& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    cout << "Is the queue full? " << (myQueue.IsFull() ? "Yes" : "No") << endl;

    cout << "Dequeuing items: ";
    try {
        while (!myQueue.IsEmpty()) {
            cout << myQueue.Dequeue() << " ";
        }
        cout << endl;
    } catch (const runtime_error& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    cout << "Is the queue empty? " << (myQueue.IsEmpty() ? "Yes" : "No") << endl;

    return EXIT_SUCCESS;
}
