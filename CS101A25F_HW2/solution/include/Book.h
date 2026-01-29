#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <ctime>
 
/**
 * @brief Represents a book in the library system
 *
 * This class encapsulates all book-related information and operations
 * including borrowing status, due dates, and book details.
 */
class Book {
private:
    int bookId;
    std::size_t relatedBookCount;
    int* relatedBookId;
    std::string isbn;
    std::string title;
    std::string author;
    std::string genre;
    int publicationYear;
    bool isAvailable;
    std::string borrowedBy;  // Member ID who borrowed the book
    std::time_t borrowDate;
    std::time_t dueDate;
    static int cnt;

public:
    // Constructors
    Book();
    Book(std::size_t relatedbookcount,const std::string& isbn, const std::string& title,
        const std::string& author, const std::string& genre, int year);
    Book(const Book& other);            // Copy constructor
    Book(Book&& other) noexcept;        // Move constructor
     // Assignment operators
    Book& operator=(const Book& other); // Copy assignment
    Book& operator=(Book&& other) noexcept; // Move assignment

    // Destructor
    ~Book();

    // Getters
    int getBookId() const;
    std::string getIsbn() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getGenre() const;
    int getPublicationYear() const;
    bool getIsAvailable() const;
    std::string getBorrowedBy() const;
    std::time_t getBorrowDate() const;
    std::time_t getDueDate() const;

    // Setters
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setGenre(const std::string& genre);
    void setPublicationYear(int year);
    void setRelatedBook(std::size_t count,const int* relatedBooks);

    // Book operations
    bool borrowBook(const std::string& memberId, int borrowDays = 14);
    bool returnBook();
    bool isOverdue() const;
    int getDaysOverdue() const;

    // Display and utility functions
    void displayInfo() const;
    void displayRelatedBooks() const;
    std::string toString() const;
    bool operator==(const Book& other) const;

    // Static utility functions
    static std::string timeToString(std::time_t time);
    static std::time_t addDays(std::time_t date, int days);
};

#endif // BOOK_H