#include <iostream>

/**
 * Default constructor.
 * Initializes the list with null head and tail pointers and zero size.
 */
template<typename T>
SortedDoublyLinkedList<T>::SortedDoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

/**
 * Destructor.
 * Iterates through the list from head to tail and frees the memory allocated for each node.
 */
template<typename T>
SortedDoublyLinkedList<T>::~SortedDoublyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

/**
 * Inserts a new value into the doubly linked list while maintaining sorted (ascending) order.
 * It manages both the 'next' and 'prev' pointers to keep the list doubly linked.
 * @param value The value to insert.
 */
template<typename T>
void SortedDoublyLinkedList<T>::insert(T value) {
    Node* newNode = new Node(value);

    // Case 1: The list is empty.
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        listSize++;
        return;
    }

    // Case 2: The new value is smaller than or equal to the current head's value.
    // Insert at the very beginning (new head).
    if (value < head->data || value == head->data) { // Account for == if it's the smallest
        newNode->next = head;       // New node points to old head
        head->prev = newNode;       // Old head points back to new node
        head = newNode;             // Update head to the new node
        listSize++;
        return;
    }

    // Case 3: The new value should be inserted somewhere in the middle or at the end.
    Node* current = head;

    // Traverse until we find a node whose value is greater than the one we are inserting,
    // OR we reach the end of the list (current->next is null).
    while (current->next != nullptr && (current->next->data < value || current->next->data == value)) {
        current = current->next;
    }

    // Case 3a: We reached the end of the list. The new node becomes the new tail.
    if (current->next == nullptr) {
        current->next = newNode;    // Current tail points to new node
        newNode->prev = current;    // New node points back to current tail
        tail = newNode;             // Update tail pointer
    }
    // Case 3b: We found the correct spot in the middle of the list.
    // We insert between 'current' and 'current->next'.
    else {
        Node* nextNode = current->next; // The node that will follow the new node

        newNode->next = nextNode;   // New node points forward
        newNode->prev = current;    // New node points backward

        current->next = newNode;    // Preceding node points forward to new node
        nextNode->prev = newNode;   // Following node points backward to new node
    }

    listSize++;
}

/**
 * Removes the first occurrence of a specific value from the doubly linked list.
 * @param value The value to remove.
 * @return true if the value was successfully found and removed, false if not found.
 */
template<typename T>
bool SortedDoublyLinkedList<T>::remove(T value) {
    // Case 1: The list is empty.
    if (head == nullptr) {
        return false;
    }

    Node* current = head;

    // Traverse the list looking for the node containing the target value.
    while (current != nullptr && !(current->data == value)) {
        current = current->next;
    }

    // If current is null, we traversed the whole list and didn't find the value.
    if (current == nullptr) {
        return false;
    }

    // We found the node to delete ('current'). Now we handle the different cases.

    // Case 2: The node to delete is the only node in the list.
    if (current == head && current == tail) {
        head = nullptr;
        tail = nullptr;
    }
    // Case 3: The node to delete is the head (but there are other nodes).
    else if (current == head) {
        head = current->next;       // Move head pointer to the second node
        head->prev = nullptr;       // The new head has no previous node
    }
    // Case 4: The node to delete is the tail (but there are other nodes).
    else if (current == tail) {
        tail = current->prev;       // Move tail pointer to the second-to-last node
        tail->next = nullptr;       // The new tail has no next node
    }
    // Case 5: The node to delete is somewhere in the middle.
    else {
        Node* prevNode = current->prev;
        Node* nextNode = current->next;

        prevNode->next = nextNode;  // The node before skips over 'current'
        nextNode->prev = prevNode;  // The node after points back to the node before
    }

    // Free the memory of the removed node and update the size.
    delete current;
    listSize--;
    return true;
}

/**
 * Searches the list for a specific value.
 * @param value The value to search for.
 * @return true if the value is found, false otherwise.
 */
template<typename T>
bool SortedDoublyLinkedList<T>::search(T value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true; // Value found
        }
        // Optimization: Since it's sorted, if we see a larger value, we know it's not there.
        if (value < current->data) {
            return false;
        }
        current = current->next;
    }
    return false;
}

/**
 * Displays all elements in the list from head to tail.
 */
template<typename T>
void SortedDoublyLinkedList<T>::displayForward() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) {
            std::cout << " <-> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

/**
 * Displays all elements in the list from tail to head, demonstrating the backward links.
 */
template<typename T>
void SortedDoublyLinkedList<T>::displayBackward() const {
    Node* current = tail;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->prev != nullptr) {
            std::cout << " <-> ";
        }
        current = current->prev;
    }
    std::cout << std::endl;
}

/**
 * Returns the current size of the linked list.
 * @return The number of elements in the list.
 */
template<typename T>
int SortedDoublyLinkedList<T>::getSize() const {
    return listSize;
}