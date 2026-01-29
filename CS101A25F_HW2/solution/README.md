# Project 2

## 1. Assignment Goal

The objective of this assignment is to complete the implementation of the `Book` class. The `Book` class is a core component of a library management system, used to represent and manage information for individual books.

You will need to fill in the specific implementations for several key functions within a pre-defined framework in the `Book.cpp` file. The focus of this assignment is to learn  **resource management** when a class contains dynamically allocated resources.

### Use makefile to build the project
```bash
# Build the project
make

# Run the program
make run

# Clean build files
make clean
## 2. Resource Management and the "Rule of Five"
```

Inside the `Book` class, there is a member variable `int* relatedBookId;`. This is a pointer to dynamically allocated memory, used to store a list of related book IDs. When you allocate memory using `new[]`, you must release it at the appropriate time using `delete[]`; otherwise, you will cause a **memory leak**.

```cpp
class Book {
private:
    // ... other member variables
    std::size_t relatedBookCount; // The number of related books
    int* relatedBookId;          // A pointer to a dynamic array storing related book IDs
    // ... other member variables
};
```

Relying on compiler-generated default functions is insufficient for correctly handling such dynamic resources. To solve these issues, you need to manually implement the **"Rule of Five"**, which consists of the following five special member functions:

1.  **Destructor**
2.  **Copy Constructor**
3.  **Copy Assignment Operator**
4.  **Move Constructor**
5.  **Move Assignment Operator**

One of the core tasks of this assignment is to correctly implement these five functions to ensure resource safety.

## 2. Tasks to Complete

You need to open the `Book.cpp` file and complete the implementation of the following 8 functions.

### Task 1: Implement Resource Management Functions ("The Rule of Five")

These five functions work together to ensure that the dynamic memory managed by the `relatedBookId` pointer is correctly created, copied, moved, and destroyed.


#### 1. Copy Constructor `Book::Book(const Book& other)`

*   **Goal**: To create a new `Book` object from an existing `Book` object (`other`). 
*   **Implementation Points**:
    *   First, copy all regular member variables (like `isbn`, `title`, etc.) from the `other` object to the new object.
    *   For the `relatedBookId` pointer, you cannot simply copy the pointer address. You must:
        1.  Check if `other.relatedBookCount` is `0`. If it is, the new object's `relatedBookId` should also be `nullptr`, and `relatedBookCount` should be 0.
        2.  Otherwise, allocate a new block of memory of the same size for the new object.
        3.  Copy the **contents** from the `other.relatedBookId` array into this new block of memory, element by element.

#### 2. Copy Assignment Operator `Book& Book::operator=(const Book& other)`

*   **Goal**: To assign the values of an existing `Book` object (`other`) to another existing `Book` object (`this`).
*   **Implementation Points**:
    1.  **Check for self-assignment**: First, check if `this` and `&other` point to the same object (`if (this == &other)`). If so, return `*this` immediately to prevent self-destruction.
    2.  Allocate new memory for `relatedBookId` and copy the contents from the `other` object. 
    3.  Release old resources.
    4.  Copy other members.
    5.  Return a reference to the current object.

#### 3. Move Constructor `Book::Book(Book&& other) noexcept`

*   **Goal**: To create a new object from a temporary `Book` object (an rvalue, `other`) that is about to be destroyed. This is an optimization that improves efficiency by "stealing" resources rather than copying them.
*   **Implementation Points**:
    1.  **Transfer resource ownership**: Make the new object's (`this`) `relatedBookId` pointer point directly to the memory managed by `other.relatedBookId`. Also, transfer the value of `relatedBookCount`.
    2.  Use `std::move` to transfer members that support moving and copy fundamental types.
    3.  Set `other.relatedBookId` to `nullptr` and `other.relatedBookCount` to 0.

#### 4. Move Assignment Operator `Book& Book::operator=(Book&& other) noexcept`

*   **Goal**: To assign the resources and values of a temporary object (`other`) to an existing object (`this`).
*   **Implementation Points**:
    1.  **Check for self-assignment**.
    2.  Release old resources.
    3.  Transfer resources.
    4.  Set `other.relatedBookId` to `nullptr` and its `relatedBookCount` to 0.
    5.  Return `*this`.

#### 5. Destructor `Book::~Book()`

*   **Goal**: To release the resources owned by a `Book` object when its lifetime ends.
*   **Implementation Points**:
    *   Use `delete[]` to free the dynamic array pointed to by `relatedBookId`.
    *   For safety, it's a good practice to set the `relatedBookId` pointer to `nullptr` after deallocation to prevent dangling pointer issues.

---

### Task 2: Implement Core Business Logic Functions

Complete the implementation of the following functions according to the comments in the `Book.cpp` file.

#### 6. `void Book::setRelatedBook(std::size_t count, const int* relatedBooks)`

*   **Goal**: To set or update the list of related books for a book.
*   **Implementation Points** :
    1.  **Handle edge cases**: As per the comments, if `count` is 0 or `relatedBooks` is `nullptr`, you should clear the current list of related books. This means deallocating the memory pointed to by `relatedBookId`, setting it to `nullptr`, and setting `relatedBookCount` to 0.
    2.  Release old memory.
    3.  **Allocate new memory and copy**:
        *   Allocate a new block of memory that can hold `count` integers using `new int[count]`.
        *   copy the data from the `relatedBooks` array into the newly allocated memory.
    4.  **Update member variables**: Make `relatedBookId` point to the newly allocated memory and update `relatedBookCount` with the value of `count`.

#### 7. `bool Book::borrowBook(const std::string& memberId, int borrowDays)`

*   **Goal**: To handle the logic for borrowing a book.
*   **Implementation Points** (based on comments):
    1.  Check if the book is currently available (`isAvailable`). If it is not available (`isAvailable` is `false`), the operation fails, so return `false` immediately.
    2.  If it is available, update the book's status:
        *   Set `isAvailable` to `false`.
        *   Set `borrowedBy` to the incoming `memberId`.
        *   Get the current time using `std::time(nullptr)` and assign it to `borrowDate`.
        *   Use the provided helper function `addDays(borrowDate, borrowDays)` to calculate the due date and assign it to `dueDate`.
    3.  Finally, return `true` to indicate that the book was successfully borrowed.

#### 8. `bool Book::operator==(const Book& other) const`

*   **Goal**: To determine if two `Book` objects are "equal".
*   **Implementation Points** :
    *   Compare `this->isbn` and `other.isbn` for equality.

