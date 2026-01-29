#include "../include/Library.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "User.cpp"

/**
 * @brief Constructor for Library class
 * @param name Name of the library
 */
Library::Library(const std::string& name)
    : libraryName(name), booksDataFile("data/books.txt"), usersDataFile("data/users.txt") {
    std::cout << "Initializing " << libraryName << "..." << std::endl;

    // Try to load data from files first
    bool usersLoaded = loadUsersFromFile();
    bool booksLoaded = loadBooksFromFile();

    // If no data files exist, load sample data
    if (!booksLoaded || !usersLoaded) {
        std::cout << "No existing data found. Loading sample data..." << std::endl;
        loadSampleData();
    }

    std::cout << "Library initialized successfully!" << std::endl;
    std::cout << "Books: " << books.size() << std::endl;
    std::cout << "Users: " << users.size() << std::endl;
    pauseScreen();
}

Library::~Library() {
    std::cout << "Thank you for using Library Management System!" << std::endl;
    std::cout << "Saving data before exit..." << std::endl;
    saveBooksToFile();
    saveUsersToFile();
    // Clean up dynamically allocated users
    for (auto user : users) {
        delete user;
    }
}

void Library::run() {
    int choice;
    bool running = true;
    while (running) {
        clearScreen();
        std::cout << "\n=== Library MENU ===" << std::endl;
        std::cout << "1. Login with userID" << std::endl;
        std::cout << "2. Register as a Member" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "==================================" << std::endl;

        choice = getIntInput("Enter your choice: ");
        switch (choice) {
            case 1: {
                User* user = findUserById(getStringInput("Enter userID: "));
                if (user == nullptr) {
                    std::cout << "User not exist!";
                } else {
                    user->menu(*this);
                }
                pauseScreen();
                break;
            }
            case 2:
                registerMember(getStringInput("Enter userID: "));
                pauseScreen();
                break;

            case 0:
                running = false;
                break;

            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                pauseScreen();
                break;
        }
    }
}

/**
 * @brief Load sample data for demonstration
 */
void Library::loadSampleData() {
    // Add sample books
    books.push_back(Book("978-0-7432-7356-5", "The Da Vinci Code", "Dan Brown", "Mystery", 2003));
    books.push_back(Book("978-0-553-29698-2", "A Brief History of Time", "Stephen Hawking", "Science", 1988));
    books.push_back(Book("978-0-06-112008-4", "To Kill a Mockingbird", "Harper Lee", "Fiction", 1960));
    books.push_back(Book("978-0-452-28423-4", "1984", "George Orwell", "Dystopian", 1949));
    books.push_back(Book("978-0-7432-4722-4", "The Great Gatsby", "F. Scott Fitzgerald", "Classic", 1925));
    books.push_back(Book("978-0-316-76948-0", "The Catcher in the Rye", "J.D. Salinger", "Fiction", 1951));
    books.push_back(Book("978-0-14-028333-4", "Pride and Prejudice", "Jane Austen", "Romance", 1813));
    books.push_back(Book("978-0-7432-7357-2", "Angels and Demons", "Dan Brown", "Mystery", 2000));

    Member* m1 = new Member("M001");
    Member* m2 = new Member("M002");
    Member* m3 = new Member("M003");
    VIPMember* v1 = new VIPMember("M004");
    VIPMember* v2 = new VIPMember("M005");
    Admin* a1 = new Admin("L001");
    Admin* a2 = new Admin("L002");

    users = {m1, m2, m3, v1, v2, a1, a2};

    m1->borrowBook(*this, "978-0-7432-7356-5");  // M001 borrows Da Vinci Code
    m2->borrowBook(*this, "978-0-06-112008-4");  // M002 borrows To Kill a Mockingbird
    v1->borrowBook(*this, "978-0-7432-7357-2");  // M004 borrows Angels and Demons
}

/**
 * @brief Load books from file
 * @param filename File to load books from
 * @return True if successful
 */
bool Library::loadBooksFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open books file: " << filename << std::endl;
        return false;
    }

    books.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::istringstream iss(line);
        std::string isbn, title, author, genre, yearStr, availableStr, borrowedBy;

        if (std::getline(iss, isbn, '|') &&
            std::getline(iss, title, '|') &&
            std::getline(iss, author, '|') &&
            std::getline(iss, genre, '|') &&
            std::getline(iss, yearStr, '|') &&
            std::getline(iss, availableStr, '|') &&
            std::getline(iss, borrowedBy, '|')) {
            books.push_back({isbn, title, author, genre, std::stoi(yearStr)});
            if (availableStr == "0") {
                static_cast<Member*>(findUserById(borrowedBy))->borrowBook(*this, isbn);
            }
        }
    }

    file.close();
    std::cout << "Loaded " << books.size() << " books from " << filename << std::endl;
    return true;
}

