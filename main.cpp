#include <iostream>
#include <string>
#include "SortedLinkedList.h"

/**
 * HELLO!
 * @struct Person
 * @brief A simple struct to demonstrate the sorted list with a user-defined type.
 *
 * Contains a name (string) and an age (int). The list will be sorted based on age.
 */
struct Person {
    std::string name;
    int age;

    /**
     * @brief Constructor for the Person struct.
     * @param n The name of the person.
     * @param a The age of the person.
     */
    Person(std::string n, int a) : name(n), age(a) {}
};

/**
 * @brief Overloads the less-than operator (<) for the Person struct.
 *
 * This is essential for the SortedLinkedList to compare two Person objects
 * and maintain sorted order. The comparison is based on age.
 *
 * @param p1 The first Person object.
 * @param p2 The second Person object.
 * @return True if p1's age is less than p2's age, false otherwise.
 */
bool operator<(const Person& p1, const Person& p2) {
    return p1.age < p2.age;
}

/**
 * @brief Overloads the equality operator (==) for the Person struct.
 *
 * This is used by the `remove` and `search` methods of the SortedLinkedList
 * to find a specific Person object in the list.
 *
 * @param p1 The first Person object.
 * @param p2 The second Person object.
 * @return True if both name and age are the same, false otherwise.
 */
bool operator==(const Person& p1, const Person& p2) {
    return p1.name == p2.name && p1.age == p2.age;
}

/**
 * @brief Overloads the stream insertion operator (<<) for the Person struct.
 *
 * This allows a Person object to be easily printed to an output stream,
 * which is used by the `display` method of the SortedLinkedList.
 *
 * @param os The output stream.
 * @param p The Person object to print.
 * @return The output stream with the person's details.
 */
std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.name << " (" << p.age << ")";
    return os;
}

/**
 * @brief The main function to demonstrate the functionality of the SortedLinkedList.
 *
 * This program showcases the use of the SortedLinkedList with three different data types:
 * 1. `int` - A fundamental data type.
 * 2. `std::string` - A standard library class.
 * 3. `Person` - A user-defined struct.
 *
 * For each type, it demonstrates insertion, display, searching, and removal operations.
 */
int main() {
    std::cout << "Demonstrating Sorted Templated Linked List" << std::endl << std::endl;

    // --- Example with integers ---
    std::cout << "--- Integer List Example ---" << std::endl;
    SortedLinkedList<int> intList;  // Create a list for integers
    intList.insert(5);
    intList.insert(2);
    intList.insert(8);
    intList.insert(1);
    intList.insert(3);  // Values are inserted and the list remains sorted

    std::cout << "Integer list after insertions: ";
    intList.display();  // Expected output: 1 -> 2 -> 3 -> 5 -> 8

    std::cout << "Size: " << intList.getSize() << std::endl;  // Expected output: 5
    std::cout << "Search for 3: " << (intList.search(3) ? "Found" : "Not found") << std::endl;  // Expected: Found
    std::cout << "Search for 4: " << (intList.search(4) ? "Found" : "Not found") << std::endl;  // Expected: Not found

    intList.remove(2);  // Remove the value 2
    std::cout << "After removing 2: ";
    intList.display();  // Expected output: 1 -> 3 -> 5 -> 8
    std::cout << std::endl;
    //some text


    // --- Example with strings ---
    std::cout << "--- String List Example ---" << std::endl;
    SortedLinkedList<std::string> stringList;  // Create a list for strings
    stringList.insert("banana");
    stringList.insert("apple");
    stringList.insert("cherry");
    stringList.insert("date");  // Strings are inserted in alphabetical order

    std::cout << "String list after insertions: ";
    stringList.display();  // Expected output: apple -> banana -> cherry -> date

    stringList.remove("cherry");  // Remove "cherry"
    std::cout << "After removing 'cherry': ";
    stringList.display();  // Expected output: apple -> banana -> date
    std::cout << std::endl;


    // --- Example with Person structs ---
    std::cout << "--- Person List Example ---" << std::endl;
    SortedLinkedList<Person> personList;  // Create a list for Person structs
    personList.insert(Person("John", 30));
    personList.insert(Person("Jane", 25));
    personList.insert(Person("Doe", 22));
    personList.insert(Person("Alice", 28));  // Person objects are sorted by age

    std::cout << "Person list after insertions: ";
    personList.display();  // Expected output: Doe (22) -> Jane (25) -> Alice (28) -> John (30)

    personList.remove(Person("Jane", 25));  // Remove Jane
    std::cout << "After removing Jane: ";
    personList.display();  // Expected output: Doe (22) -> Alice (28) -> John (30)

    return 0;
}
