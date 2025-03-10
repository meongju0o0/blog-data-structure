#include <iostream>

#define MAX_ITEMS 50

using namespace std;

typedef int ItemType;
class UnsortedList;

class UnsortedList {
public:
    UnsortedList();
    [[nodiscard]] bool IsFull() const; // 리스트가 가득 차있는지 확인
    [[nodiscard]] bool IsEmpty() const; // 리스트가 모두 비었는지 확인
    [[nodiscard]] int LengthIs() const; // 리스트 길이 반환
    [[nodiscard]] bool RetrieveItem(const ItemType& item) const; // 리스트에 파라미터로 준 아이템이 있는지 확인
    void InsertItem(ItemType item); // 입력받은 아이템을 삽입
    void DeleteItem(ItemType item); // 입력받은 아이템과 일치하는 아이템을 삭제
    void MakeEmpty(); // 현재 리스트의 모든 요소 삭제
    void ResetList(); // 아이템을 가리키는 CurrentPos를 0으로 초기화
    ItemType GetNextItem(); // 다음 위치의 아이템을 반환

private:
    int length;
    ItemType info[MAX_ITEMS]{};
    int currentPos;
};

UnsortedList::UnsortedList() {
    length = 0;
    currentPos = 0;
}

void UnsortedList::InsertItem(ItemType item) {
    info[length++] = item;
}

void UnsortedList::DeleteItem(ItemType item) {
    for (int i = 0; i < length; i++) { // list 길이 만큼 일치하는 아이템이 있는지 탐색
        if (info[i] == item) { // 일치하는 아이템이 있으면
            info[i] = info[length-1]; // 맨 마지막 요소를 해당 위치로 옮김
            length--; // 맨 마지막 요소를 지웠다 가정한 후 길이를 줄임
        }
    }
}

void UnsortedList::MakeEmpty() {
    length = 0; // length를 0으로 만들어 리스트가 빈 것 처럼 만듦
}

bool UnsortedList::RetrieveItem(const ItemType& item) const {
    for (int i = 0; i < length; i++) { // list 길이 만큼 일치하는 아이템이 있는지 탐색
        if (info[i] == item) { // 일치하는 아이템이 있으면
            return true; // true 반환
        }
    }
    return false; // 일치하는 아이템을 찾지 못하면 false 반환
}

int UnsortedList::LengthIs() const {
    return length;
}

bool UnsortedList::IsFull() const {
    return length == MAX_ITEMS;
}

bool UnsortedList::IsEmpty() const {
    return length == 0;
}

void UnsortedList::ResetList() {
    currentPos = 0;
}

ItemType UnsortedList::GetNextItem() {
    return info[currentPos++];
}

int main() {
    UnsortedList list;

    for (int i = 1; i <= 3; i++) {
        list.InsertItem(i * 10);
    }

    cout << "Length of list: " << list.LengthIs() << endl;

    if (list.IsFull()) {
        cout << "The list is full." << endl;
    }
    else {
        cout << "The list is not full." << endl;
    }

    int item = 20;
    if (list.RetrieveItem(item)) {
        cout << "Item " << item << " found in the list." << endl;
    }
    else {
        cout << "Item " << item << " not found in the list." << endl;
    }

    list.DeleteItem(20);
    cout << "Item 20 deleted." << endl;
    cout << "Length of list after deletion: " << list.LengthIs() << endl;

    list.ResetList();
    cout << "Items in the list: ";
    for (int i = 0; i < list.LengthIs(); i++) {
        cout << list.GetNextItem() << " ";
    }
    cout << endl;

    list.MakeEmpty();
    cout << "Length of list: " << list.LengthIs() << endl;

    return EXIT_SUCCESS;
}