/**
 * @brief Save books to file
 * @param filename File to save books to
 * @return True if successful
 */
bool Library::saveBooksToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open books file for writing: " << filename << std::endl;
        return false;
    }

    for (const auto& book : books) {
        file << book.toString() << std::endl;
    }

    file.close();
    std::cout << "Saved " << books.size() << " books to " << filename << std::endl;
    return true;
}

/**
 * @brief Load users from file
 * @param filename File to load users from
 * @return True if successful
 */
bool Library::loadUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open users file: " << filename << std::endl;
        return false;
    }

    users.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::istringstream iss(line);
        std::string id, type;

        if (std::getline(iss, id, '|') &&
            std::getline(iss, type, '|')) {
            if (type == "0")
                users.push_back(new Member(id));
            else if (type == "1")
                users.push_back(new VIPMember(id));
            else if (type == "2")
                users.push_back(new Admin(id));
        }
    }

    file.close();
    std::cout << "Loaded " << users.size() << " users from " << filename << std::endl;
    return true;
}

/**
 * @brief Save users to file
 * @param filename File to save users to
 * @return True if successful
 */
bool Library::saveUsersToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open users file for writing: " << filename << std::endl;
        return false;
    }

    for (const auto& user : users) {
        file << user->getUserId() << "|" << user->type() << "|" << std::endl;
    }

    file.close();
    std::cout << "Saved " << users.size() << " users to " << filename << std::endl;
    return true;
}

// Book management methods
bool Library::addBook(const Book& book) {
    // Check if book with same ISBN already exists
    if (findBookByIsbn(book.getIsbn()) != nullptr) {
        std::cout << "Book with ISBN " << book.getIsbn() << " already exists!" << std::endl;
        return false;
    }

    books.push_back(book);
    std::cout << "Book added successfully: " << book.getTitle() << std::endl;
    return true;
}

bool Library::removeBook(const std::string& isbn) {
    auto it = std::find_if(books.begin(), books.end(),
                           [&isbn](const Book& book) { return book.getIsbn() == isbn; });

    if (it != books.end()) {
        if (!it->getIsAvailable()) {
            std::cout << "Cannot remove book - it is currently borrowed!" << std::endl;
            return false;
        }

        std::cout << "Removing book: " << it->getTitle() << std::endl;
        books.erase(it);
        return true;
    }

    std::cout << "Book with ISBN " << isbn << " not found!" << std::endl;
    return false;
}

Book* Library::findBookByIsbn(const std::string& isbn) {
    auto it = std::find_if(books.begin(), books.end(),
                           [&isbn](const Book& book) { return book.getIsbn() == isbn; });

    return (it != books.end()) ? &(*it) : nullptr;
}

std::vector<const Book*> Library::findBorrowedBooks(const std::string& userId) const {
    std::vector<const Book*> borrowedBooks;
    for (const auto& book : books) {
        if (book.getBorrowedBy() == userId) {
            borrowedBooks.push_back(&book);
        }
    }
    return borrowedBooks;
}

void Library::displayAllBooks() const {
    std::cout << "\n=== ALL BOOKS ===" << std::endl;
    if (books.empty()) {
        std::cout << "No books in the library." << std::endl;
        return;
    }

    std::cout << std::left << std::setw(5) << "id"
              << std::setw(20) << "ISBN"
              << std::setw(30) << "Title"
              << std::setw(20) << "Author"
              << std::setw(15) << "Genre"
              << std::setw(6) << "Year"
              << std::setw(10) << "Status" << std::endl;
    std::cout << std::string(101, '-') << std::endl;

    for (const auto& book : books) {
        std::cout << std::left
                  << std::setw(20) << book.getIsbn()
                  << std::setw(30) << book.getTitle()
                  << std::setw(20) << book.getAuthor()
                  << std::setw(15) << book.getGenre()
                  << std::setw(6) << book.getPublicationYear()
                  << std::setw(10) << (book.getIsAvailable() ? "Available" : "Borrowed")
                  << std::endl;
    }
    std::cout << "=================" << std::endl;
}

