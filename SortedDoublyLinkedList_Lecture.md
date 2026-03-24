# Sorted Doubly Linked List: Insertion and Removal Logic

## Introduction

In our previous session, we built a sorted *singly* linked list. Today, we're upgrading our data structure to a **sorted doubly linked list**.

The key difference is that each node now has *two* pointers:
1.  `next`: Points to the next node in the sequence.
2.  `prev`: Points to the previous node in the sequence.

This bidirectional linking allows for traversal in both directions (forward and backward) and can make certain operations, like deletion, more straightforward if you already have a pointer to the node. However, it also means we have more pointers to manage during insertions and removals!

---

## 1. The `Node` Structure

First, let's look at how our `Node` structure changes:

```cpp
template <typename T>
struct Node {
    T data;
    Node* next; // Points forward
    Node* prev; // Points backward

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};
```

We also add a `tail` pointer to our class to keep track of the end of the list, which makes backward traversal possible from the start.

```cpp
template<typename T>
class SortedDoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int listSize;
    // ...
```

---

## 2. Insertion Logic

Inserting a node into a sorted doubly linked list involves finding the correct position and then carefully updating up to four pointers:
1.  The new node's `next`
2.  The new node's `prev`
3.  The preceding node's `next`
4.  The following node's `prev`

We must handle several distinct cases.

### Case 1: The List is Empty

If the list is empty, the new node becomes both the `head` and the `tail`. Its `next` and `prev` remain `nullptr`.

```cpp
if (head == nullptr) {
    head = newNode;
    tail = newNode;
    listSize++;
    return;
}
```

### Case 2: Inserting at the Head (New Smallest Value)

If the new value is smaller than or equal to the current `head`'s data, we must insert it at the very beginning.

```cpp
if (value <= head->data) {
    newNode->next = head; // 1. New node points forward to old head
    head->prev = newNode; // 2. Old head points backward to new node
    head = newNode;       // 3. Update the head pointer to the new node
                          // newNode->prev remains nullptr
    listSize++;
    return;
}
```

### Finding the Insertion Point

For all other cases, we traverse the list to find the correct spot. We look for a node (`current`) whose *next* node has a value greater than or equal to the value we are inserting.

```cpp
Node* current = head;
while (current->next != nullptr && current->next->data < value) {
    current = current->next;
}
```

After this loop, we insert the new node *after* `current`.

### Case 3: Inserting at the Tail (New Largest Value)

If the loop terminates because `current->next == nullptr`, we are at the end of the list. The new node becomes the new `tail`.

```cpp
if (current->next == nullptr) {
    current->next = newNode; // 1. Old tail points forward to new node
    newNode->prev = current; // 2. New node points backward to old tail
    tail = newNode;          // 3. Update the tail pointer to the new node
                             // newNode->next remains nullptr
}
```

### Case 4: Inserting in the Middle

If `current->next != nullptr`, we are inserting between `current` and `current->next` (which we'll call `nextNode`).

```cpp
else {
    Node* nextNode = current->next;

    // Set pointers for the new node
    newNode->next = nextNode; // 1. New node points forward
    newNode->prev = current;  // 2. New node points backward

    // Update surrounding nodes
    current->next = newNode;  // 3. Preceding node points forward to new node
    nextNode->prev = newNode; // 4. Following node points backward to new node
}
```

---

## 3. Removal Logic

Removing a node also requires careful pointer management to ensure the list remains connected. Like insertion, we must handle different cases based on where the target node is located.

First, we traverse to find the node containing the target value:

```cpp
Node* current = head;
while (current != nullptr && current->data != value) {
    current = current->next;
}

// If current is nullptr, the value wasn't found.
if (current == nullptr) return false;
```

Once we have the node (`current`) to delete, we handle the following cases:

### Case 1: Removing the Only Node in the List

If `current` is both the `head` and the `tail`, removing it empties the list.

```cpp
if (current == head && current == tail) {
    head = nullptr;
    tail = nullptr;
}
```

### Case 2: Removing the Head Node

If the node to remove is the `head` (but not the `tail`), we update the `head` pointer and remove the `prev` link from the new head.

```cpp
else if (current == head) {
    head = current->next; // 1. Move head to the second node
    head->prev = nullptr; // 2. The new head has no previous node
}
```

### Case 3: Removing the Tail Node

If the node to remove is the `tail` (but not the `head`), we update the `tail` pointer and remove the `next` link from the new tail.

```cpp
else if (current == tail) {
    tail = current->prev; // 1. Move tail to the second-to-last node
    tail->next = nullptr; // 2. The new tail has no next node
}
```

### Case 4: Removing a Node from the Middle

If the node is in the middle, we need to bypass it by connecting its `prev` node directly to its `next` node.

```cpp
else {
    Node* prevNode = current->prev;
    Node* nextNode = current->next;

    prevNode->next = nextNode; // 1. Node before skips over 'current'
    nextNode->prev = prevNode; // 2. Node after points back to the node before
}
```

### Final Cleanup

Regardless of the case, we must free the memory and decrement the size.

```cpp
delete current;
listSize--;
return true;
```

---

## Summary

Managing a doubly linked list requires diligence when updating pointers. A good rule of thumb when inserting or removing in the middle is:

1.  **Always update the new node's pointers first.** (e.g., `newNode->next`, `newNode->prev`)
2.  **Then update the surrounding nodes' pointers.** (e.g., `current->next`, `nextNode->prev`)

This prevents you from accidentally losing track of the rest of the list before you've made the necessary connections!