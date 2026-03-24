#ifndef SORTEDTEMPLATEDLIST_SORTEDLINKEDLIST_H
#define SORTEDTEMPLATEDLIST_SORTEDLINKEDLIST_H

/**
 * A templated class representing a sorted singly linked list.
 * Elements are inserted in ascending order based on the < operator.
 *
 * @tparam T The type of elements stored in the list. The type T must support
 *           the < (less than) and == (equality) operators for sorting and searching.
 */
template<typename T>
class SortedLinkedList {
private:
    /**
     * Internal structure representing a single node in the linked list.
     */
    struct Node {
        T data;     // The value stored in the node
        Node* next; // Pointer to the next node in the list

        /**
         * Constructor to initialize a node with a given value.
         * @param val The value to store in the node.
         */
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;   // Pointer to the first node in the list
    int listSize; // The current number of elements in the list

public:
    /**
     * Default constructor. Initializes an empty list.
     */
    SortedLinkedList();

    /**
     * Destructor. Frees all memory allocated for the nodes in the list.
     */
    ~SortedLinkedList();

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
     * Displays all elements in the list to standard output.
     * Elements are separated by " -> ".
     */
    void display() const;

    /**
     * Returns the current number of elements in the list.
     * @return The size of the list.
     */
    int getSize() const;
};

// Include the implementation file because this is a template class.
// Template definitions typically need to be visible to the compiler
// at the point of instantiation.
#include "SortedLinkedList.cpp"

#endif //SORTEDTEMPLATEDLIST_SORTEDLINKEDLIST_H