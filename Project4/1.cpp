#include <iostream>

// Node 클래스 정의
class Node {
public:
    int data;     // 노드의 데이터를 저장하는 변수
    Node* next;   // 다음 노드를 가리키는 포인터
};

// Link 클래스 정의
class Link {
public:
    Node* head; // 리스트의 헤드(첫 번째 노드)를 가리키는 포인터

    // Link 클래스의 생성자 정의, 시작할 때 아무 노드도 가리키지 않는 상태로 설정
    Link() : head(nullptr) {} 

    // 데이터 삽입 메서드 정의
    void insert(int data);

    // 특정 인덱스의 데이터 반환 메서드 정의
    int getData(int nodeIndex);

    // 리스트 출력 메서드 정의
    void printList();

    // 특정 인덱스의 데이터 삭제 메서드 정의
    void deleteData(int nodeIndex);
};

// 데이터 삽입 메서드 구현
void Link::insert(int data) {
    Node* newNode = new Node(); // 새로운 노드 생성
    newNode->data = data;
    newNode->next = nullptr;

    // 리스트가 비어있을 경우 새로운 노드를 헤드로 설정
    if (head == nullptr) {
        head = newNode;
    }
    else {
        // 리스트가 비어있지 않을 경우 마지막 노드까지 이동한 후 새로운 노드를 추가
        Node* tempNode = head;
        while (tempNode->next != nullptr) {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
}

// 특정 인덱스의 데이터 반환 메서드 구현
int Link::getData(int nodeIndex) {
    Node* tempNode = head;
    int currentIndex = 0;

    // 인덱스에 해당하는 노드까지 이동하면서 데이터 반환
    while (tempNode != nullptr) {
        if (currentIndex == nodeIndex) {
            return tempNode->data;
        }
        currentIndex++;
        tempNode = tempNode->next;
    }

    // 인덱스가 범위를 벗어날 경우 -1 반환
    return -1;
}

// 리스트 출력 메서드 구현
void Link::printList() {
    Node* tempNode = head;

    // 리스트가 비어있을 경우 메시지 출력 후 종료
    if (tempNode == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    }

    // 리스트의 모든 노드의 데이터 출력
    while (tempNode != nullptr) {
        std::cout << tempNode->data << " ";
        tempNode = tempNode->next;
    }
    std::cout << std::endl;
}

// 특정 인덱스의 데이터 삭제 메서드 구현
void Link::deleteData(int nodeIndex) {
    // 리스트가 비어있을 경우 메시지 출력 후 종료
    if (head == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    }

    Node* tempNode = head;

    // 헤드 노드를 삭제하는 경우
    if (nodeIndex == 0) {
        head = tempNode->next;
        delete tempNode;
        return;
    }

    int currentIndex = 0;
    // 삭제할 노드의 이전 노드까지 이동
    while (tempNode != nullptr && currentIndex < nodeIndex - 1) {
        tempNode = tempNode->next;
        currentIndex++;
    }

    // 인덱스가 범위를 벗어나거나 마지막 노드를 삭제하려는 경우 메시지 출력 후 종료
    if (tempNode == nullptr || tempNode->next == nullptr) {
        std::cout << "Index out of range." << std::endl;
        return;
    }

    // 삭제할 노드를 임시로 저장하고 이전 노드의 next를 삭제할 노드의 next로 설정
    Node* nodeToDelete = tempNode->next;
    tempNode->next = nodeToDelete->next;
    delete nodeToDelete;
}

// 메인 함수
int main() {
    Link l;     // Link 클래스의 객체 생성
    int choice; // 사용자의 선택을 저장하는 변수
    int data;   // 사용자로부터 입력받는 데이터

    // 사용자가 종료를 선택할 때까지 반복
    do {
        // 메뉴 출력
        std::cout << "1. Insert Data 2. Print List 3. Get Data 4. Delete Node 5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // 사용자의 선택에 따라 해당하는 동작 수행
        switch (choice) {
        case 1:
            std::cout << "Enter data to insert: ";
            std::cin >> data;
            l.insert(data);
            break;
        case 2:
            std::cout << "List: ";
            l.printList();
            break;
        case 3:
            int nodeIndex;
            std::cout << "Enter node index: ";
            std::cin >> nodeIndex;
            data = l.getData(nodeIndex);
            if (data != -1) {
                std::cout << "Data at index " << nodeIndex << ": " << data << std::endl;
            }
            else {
                std::cout << "Invalid index." << std::endl;
            }
            break;
        case 4:
            int delIndex;
            std::cout << "Enter index to delete: ";
            std::cin >> delIndex;
            l.deleteData(delIndex);
            break;
        case 5:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
        }
    } while (choice != 5);

    return 0;
}
