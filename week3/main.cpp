#include <iostream>
#include "LinkedQuick.h"

int main() {
    Link l;
    int choice;
    int data;

    do {
        std::cout << "1. Insert Data 2. Print List 3. Quick Sort 4. Exit" << std::endl;
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
            std::cout << "Applying Quick Sort..." << std::endl;
            l.quickSort();
            std::cout << "List after Quick Sort: ";
            l.printList();
            break;
        case 4:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
        }
    } while (choice != 4);

    return 0;
}