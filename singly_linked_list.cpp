#include <iostream>

using namespace std;

typedef int ItemType;
struct Node;
class SLL;

struct Node {
    ItemType item = 0;
    Node* next = nullptr;
};

class SLL {
private:
    Node* root = nullptr;
    size_t size = 0;

public:
    class Iterator { //SLL 객체의 아이템 접근을 위한 iterator
    private:
        Node* current;
        Node* previous;

    public:
        explicit Iterator(Node* node); //iterator 객체 생성자
        ItemType& operator*() const; //SLL Node의 item 접근을 위한 연산자 오버로딩
        Iterator& operator++(); //SLL iterator가 다음 노드를 지시하도록 하기 위한 연산자 오버로딩
        bool operator==(const Iterator& other) const; //SLL iterator가 지시하는 노드가 서로 동일한지 확인하는 연산자
        bool operator!=(const Iterator& other) const; //SLL iterator가 지시하는 노드가 서로 다른지 확인하는 연산자
        [[nodiscard]] Node* GetCurrent() const; //SLL iterator가 현재 지시하고 있는 노드의 포인터를 반환
        [[nodiscard]] Node* GetPrevious() const; // 현재 지시하고 있는 노드의 이전 노드의 포인터를 반환
    };

    explicit SLL(ItemType root_item);
    ~SLL();
    [[nodiscard]] bool IsFull() const; //SLL이 가득 차 있는지 확인
    [[nodiscard]] bool IsEmpty() const; //SLL이 비어있는지 확인
    [[nodiscard]] int SizeIs() const; //SLL의 크기 반환
    void Insert(Iterator pos, ItemType new_item); //SLL에 아이템 삽입
    void Erase(Iterator pos); //SLL의 아이템 삭제

    [[nodiscard]] Iterator Begin() const { return Iterator(root); } //SLL의 처음 시작위치 반환
    [[nodiscard]] Iterator End() const { return Iterator(nullptr); } //SLL의 마지막 위치 반환(nullptr)
};

// SLL::Iterator 클래스의 멤버 함수 정의
SLL::Iterator::Iterator(Node* node) : current(node), previous(nullptr) {}

ItemType& SLL::Iterator::operator*() const {
    return current->item;
}

SLL::Iterator& SLL::Iterator::operator++() {
    if (current != nullptr) {
        previous = current; // 이전 노드를 현재 노드로 업데이트
        current = current->next;
    }
    return *this;
}

bool SLL::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

bool SLL::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

Node* SLL::Iterator::GetCurrent() const {
    return current;
}

Node* SLL::Iterator::GetPrevious() const {
    return previous;
}

SLL::SLL(const ItemType root_item) {
    root = new Node();
    root->item = root_item;
    root->next = nullptr;
    size++;
}

SLL::~SLL() {
    Node* cur_node = root;
    while(cur_node != nullptr) {
        Node* temp_ptr = cur_node->next;
        delete cur_node;
        cur_node = temp_ptr;
    }
}

bool SLL::IsFull() const {
    try {
        const Node* dummy_node = new Node(); //dummy_node가 생성 가능하면 false 반환
        delete dummy_node;
        return false;
    }
    catch(const bad_alloc& e) { //dummy_node가 생성되지 않고 bad_alloc exception 발생
        return true; //true 반환
    }
}

bool SLL::IsEmpty() const {
    return root == nullptr;
}

int SLL::SizeIs() const {
    return size;
}

void SLL::Insert(Iterator pos, ItemType new_item) {
    if (IsFull()) {
        cerr << "List is Full, bad_alloc exception" << endl;
        return;
    }

    Node* new_node = new Node();
    new_node->item = new_item;

    if (pos.GetCurrent() == root) {
        new_node->next = root;
        root = new_node;
    }
    else {
        Node* prev_node = pos.GetPrevious();
        new_node->next = pos.GetCurrent();
        if (prev_node != nullptr) {
            prev_node->next = new_node;
        }
    }
    size++;
}

void SLL::Erase(Iterator pos) {
    if (IsEmpty() || pos.GetCurrent() == nullptr) {
        cerr << "List is empty or invalid iterator, nothing to erase." << endl;
        return;
    }

    if (pos.GetCurrent() == root) {
        Node* temp_ptr = root;
        root = root->next;
        delete temp_ptr;
    }
    else {
        Node* prev_node = pos.GetPrevious();
        if (prev_node != nullptr) {
            prev_node->next = pos.GetCurrent()->next;
            delete pos.GetCurrent();
        }
    }
    size--;
}

int main() {
    SLL list(5);
    list.Insert(list.Begin(), 10);
    list.Insert(list.Begin(), 15);
    list.Insert(list.Begin(), 20);

    cout << "List Size: " << list.SizeIs() << endl;

    for (SLL::Iterator it = list.Begin(); it != list.End(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    SLL::Iterator erase_it = list.Begin();
    ++erase_it;
    list.Erase(erase_it);

    cout << "List Size after erasing 10: " << list.SizeIs() << endl;

    for (SLL::Iterator it = list.Begin(); it != list.End(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}
