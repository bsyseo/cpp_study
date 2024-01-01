#include <iostream>

class Node {
public:
    int data;
    Node* next;

};

class Link {
public:
    Node* head; // 리스트의 헤드(첫 번째 노드)를 가리키는 포인터

    Link() : head(nullptr) {} // Link 클래스의 생성자 정의, 시작할 때 아무 노드도 가리키지 않는 상태로 설정

    void insert(int data);
    int getData(int nodeIndex);
    void deleteData(int nodeIndex);
    void printList();
};

void Link::insert(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* tempNode = head;
        while (tempNode->next != nullptr) {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
}

int Link::getData(int nodeIndex) {
    Node* tempNode = head;
    int currentIndex = 0;

    while (tempNode != nullptr) {
        if (currentIndex == nodeIndex) {
            return tempNode->data;
        }
        currentIndex++;
        tempNode = tempNode->next;
    }

    // Return an invalid value if the nodeIndex is out of range
    return -1;
}

void Link::printList() {
    Node* tempNode = head;

    if (tempNode == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    }

    while (tempNode != nullptr) {
        std::cout << tempNode->data << " ";
        tempNode = tempNode->next;
    }
    std::cout << std::endl;
}

void Link::deleteData(int nodeIndex) {
    if (head == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    }

    Node* tempNode = head;

    if (nodeIndex == 0) {
        head = tempNode->next;
        delete tempNode;
        return;
    }

    int currentIndex = 0;
    while (tempNode != nullptr && currentIndex < nodeIndex - 1) {
        tempNode = tempNode->next;
        currentIndex++;
    }

    if (tempNode == nullptr || tempNode->next == nullptr) {
        std::cout << "Index out of range." << std::endl;
        return;
    }

    Node* nodeToDelete = tempNode->next;
    tempNode->next = nodeToDelete->next;
    delete nodeToDelete;
}

int main() {
    Link l;
    int choice;
    int data;

    do {
        std::cout << "1. Insert Data 2. Print List 3. Get Data 4. Delete Node 5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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
