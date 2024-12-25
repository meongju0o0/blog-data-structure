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
    Node* head = nullptr;
    size_t size = 0;

public:
    class Iterator { // SLL 객체의 아이템 접근을 위한 iterator
    private:
        Node* current;
        Node* previous;

    public:
        explicit Iterator(Node* node); // iterator 객체 생성자
        SLL::Iterator& operator=(const Iterator& other); // iterator 복사 연산자
        ItemType& operator*() const; // SLL Node의 item 접근을 위한 연산자 오버로딩
        Iterator& operator++(); // SLL iterator가 다음 노드를 지시하도록 하기 위한 연산자 오버로딩
        bool operator==(const Iterator& other) const; // SLL iterator가 지시하는 노드가 서로 동일한지 확인하는 연산자
        bool operator!=(const Iterator& other) const; // SLL iterator가 지시하는 노드가 서로 다른지 확인하는 연산자
        [[nodiscard]] Node* GetCurrent() const; // SLL iterator가 현재 지시하고 있는 노드의 포인터를 반환
        [[nodiscard]] Node* GetPrevious() const; // 현재 지시하고 있는 노드의 이전 노드의 포인터를 반환
    };

    explicit SLL(ItemType root_item);
    ~SLL();
    [[nodiscard]] bool IsFull() const; // SLL이 가득 차 있는지 확인
    [[nodiscard]] bool IsEmpty() const; // SLL이 비어있는지 확인
    [[nodiscard]] size_t SizeIs() const; // SLL의 크기 반환
    void Insert(Iterator pos, ItemType new_item); // SLL에 아이템 삽입
    void Erase(Iterator pos); // SLL의 아이템 삭제

    [[nodiscard]] Iterator Begin() const { return Iterator(head); } // SLL의 처음 시작위치 반환
    [[nodiscard]] Iterator End() const { return Iterator(nullptr); } // SLL의 마지막 위치 반환(nullptr)
};

SLL::Iterator::Iterator(Node* node) : current(node), previous(nullptr) {}

SLL::Iterator &SLL::Iterator::operator=(const Iterator &other) {
    if (this != &other) { // 자기 자신이 아닐 때만 복사 수행
        current = other.current; // 현재 노드 복사
        previous = other.previous; // 이전 노드 복사
    }
    return *this;
}

ItemType& SLL::Iterator::operator*() const {
    return current->item;
}

SLL::Iterator& SLL::Iterator::operator++() {
    if (current != nullptr) {
        previous = current;
        // 이전 노드의 포인터를 직전의 현재 노드 정보를 활용하여 추적 관리
        // 삭제 연산에 대비하기 위함

        current = current->next; // 현재 노드 포인터 관리
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
    head = new Node();
    head->item = root_item;
    head->next = nullptr;
    size++;
}

SLL::~SLL() {
    Node* cur_node = head;
    while(cur_node != nullptr) {
        Node* temp_ptr = cur_node->next;
        delete cur_node;
        cur_node = temp_ptr;
    }
}

bool SLL::IsFull() const {
    try {
        const Node* dummy_node = new Node(); // dummy_node가 생성 가능하면 false 반환
        delete dummy_node;
        return false;
    }
    catch(const bad_alloc& e) { // dummy_node가 생성되지 않고 bad_alloc exception 발생
        return true; // true 반환
    }
}

bool SLL::IsEmpty() const {
    return head == nullptr;
}

size_t SLL::SizeIs() const {
    return size;
}

void SLL::Insert(Iterator pos, ItemType new_item) {
    if (IsFull()) {
        cerr << "List is Full, bad_alloc exception" << endl;
        return;
    }

    // pos == End()인 경우, 즉 current == nullptr이라면
    // "pos 다음에 삽입"이 불가능하므로 예외적으로 처리
    if (pos.GetCurrent() == nullptr) {
        cerr << "Iterator is End(), cannot insert after the end of the list." << endl;
        return;
    }

    Node* new_node = new Node(); // 새로운 노드 생성
    new_node->item = new_item; // 새로운 노드에 주어진 아이템 삽입

    // "pos 다음 위치"에 삽입
    Node* cur = pos.GetCurrent(); // 주어진 pos의 포인터 저장
    new_node->next = cur->next; // 새로운 노드의 next 포인터는 현재 노드의 다음 노드를 지칭
    cur->next = new_node; // 현재 노드의 next 포인터는 새로은 노드를 지칭

    size++;
}

void SLL::Erase(Iterator pos) {
    if (IsEmpty() || pos.GetCurrent() == nullptr) {
        cerr << "List is empty or invalid iterator, nothing to erase." << endl;
        return;
    }

    // pos == Begin()인 경우, 즉 current == head이라면
    if (pos.GetCurrent() == head) {
        Node* temp_ptr = head; // 기존 head 포인터 임시 저장
        head = head->next; // head 포인터를 head->next로 수정
        delete temp_ptr; // 기존 head 삭제(메모리 할당 해제)
    }

    // pos != Begin()인 경우, 즉 current != head이라면
    else {
        Node* prev_node = pos.GetPrevious(); // 현재 노드의 이전 노드 포인터 저장

        // 이전 노드가 nullptr이 아니라면 삭제 연산 수행
        // (head가 아니면서 이전 노드가 nullptr일 순 없으나, 만일의 경우를 대비한 예외처리)
        if (prev_node != nullptr) {
            prev_node->next = pos.GetCurrent()->next;
            // 이전 노드의 next 포인터가 현재 노드의 다음 노드 지칭하도록 수정
            // 현재 노드를 건너뛰게됨

            delete pos.GetCurrent(); // 현재 노드 삭제
        }
    }
    size--;
}

int main() {
    SLL list(5);

    SLL::Iterator it1 = list.Begin();
    list.Insert(it1, 10);
    list.Insert(++it1, 15);
    list.Insert(++it1, 20);

    cout << "List Size: " << list.SizeIs() << endl;

    for (SLL::Iterator it = list.Begin(); it != list.End(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // operator=() 테스트
    SLL::Iterator it2 = list.Begin();
    ++it2; // 두 번째 노드(10)로 이동
    SLL::Iterator it3 = it2; // operator=()로 상태 복사
    ++it3; // 복사된 이터레이터로 다음 노드(15)로 이동

    cout << "Current item in it2: " << *it2 << endl; // 10
    cout << "Current item in it3: " << *it3 << endl; // 15

    return EXIT_SUCCESS;
}