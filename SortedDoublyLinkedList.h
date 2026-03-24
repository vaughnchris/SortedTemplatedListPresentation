#ifndef SORTEDTEMPLATEDLIST_SORTEDDOUBLYLINKEDLIST_H
#define SORTEDTEMPLATEDLIST_SORTEDDOUBLYLINKEDLIST_H

/**
 * A templated class representing a sorted doubly linked list.
 * Elements are inserted in ascending order based on the < operator.
 *
 * In a doubly linked list, each node maintains pointers to both the
 * next node and the previous node, allowing for efficient traversal
 * in both directions.
 *
 * @tparam T The type of elements stored in the list. The type T must support
 *           the < (less than) and == (equality) operators.
 */
template<typename T>
class SortedDoublyLinkedList {
private:
    /**
     * Internal structure representing a single node in the doubly linked list.
     */
    struct Node {
        T data;     // The value stored in the node
        Node* next; // Pointer to the next node in the list
        Node* prev; // Pointer to the previous node in the list

        /**
         * Constructor to initialize a node with a given value.
         * @param val The value to store in the node.
         */
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;   // Pointer to the first node in the list
    Node* tail;   // Pointer to the last node in the list
    int listSize; // The current number of elements in the list

public:
    /**
     * Default constructor. Initializes an empty list.
     */
    SortedDoublyLinkedList();

    /**
     * Destructor. Frees all memory allocated for the nodes in the list.
     */
    ~SortedDoublyLinkedList();

    /**
     * Inserts a new value into the list while maintaining sorted order.
     * @param value The value to be inserted.
     */
    void insert(T value);

    /**
     * Removes the first occurrence of a specific value from the list.
     * @param value The value to be removed.
     * @return true if the value was found and removed, false otherwise.
     */
    bool remove(T value);

    /**
     * Searches for a specific value in the list.
     * @param value The value to search for.
     * @return true if the value is found, false otherwise.
     */
    bool search(T value) const;

    /**
     * Displays all elements in the list from head to tail.
     */
    void displayForward() const;

    /**
     * Displays all elements in the list from tail to head.
     * This showcases the advantage of the prev pointer.
     */
    void displayBackward() const;

    /**
     * Returns the current number of elements in the list.
     * @return The size of the list.
     */
    int getSize() const;
};

// Include the implementation file for template compilation
#include "SortedDoublyLinkedList.cpp"

#endif //SORTEDTEMPLATEDLIST_SORTEDDOUBLYLINKEDLIST_H