#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include <vector>
#include <memory>
#include <string>

/**
 * @brief Main library management system class
 *
 * This class manages the entire library system including books, members,
 * and librarians. It provides composition by containing collections of
 * books and users, and handles all library operations.
 */
class Library {
private:
    std::string libraryName;
    std::vector<Book> books;
    std::string booksDataFile;

public:
    // Constructor and Destructor
    Library(const std::string& name = "City Library");
    ~Library() = default;

    // Initialization
    void initializeLibrary();
    void loadSampleData();

    // File I/O operations
    bool loadBooksFromFile(const std::string& filename = "data/books.txt");
    bool saveBooksToFile(const std::string& filename = "data/new_books.txt");

    // Book management
    bool addBook(const Book& book);
    bool removeBook(const std::string& isbn);
    bool addRelatedBook(const std::string& isbn,const int* relatedBooks, std::size_t count);
    Book* findBookByIsbn(const std::string& isbn);
    std::vector<Book*> findBooksByTitle(const std::string& title);
    std::vector<Book*> findBooksByAuthor(const std::string& author);
    void displayAllBooks() const;
    void displayAvailableBooks() const;
    void displayBorrowedBooks() const;

    // Borrow/Return operations
    bool borrowBook(const std::string& isbn, const std::string& memberId);
    bool returnBook(const std::string& isbn, const std::string& memberId);
    void displayOverdueBooks() const;
    void calculateFines();

    // Search and filter operations
    std::vector<Book*> searchBooks(const std::string& query) const;

    // Statistics and reports
    void displayLibraryStats() const;
    int getTotalBooks() const;
    int getAvailableBooks() const;
    int getBorrowedBooks() const;

    // Utility functions
    std::string getLibraryName() const;
    void setLibraryName(const std::string& name);
    void displayMenu() const;
    void displayAdminMenu() const;

    // Data validation
    bool isValidIsbn(const std::string& isbn) const;
};

#endif // LIBRARY_H