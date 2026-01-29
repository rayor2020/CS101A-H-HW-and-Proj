#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

/**
 * @brief Represents a book in the library system
 *
 * This class encapsulates all book-related information and operations
 * including borrowing status, due dates, and book details.
 */
class Book {
   private:
    std::string isbn;
    std::string title;
    std::string author;
    std::string genre;
    int publicationYear;
    bool isAvailable;
    std::string borrowedBy;  // Member ID who borrowed the book

   public:
    // Constructors
    Book(const std::string& isbn, const std::string& title, const std::string& author, const std::string& genre, int year);

    // Getters
    std::string getIsbn() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getGenre() const;
    int getPublicationYear() const;
    bool getIsAvailable() const;
    std::string getBorrowedBy() const;

    // Setters
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setGenre(const std::string& genre);
    void setPublicationYear(int year);

    // Book operations
    bool borrowBook(const std::string& memberId);
    bool returnBook();

    // Display and utility functions
    void displayInfo() const;
    std::string toString() const;
    bool operator==(const Book& other) const;
};

#endif  // BOOK_H