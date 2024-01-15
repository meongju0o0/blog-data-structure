//
// Created by meongju0o0 on 2024-01-15.
//

#include <iostream>
#include <climits>
using namespace std;

#define MAX_ITEMS 50
typedef int ItemType;
class SortedType;

class SortedType {
public:
    SortedType();
    [[nodiscard]] bool IsFull() const; //리스트가 가득 차있는지 확인
    [[nodiscard]] int LengthIs() const; //리스트 길이 반환
    bool RetrieveItem(ItemType& item); //리스트에 파라미터로 준 아이템이 있는지 확인
    void InsertItem(ItemType item); //입력받은 아이템을 삽입
    void DeleteItem(ItemType item); //입력받은 아이템과 일치하는 아이템을 삭제
    void MakeEmpty(); //현재 리스트의 모든 요소 삭제
    void ResetList(); //아이템을 가리키는 CurrentPos를 0으로 초기화
    ItemType GetNextItem(); //다음 위치의 아이템을 반환

private:
    int length;
    ItemType info[MAX_ITEMS]{};
    int currentPos;
};

SortedType::SortedType() {
    length = 0;
    currentPos = 0;
    for (int& i : info) {
        i = INT_MIN; //편의상 INT_MIN으로 고정, 자료형 변경 시 수정 필요
    }
}

void SortedType::InsertItem(ItemType item) {
    //아이템을 삽입할 위치 찾기
    int correctPos = 0;
    for (int i = 0; i < length; i++) {
        if (info[i] <= item) {
            correctPos++;
        }
        else {
            break;
        }
    }
    //해당 위치 뒤부터 있는 아이템들을 한 칸씩 미루기
    for (int i = length; i > correctPos; i--) {
        info[i] = info[i-1];
    }
    //해당 위치에 넣고자 하는 아이템을 넣기
    info[correctPos] = item;
    length++; //길이를 1만큼 늘림
}

void SortedType::DeleteItem(ItemType item) {
    //아이템을 삭제할 위치 찾기
    int correctPos = 0;
    for (int i = 0; i < length; i++) {
        if (info[i] != item) {
            correctPos++;
        }
        else {
            break;
        }
    }
    //해당 위치에 아이템을 한 칸 씩 앞으로 당기기
    for (int i = correctPos; i < length; i++) {
        info[i] = info[i+1];
    }
    info[length - 1] = INT_MIN;
    length--; //길이를 1만큼 줄임
}

void SortedType::MakeEmpty() {
    for (int& i : info) {
        i = INT_MIN;
    }
    length = 0;
}

bool SortedType::RetrieveItem(ItemType& item) { //BinarySearch 구현
    int first = 0; //탐색 범위 시작 인덱스
    int last = length - 1; //탐색 범위 마지막 인덱스
    int midPoint = (first + last) / 2; //탐색 범위 중심 인덱스
    bool found = false; //탐색 완료 시 참으로 변경
    while ((first <= last) && !found) {
        midPoint = (first + last) / 2; //탐색 범위 중심 계산
        if (item < info[midPoint]) {
            last = midPoint - 1;
        }
        else if (item > info[midPoint]) {
            first = midPoint + 1;
        }
        else if (info[midPoint] == item) { //일치하는 아이템이 있으면
            found = true; //found 참으로 변환
        }
    }
    return found;
}

int SortedType::LengthIs() const {
    return length;
}

bool SortedType::IsFull() const {
    return length == MAX_ITEMS;
}

void SortedType::ResetList() {
    currentPos = 0;
}

ItemType SortedType::GetNextItem() {
    return info[currentPos++];
}

int main() {
    SortedType list;

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