void Library::displayBorrowedBooks(const std::string& userId) const {
    std::cout << "\n=== DISPLAY BORROWED BOOKS ===" << std::endl;
    auto borrowedBooks = findBorrowedBooks(userId);
    if (borrowedBooks.empty()) {
        std::cout << "No books to display." << std::endl;
        return;
    }
    std::cout << std::left << std::setw(5) << "id"
              << std::setw(20) << "ISBN"
              << std::setw(30) << "Title"
              << std::setw(20) << "Author"
              << std::setw(15) << "Genre"
              << std::setw(6) << "Year"
              << std::setw(10) << "Status" << std::endl;
    std::cout << std::string(101, '-') << std::endl;

    for (const auto& book : borrowedBooks) {
        std::cout << std::left
                  << std::setw(20) << book->getIsbn()
                  << std::setw(30) << book->getTitle()
                  << std::setw(20) << book->getAuthor()
                  << std::setw(15) << book->getGenre()
                  << std::setw(6) << book->getPublicationYear()
                  << std::setw(10) << (book->getIsAvailable() ? "Available" : "Borrowed")
                  << std::endl;
    }
    std::cout << "=================" << std::endl;
}

// Member management methods
User* Library::findUserById(const std::string& userId) const {
    auto it = std::find_if(users.begin(), users.end(),
                           [&userId](User* user) {
                               return user->getUserId() == userId;
                           });
    return (it != users.end()) ? *it : nullptr;
}

bool Library::registerMember(const std::string& userId) {
    // Check if user with same ID already exists
    if (findUserById(userId) != nullptr) {
        std::cout << "User with ID " << userId << " already exists!" << std::endl;
        return false;
    }
    users.push_back(new Member(userId));
    std::cout << "Member added successfully: " << userId << std::endl;
    return true;
}

// Borrow/Return operations
bool Library::borrowBook(const std::string& isbn, const std::string& memberId) {
    Book* book = findBookByIsbn(isbn);
    if (!book) {
        std::cout << "Book with ISBN " << isbn << " not found!" << std::endl;
        return false;
    }

    if (!book->getIsAvailable()) {
        std::cout << "Book is already borrowed!" << std::endl;
        return false;
    }

    // Perform the borrowing
    if (book->borrowBook(memberId)) {
        std::cout << "Book borrowed successfully!" << std::endl;
        std::cout << "Title: " << book->getTitle() << std::endl;
        std::cout << "Borrowed by: " << memberId << std::endl;
        return true;
    }

    return false;
}

bool Library::returnBook(const std::string& isbn, const std::string& memberId) {
    Book* book = findBookByIsbn(isbn);
    if (!book) {
        std::cout << "Book with ISBN " << isbn << " not found!" << std::endl;
        return false;
    }

    if (book->getIsAvailable()) {
        std::cout << "Book is not currently borrowed!" << std::endl;
        return false;
    }

    if (book->getBorrowedBy() != memberId) {
        std::cout << "Book was not borrowed by this member!" << std::endl;
        return false;
    }

    // Perform the return
    if (book->returnBook()) {
        std::cout << "Book returned successfully!" << std::endl;
        std::cout << "Title: " << book->getTitle() << std::endl;
        std::cout << "Returned by: " << memberId << std::endl;
        return true;
    }

    return false;
}

// Search operations
std::vector<Book*> Library::searchBooks(const std::string& query) const {
    std::vector<Book*> results;
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (auto& book : const_cast<std::vector<Book>&>(books)) {
        std::string title = book.getTitle();
        std::string author = book.getAuthor();
        std::string genre = book.getGenre();

        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        std::transform(author.begin(), author.end(), author.begin(), ::tolower);
        std::transform(genre.begin(), genre.end(), genre.begin(), ::tolower);

        if (title.find(lowerQuery) != std::string::npos ||
            author.find(lowerQuery) != std::string::npos ||
            genre.find(lowerQuery) != std::string::npos ||
            book.getIsbn().find(query) != std::string::npos) {
            results.push_back(&book);
        }
    }

    return results;
}

// Utility functions
std::string Library::getLibraryName() const {
    return libraryName;
}
void Library::setLibraryName(const std::string& name) {
    this->libraryName = name;
}

// Data validation
bool Library::isValidIsbn(const std::string& isbn) const {
    // Simple ISBN validation - check if it's not empty and has reasonable length
    return !isbn.empty() && isbn.length() >= 10 && isbn.length() <= 17;
}
