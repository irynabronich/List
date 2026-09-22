#include <iostream>

struct Node {
    int data;
    Node* prev;
    Node* next;
};

struct DoublyLinkedList {
    Node* head = nullptr;
    Node* tail = nullptr;
};

bool isEmpty(const DoublyLinkedList& list) {
    return list.head == nullptr;
}

int getLength(const DoublyLinkedList& list) {
    int length = 0;
    Node* current = list.head;
    while (current != nullptr) {
        length++;
        current = current->next;
    }
    return length;
}

void addToHead(DoublyLinkedList& list, int value) {
    Node* newNode = new Node{ value, nullptr, nullptr };
    if (isEmpty(list)) {
        list.head = newNode;
        list.tail = newNode;
    }
    else {
        newNode->next = list.head;
        list.head->prev = newNode;
        list.head = newNode;
    }
}

void addToTail(DoublyLinkedList& list, int value) {
    Node* newNode = new Node{ value, nullptr, nullptr };
    if (isEmpty(list)) {
        list.head = newNode;
        list.tail = newNode;
    }
    else {
        newNode->prev = list.tail;
        list.tail->next = newNode;
        list.tail = newNode;
    }
}

void printList(const DoublyLinkedList& list) {
    if (isEmpty(list)) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node* current = list.head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void clearList(DoublyLinkedList& list) {
    Node* current = list.head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    list.head = nullptr;
    list.tail = nullptr;
}

int countOccurrences(const DoublyLinkedList& list, int E) {
    int count = 0;
    Node* current = list.head;
    std::cout << "\n--- Pointer Transition Table (A) ---\n";
    std::cout << "Current Address\tValue\t\tNext Address\n";

    while (current != nullptr) {
        std::cout << current << "\t" << current->data << "\t\t" << current->next << "\n";
        if (current->data == E) {
            count++;
        }
        current = current->next;
    }
    return count;
}

DoublyLinkedList combineLists(const DoublyLinkedList& L1, const DoublyLinkedList& L2) {
    DoublyLinkedList L;
    Node* current = L1.head;

    std::cout << "\n--- Pointer Transition Table (B: L1) ---\n";
    std::cout << "Current Address\tValue\t\tCopy Status\n";
    while (current != nullptr) {
        std::cout << current << "\t" << current->data << "\t\t";
        if (current->data > 0) {
            addToTail(L, current->data);
            std::cout << "Added to L\n";
        }
        else {
            std::cout << "Skipped\n";
        }
        current = current->next;
    }

    current = L2.head;
    std::cout << "\n--- Pointer Transition Table (B: L2) ---\n";
    std::cout << "Current Address\tValue\t\tCopy Status\n";
    while (current != nullptr) {
        std::cout << current << "\t" << current->data << "\t\t";
        if (current->data < 0) {
            addToTail(L, current->data);
            std::cout << "Added to L\n";
        }
        else {
            std::cout << "Skipped\n";
        }
        current = current->next;
    }
    return L;
}

bool hasCycle(const DoublyLinkedList& list) {
    if (list.head == nullptr) return false;

    Node* slow = list.head;
    Node* fast = list.head;

    std::cout << "\n--- Pointer Transition Table (C) ---\n";
    std::cout << "Step\tSlow Pointer\tFast Pointer\n";

    int step = 1;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        std::cout << step++ << "\t" << slow << "\t" << fast << "\n";

        if (slow == fast) {
            return true;
        }
    }
    return false;
}

int main() {
    DoublyLinkedList L;
    addToTail(L, 5);
    addToTail(L, 3);
    addToTail(L, 7);
    addToTail(L, 3);
    addToTail(L, 9);

    std::cout << "Initial list L: ";
    printList(L);
    std::cout << "Length of list L: " << getLength(L) << std::endl;

    int E = 3;
    int occurrences = countOccurrences(L, E);
    std::cout << "\nResult of Task A: Element " << E << " appears in the list " << occurrences << " time(s).\n";
    std::cout << "List content: ";
    printList(L);
    std::cout << "List length: " << getLength(L) << std::endl;

    DoublyLinkedList L1, L2;
    addToTail(L1, -1);
    addToTail(L1, 10);
    addToTail(L1, 4);
    addToTail(L2, -5);
    addToTail(L2, 8);
    addToTail(L2, -2);

    std::cout << "\nList L1: ";
    printList(L1);
    std::cout << "List L2: ";
    printList(L2);

    DoublyLinkedList Lcombined = combineLists(L1, L2);
    std::cout << "\nResult of Task B (New list L): ";
    printList(Lcombined);
    std::cout << "Length of new list L: " << getLength(Lcombined) << std::endl;

    std::cout << "\nCycle check without a cycle:";
    bool cycleRes1 = hasCycle(Lcombined);
    std::cout << "Result of Task C: " << (cycleRes1 ? "Cycle detected" : "No cycle") << std::endl;

    if (Lcombined.tail != nullptr && Lcombined.head != nullptr) {
        Lcombined.tail->next = Lcombined.head->next;
    }

    std::cout << "\nCycle check after creating an artificial cycle:";
    bool cycleRes2 = hasCycle(Lcombined);
    std::cout << "Result of Task C: " << (cycleRes2 ? "Cycle is there" : "No cycle") << std::endl;

    if (Lcombined.tail != nullptr) {
        Lcombined.tail->next = nullptr;
    }

    clearList(L);
    clearList(L1);
    clearList(L2);
    clearList(Lcombined);

    return 0;
}
