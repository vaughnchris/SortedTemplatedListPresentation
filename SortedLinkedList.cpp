#include <iostream>

/**
 * Default constructor.
 * Initializes the list with a null head pointer and zero size.
 * @tparam T The type of elements in the list.
 */
template<typename T>
SortedLinkedList<T>::SortedLinkedList() : head(nullptr), listSize(0) {}

/**
 * Destructor.
 * Iterates through the list and frees the memory allocated for each node
 * to prevent memory leaks.
 * @tparam T The type of elements in the list.
 */
template<typename T>
SortedLinkedList<T>::~SortedLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next; // Store the next pointer before deleting current
        delete current;             // Free the memory of the current node
        current = next;             // Move to the next node
    }
}

/**
 * Inserts a new value into the list while maintaining sorted (ascending) order.
 * It dynamically allocates a new node and finds the correct insertion point.
 * @tparam T The type of elements in the list.
 * @param value The value to insert.
 */
template<typename T>
void SortedLinkedList<T>::insert(T value) {
    Node* newNode = new Node(value);

    // Case 1: The list is empty, OR the new value is smaller than the current head's value.
    // In this case, the new node becomes the new head of the list.
    if (head == nullptr || value < head->data) {
        newNode->next = head; // Point the new node's next to the current head (which might be nullptr)
        head = newNode;       // Update the head pointer to the new node
    } else {
        // Case 2: The new value should be inserted somewhere after the head.
        Node* current = head;

        // Traverse the list until we find a node whose next node has a value greater than or equal
        // to the value we are inserting, or we reach the end of the list.
        while (current->next != nullptr && current->next->data < value) {
            current = current->next;
        }

        // Insert the new node between 'current' and 'current->next'
        newNode->next = current->next; // Point new node to the next node in the sequence
        current->next = newNode;       // Point the current node to the newly inserted node
    }
    listSize++; // Increment the size of the list
}

/**
 * Removes the first occurrence of a specific value from the list.
 * @tparam T The type of elements in the list.
 * @param value The value to remove.
 * @return true if the value was successfully found and removed, false if not found.
 */
template<typename T>
bool SortedLinkedList<T>::remove(T value) {
    // Case 1: The list is empty. Nothing to remove.
    if (head == nullptr) {
        return false;
    }

    // Case 2: The value to remove is at the head of the list.
    if (head->data == value) {
        Node* temp = head;   // Temporarily store the head node to delete it later
        head = head->next;   // Update head to the second node
        delete temp;         // Free memory of the old head
        listSize--;          // Decrement the list size
        return true;
    }

    // Case 3: The value to remove is located somewhere after the head.
    Node* current = head;

    // Traverse the list looking for the node BEFORE the node to be removed.
    // We stop if we reach the end, or if the next node contains the target value.
    while (current->next != nullptr && !(current->next->data == value)) {
        current = current->next;
    }

    // If current->next is not nullptr, it means we found the node containing the value.
    if (current->next != nullptr) {
        Node* temp = current->next;  // The node to be deleted
        current->next = temp->next;  // Bypass the node to be deleted, linking current to the node after temp
        delete temp;                 // Free memory of the removed node
        listSize--;                  // Decrement the list size
        return true;
    }

    // Case 4: We reached the end of the list without finding the value.
    return false;
}

/**
 * Searches the list for a specific value.
 * @tparam T The type of elements in the list.
 * @param value The value to search for.
 * @return true if the value is found, false otherwise.
 */
template<typename T>
bool SortedLinkedList<T>::search(T value) const {
    Node* current = head;

    // Traverse the list
    while (current != nullptr) {
        // If the current node contains the target value, return true
        if (current->data == value) {
            return true;
        }
        current = current->next; // Move to the next node
    }

    // The entire list was traversed and the value was not found
    return false;
}

/**
 * Displays all elements currently in the list to the standard output.
 * Elements are printed sequentially, separated by " -> ".
 * @tparam T The type of elements in the list.
 */
template<typename T>
void SortedLinkedList<T>::display() const {
    Node* current = head;

    // Traverse and print each element
    while (current != nullptr) {
        std::cout << current->data;
        // Print a separator if it's not the last element
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << std::endl; // Print a newline at the end
}

/**
 * Returns the current size of the linked list.
 * @tparam T The type of elements in the list.
 * @return The number of elements in the list.
 */
template<typename T>
int SortedLinkedList<T>::getSize() const {
    return listSize;
}