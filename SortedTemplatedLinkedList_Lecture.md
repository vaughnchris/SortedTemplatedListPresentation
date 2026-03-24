# Sorted Templated Linked List: A Data Structures Example

## Introduction

Good morning, class! Today, we're diving into data structures with a practical example: a **sorted templated linked list** in C++. This project demonstrates key concepts like linked lists, sorting, templates, and memory management. We'll explore how to implement a generic, sorted data structure that can handle different data types, including custom objects.

## What is a Linked List?

A linked list is a linear data structure where elements are stored in nodes. Each node contains:
- Data
- A pointer to the next node

Unlike arrays, linked lists allow dynamic sizing and efficient insertions/deletions anywhere in the list.

### Types of Linked Lists
- **Singly Linked List**: Each node points to the next.
- **Doubly Linked List**: Nodes point to both next and previous.
- **Circular Linked List**: Last node points back to the first.

Our example uses a singly linked list.

## Adding Sorting

A sorted linked list maintains elements in order (e.g., ascending). Insertions place new elements in the correct position to preserve order.

Benefits:
- Fast searches (we can stop early if we pass the target value)
- Ordered output without a separate sorting step

Drawbacks:
- Insertions are O(n) in worst case (we must traverse to find the spot)

## Templates in C++

Templates allow generic programming. Our `SortedLinkedList<T>` works with any type `T` that supports comparison.

```cpp
template <typename T>
class SortedLinkedList {
    // ...
};
```

This enables reuse for `int`, `std::string`, and custom types like a `Person` struct!

## Project Structure

The project separates concerns:
- `SortedLinkedList.h`: Declarations and documentation.
- `SortedLinkedList.cpp`: Implementations.
- `main.cpp`: Demonstration of various data types.

**Important Note on Templates:** Because we are using templates, the implementation file (`.cpp`) is actually included at the bottom of the header file (`.h`). This is necessary because the compiler needs to see the full implementation when it instantiates a template for a specific type.

### Node Structure (Inner Class)

We encapsulate the `Node` structure within the `SortedLinkedList` class:

```cpp
template <typename T>
class SortedLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    // ...
};
```

### Class Declaration

```cpp
template<typename T>
class SortedLinkedList {
private:
    Node* head;
    int listSize;

public:
    SortedLinkedList();
    ~SortedLinkedList();

    void insert(T value);
    bool remove(T value);
    bool search(T value) const;
    void display() const;
    int getSize() const;
};
```

## Key Methods

### Insertion

Maintains sorted order by finding the correct position. It relies on the `<` operator of type `T`.

```cpp
template<typename T>
void SortedLinkedList<T>::insert(T value) {
    Node* newNode = new Node(value);

    if (head == nullptr || value < head->data) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->data < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    listSize++;
}
```

### Search

Linear search through the list. It relies on the `==` operator of type `T`.

```cpp
template<typename T>
bool SortedLinkedList<T>::search(T value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}
```

### Removal

Finds and removes the first occurrence, maintaining the list's links.

```cpp
template<typename T>
bool SortedLinkedList<T>::remove(T value) {
    if (head == nullptr) return false;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        listSize--;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && !(current->next->data == value)) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        listSize--;
        return true;
    }
    return false;
}
```

## Memory Management

The destructor cleans up all nodes to prevent leaks. This is critical in C++!

```cpp
template<typename T>
SortedLinkedList<T>::~SortedLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
```

## Custom Data Types

One of the great powers of templates is using them with custom types. In `main.cpp`, we demonstrate this with a `Person` struct.

To use `Person` in `SortedLinkedList<Person>`, we *must* overload the operators the list relies on:

```cpp
struct Person {
    std::string name;
    int age;
    Person(std::string n, int a) : name(n), age(a) {}
};

// Required for insert()
bool operator<(const Person& p1, const Person& p2) {
    return p1.age < p2.age;
}

// Required for search() and remove()
bool operator==(const Person& p1, const Person& p2) {
    return p1.name == p2.name && p1.age == p2.age;
}

// Helpful for display()
std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.name << " (" << p.age << ")";
    return os;
}
```

## Demonstration

The `main.cpp` shows usage with integers, strings, and custom `Person` objects.

### Integer Example
```cpp
SortedLinkedList<int> intList;
intList.insert(5);
intList.insert(2);
intList.insert(8);
intList.insert(1);
intList.insert(3);
// Output: 1 -> 2 -> 3 -> 5 -> 8
```

### String Example
```cpp
SortedLinkedList<std::string> stringList;
stringList.insert("banana");
stringList.insert("apple");
stringList.insert("cherry");
stringList.insert("date");
// Output: apple -> banana -> cherry -> date
```

### Person Example
```cpp
SortedLinkedList<Person> personList;
personList.insert(Person("John", 30));
personList.insert(Person("Jane", 25));
personList.insert(Person("Doe", 22));
personList.insert(Person("Alice", 28));
// Output: Doe (22) -> Jane (25) -> Alice (28) -> John (30)
```

## Conclusion

This example illustrates:
- Linked list implementation and traversal.
- Sorting logic during insertion.
- The power and requirements of C++ Templates.
- Proper dynamic memory management.
- Operator overloading for custom data types.

Questions? Let's discuss optimizations, like stopping a search early since we know the list is sorted!