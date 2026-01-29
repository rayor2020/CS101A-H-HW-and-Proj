#ifndef LIBRARY_H
#define LIBRARY_H

#include <memory>
#include <string>
#include <vector>
#include "Book.h"

class User;

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
    std::vector<User*> users;
    std::string booksDataFile;
    std::string usersDataFile;
    friend class Admin;

   public:
    // Constructor and Destructor
    Library(const std::string& name = "City Library");
    ~Library();

    // Initialization and running
    void loadSampleData();
    void run();

    // File I/O operations
    bool loadBooksFromFile(const std::string& filename = "data/books.txt");
    bool saveBooksToFile(const std::string& filename = "data/books.txt");
    bool loadUsersFromFile(const std::string& filename = "data/users.txt");
    bool saveUsersToFile(const std::string& filename = "data/users.txt");

    // Book management
    bool addBook(const Book& book);
    bool removeBook(const std::string& isbn);
    Book* findBookByIsbn(const std::string& isbn);
    std::vector<const Book*> findBorrowedBooks(const std::string& userId) const;
    void displayAllBooks() const;
    void displayBorrowedBooks(const std::string& userId) const;

    // Member management
    User* findUserById(const std::string& userId) const;
    bool registerMember(const std::string& userId);

   public:
    // Borrow/Return operations
    bool borrowBook(const std::string& isbn, const std::string& memberId);
    bool returnBook(const std::string& isbn, const std::string& memberId);

    // Search and filter operations
    std::vector<Book*> searchBooks(const std::string& query) const;

    // Utility functions
    std::string getLibraryName() const;
    void setLibraryName(const std::string& name);

    // Data validation
    bool isValidIsbn(const std::string& isbn) const;
};

#endif  // LIBRARY_H