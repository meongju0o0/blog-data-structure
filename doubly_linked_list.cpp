#include <iostream>

using namespace std;

typedef int ItemType;
struct Node;
class DLL;

struct Node {
    ItemType item = 0;
    Node* next = nullptr;
    Node* prev = nullptr;
};

class DLL {
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;

public:
    class Iterator {
    private:
        Node* current;

    public:
        explicit Iterator(Node* node);
        DLL::Iterator& operator=(const Iterator& other);
        ItemType& operator*() const;
        Iterator& operator++();
        Iterator& operator--();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        [[nodiscard]] Node* GetCurrent() const;
    };

    explicit DLL(ItemType root_item);
    ~DLL();
    [[nodiscard]] bool IsFull() const;
    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] size_t SizeIs() const;
    void Insert(Iterator pos, ItemType new_item);
    void Erase(Iterator pos);

    [[nodiscard]] Iterator Begin() const { return Iterator(head); }
    [[nodiscard]] Iterator End() const { return Iterator(nullptr); }
    [[nodiscard]] Iterator RBegin() const { return Iterator(tail); }
};

DLL::Iterator::Iterator(Node* node) : current(node) {}

DLL::Iterator &DLL::Iterator::operator=(const Iterator &other) {
    if (this != &other) {
        current = other.current;
    }
    return *this;
}

ItemType& DLL::Iterator::operator*() const {
    return current->item;
}

DLL::Iterator& DLL::Iterator::operator++() {
    if (current != nullptr) {
        current = current->next;
    }
    return *this;
}

DLL::Iterator& DLL::Iterator::operator--() {
    if (current != nullptr) {
        current = current->prev;
    }
    return *this;
}

bool DLL::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

bool DLL::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

Node* DLL::Iterator::GetCurrent() const {
    return current;
}

DLL::DLL(const ItemType root_item) {
    head = new Node();
    head->item = root_item;
    head->next = nullptr;
    head->prev = nullptr;
    tail = head; // 초기화 시 head와 tail이 동일
    size++;
}

DLL::~DLL() {
    Node* cur_node = head;
    while (cur_node != nullptr) {
        Node* temp_ptr = cur_node->next;
        delete cur_node;
        cur_node = temp_ptr;
    }
}

bool DLL::IsFull() const {
    try {
        const Node* dummy_node = new Node();
        delete dummy_node;
        return false;
    } catch (const bad_alloc&) {
        return true;
    }
}

bool DLL::IsEmpty() const {
    return head == nullptr;
}

size_t DLL::SizeIs() const {
    return size;
}

void DLL::Insert(Iterator pos, ItemType new_item) {
    if (IsFull()) {
        cerr << "List is Full, bad_alloc exception" << endl;
        return;
    }

    Node* new_node = new Node();
    new_node->item = new_item;

    if (pos.GetCurrent() == nullptr) {
        // Tail 뒤에 삽입하는 경우
        if (tail != nullptr) {
            tail->next = new_node;
            new_node->prev = tail;
        } else {
            head = new_node;
        }
        tail = new_node;
    } else {
        Node* cur = pos.GetCurrent();
        new_node->next = cur->next;
        new_node->prev = cur;

        if (cur->next != nullptr) {
            cur->next->prev = new_node;
        } else {
            tail = new_node; // Tail 갱신
        }
        cur->next = new_node;
    }
    size++;
}

void DLL::Erase(Iterator pos) {
    if (IsEmpty() || pos.GetCurrent() == nullptr) {
        cerr << "List is empty or invalid iterator, nothing to erase." << endl;
        return;
    }

    Node* target = pos.GetCurrent();

    if (target->prev != nullptr) {
        target->prev->next = target->next;
    } else {
        head = target->next; // 삭제한 노드가 head라면 갱신
    }

    if (target->next != nullptr) {
        target->next->prev = target->prev;
    } else {
        tail = target->prev; // 삭제한 노드가 tail이라면 갱신
    }

    delete target;
    size--;
}

int main() {
    DLL list(5);

    DLL::Iterator it1 = list.Begin();
    list.Insert(it1, 10);
    list.Insert(++it1, 15);
    list.Insert(++it1, 20);

    cout << "List Size: " << list.SizeIs() << endl;

    for (DLL::Iterator it = list.Begin(); it != list.End(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    DLL::Iterator it2 = list.RBegin(); // Tail부터 출력
    cout << "Items in reverse order: ";
    for (; it2 != list.End(); --it2) {
        cout << *it2 << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}