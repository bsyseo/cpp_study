#include <iostream>

class Node
{
public:
    int data;
    Node *next;

    //생성자 정의: 기본값을 가진 매개변수를 사용하여 초기화
    Node(int val = 0) : data(val), next(nullptr) {}
};

class Link
{
public:
    Node *head = nullptr; //LinkedListdml head Node

    void insert(int data);
    void printList();
    void quickSort(); // 퀵 정렬을 위한 메서드

    Link()
    {
        head = nullptr;
    }

private:
    Node *partition(Node *low, Node *high); // 퀵 소트에서 사용할 파티션 메서드
    void quickSort(Node *low, Node *high);  // 퀵 소트의 재귀 호출을 위한 메서드
};

void Link::insert(int data)
{
    Node *newNode = new Node(data); // 새로운 노드 생성
    newNode->next = nullptr;

    // 리스트가 비어있을 경우 새로운 노드를 헤드로 설정
    if (head == nullptr)
    {
        head = newNode;
    }

    // 리스트가 비어있지 않을 경우 마지막 노드까지 이동한 후 새로운 노드를 추가
    else
    {
        Node *tempNode = head;
        while (tempNode->next != nullptr)
        {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
}

void Link::printList()
{
    Node *tempNode = head;

    if (tempNode == nullptr)
    {
        std::cout << "List is empty." << std::endl;
        return;
    }

    while (tempNode != nullptr)
    {
        std::cout << tempNode->data << " ";
        tempNode = tempNode->next;
    }
    std::cout << std::endl;
}

//Link 클래스의 partition 메서드 정의
Node *Link::partition(Node *low, Node *high)
{
    int pivot = high->data; //high가 가리키는 노드의 데이터 값을 가져오고 high가 가리키는 노드의 데이터 값이 pivot에 저장
    Node *i = low;
//i는 Node 타입의 포인터
//i가 가리킬 것은 파티션을 수행하면서 피벗보다 작은 값을 갖는 노드들의 위치를 나타내게 됩니다.

    // 리스트를 피벗을 기준으로 분할
    for (Node *j = low; j != high; j = j->next)
    {
        if (j->data < pivot)
        {
            std::swap(i->data, j->data);
            i = i->next;
        }
    }

    // 피벗의 위치를 바꾸어 정렬 완료
    std::swap(i->data, high->data);
    return i;
}

// 퀵 정렬의 재귀 호출을 위한 메서드
void Link::quickSort(Node *low, Node *high)
{
    if (low != nullptr && high != nullptr && low != high && low != high->next)
    {
        // 현재 리스트를 피벗을 기준으로 파티션
        Node *pivot = partition(low, high);

        // 피벗을 기준으로 양쪽 부분 리스트에 대해 재귀적으로 퀵 정렬 수행
        quickSort(low, pivot);
        quickSort(pivot->next, high);
    }
}

void Link::quickSort()
{
    // 퀵 소트를 시작하기 위해 head와 마지막 노드를 전달
    Node *lastNode = head;
    while (lastNode != nullptr && lastNode->next != nullptr)
    {
        lastNode = lastNode->next;
    }

    quickSort(head, lastNode);
}