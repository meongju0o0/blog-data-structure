#include <iostream>

#define MAX_ITEMS 50

using namespace std;

typedef int ItemType;
class SortedList;

class SortedList {
public:
    SortedList();
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
    int length; // 리스트의 길이 관리
    ItemType info[MAX_ITEMS]{}; // 리스트에 저장된 데이터 관리
    int currentPos; // 리스트의 현재 위치 관리
};

SortedList::SortedList() {
    length = 0;
    currentPos = 0;
}

void SortedList::InsertItem(const ItemType item) {
    // array가 꽉 찬 경우 아이템 삽입 불가
    if (IsFull()) {
        cerr << "List is full. Cannot insert item." << endl;
        return;
    }

    // 이진 탐색으로 삽입 위치 찾기
    int first = 0, last = length - 1;
    while (first <= last) {
        int mid = (first + last) / 2;
        if (info[mid] < item) {
            first = mid + 1;
        } else {
            last = mid - 1;
        }
    }
    const int correctPos = first; // 삽입 위치는 first가 최종적으로 가리키는 위치

    // 삽입 위치 이후의 요소를 한 칸씩 뒤로 이동
    for (int i = length; i > correctPos; i--) {
        info[i] = info[i - 1];
    }

    // 삽입 위치에 아이템 삽입
    info[correctPos] = item;
    length++; // 리스트 길이 증가
}

void SortedList::DeleteItem(const ItemType item) {
    // array가 비어있는 경우 아이템 삭제 불가
    if (IsEmpty()) {
        cerr << "List is empty. Cannot delete item." << endl;
        return;
    }

    // 이진 탐색으로 삭제 위치 찾기
    int first = 0, last = length - 1;
    while (first <= last) {
        int mid = (first + last) / 2;
        if (info[mid] < item) {
            first = mid + 1;
        } else {
            last = mid - 1;
        }
    }
    const int correctPos = first; // 삭제 위치는 first가 최종적으로 가리키는 위치

    // 해당 위치에 아이템을 한 칸씩 앞으로 이동
    for (int i = correctPos; i < length; i++) {
        info[i] = info[i+1];
    }

    length--; // 리스트 길이 감소
}

void SortedList::MakeEmpty() {
    length = 0;
}

bool SortedList::RetrieveItem(const ItemType& item) const { // BinarySearch 구현
    int first = 0; // 탐색 범위 시작 인덱스
    int last = length - 1; // 탐색 범위 마지막 인덱스
    bool found = false; // 탐색 완료 시 참으로 변경
    while ((first <= last) && !found) {
        const int midPoint = (first + last) / 2; // 탐색 범위 중심 계산
        if (item < info[midPoint]) {
            last = midPoint - 1;
        }
        else if (item > info[midPoint]) {
            first = midPoint + 1;
        }
        else if (info[midPoint] == item) { // 일치하는 아이템이 있으면
            found = true; // found 참으로 변환
        }
    }
    return found;
}

int SortedList::LengthIs() const {
    return length;
}

bool SortedList::IsFull() const {
    return length == MAX_ITEMS;
}

bool SortedList::IsEmpty() const {
    return length == 0;
}

void SortedList::ResetList() {
    currentPos = 0;
}

ItemType SortedList::GetNextItem() {
    return info[currentPos++];
}

int main() {
    SortedList list;

    list.InsertItem(30);
    list.InsertItem(10);
    list.InsertItem(20);
    list.InsertItem(-7);
    list.InsertItem(70);
    list.InsertItem(60);
    list.InsertItem(-5);

    cout << "Length of list: " << list.LengthIs() << endl;

    cout << "Items in the list (sorted): ";
    list.ResetList();
    for (int i = 0; i < list.LengthIs(); i++) {
        cout << list.GetNextItem() << " ";
    }
    cout << endl;

    if (list.IsFull())
        cout << "The list is full." << endl;
    else
        cout << "The list is not full." << endl;

    int item = 20;
    list.ResetList();
    if (list.RetrieveItem(item))
        cout << "Item " << item << " found in the list." << endl;
    else
        cout << "Item " << item << " not found in the list." << endl;

    list.DeleteItem(20);
    cout << "Item 20 deleted." << endl;
    cout << "Length of list after deletion: " << list.LengthIs() << endl;

    cout << "Items in the list (sorted): ";
    list.ResetList();
    for (int i = 0; i < list.LengthIs(); i++) {
        cout << list.GetNextItem() << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}