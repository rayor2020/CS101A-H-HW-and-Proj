#include "../include/Library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

/**
 * @brief Constructor for Library class
 * @param name Name of the library
 */
Library::Library(const std::string& name)
    : libraryName(name), booksDataFile("data/books.txt") {
}

/**
 * @brief Initialize library with sample data
 */
void Library::initializeLibrary() {
    std::cout << "Initializing " << libraryName << "..." << std::endl;

    // Try to load data from files first
    bool booksLoaded = loadBooksFromFile();

    // If no data files exist, load sample data
    if (!booksLoaded) {
        std::cout << "No existing data found. Loading sample data..." << std::endl;
        loadSampleData();
    }

    std::cout << "Library initialized successfully!" << std::endl;
    std::cout << "Books: " << books.size() << std::endl;
}

/**
 * @brief Load sample data for demonstration
 */
void Library::loadSampleData() {
    // Add sample books
    books.push_back(Book(5,"978-0-7432-7356-5", "The Da Vinci Code", "Dan Brown", "Mystery", 2003));
    books.push_back(Book(2,"978-0-553-29698-2", "A Brief History of Time", "Stephen Hawking", "Science", 1988));
    books.push_back(Book(0,"978-0-06-112008-4", "To Kill a Mockingbird", "Harper Lee", "Fiction", 1960));
    books.push_back(Book(0,"978-0-452-28423-4", "1984", "George Orwell", "Dystopian", 1949));
    books.push_back(Book(0,"978-0-7432-4722-4", "The Great Gatsby", "F. Scott Fitzgerald", "Classic", 1925));
    books.push_back(Book(4,"978-0-316-76948-0", "The Catcher in the Rye", "J.D. Salinger", "Fiction", 1951));
    books.push_back(Book(4,"978-0-14-028333-4", "Pride and Prejudice", "Jane Austen", "Romance", 1813));
    books.push_back(Book(12,"978-0-7432-7357-2", "Angels and Demons", "Dan Brown", "Mystery", 2000));

    // Set some sample borrowed books
    if (books.size() >= 2) {
        borrowBook("978-0-7432-7356-5", "M001");  // John borrows Da Vinci Code
        borrowBook("978-0-553-29698-2", "M002");  // Emily borrows Brief History of Time
    }
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
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string relatedbookcount;
        std::string isbn, title, author, genre, yearStr, availableStr, borrowedBy, borrowDateStr, dueDateStr;

        if (std::getline(iss, relatedbookcount, '|') &&
            std::getline(iss, isbn, '|') &&
            std::getline(iss, title, '|') &&
            std::getline(iss, author, '|') &&
            std::getline(iss, genre, '|') &&
            std::getline(iss, yearStr, '|') &&
            std::getline(iss, availableStr, '|') &&
            std::getline(iss, borrowedBy, '|') &&
            std::getline(iss, borrowDateStr, '|') &&
            std::getline(iss, dueDateStr)) {

            Book book(std::stoi(relatedbookcount),isbn, title, author, genre, std::stoi(yearStr));

            if (availableStr == "0") {
                book.borrowBook(borrowedBy);
                // Note: In a real implementation, you'd restore the actual dates
            }

            books.push_back(std::move(book));
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

bool Library::addRelatedBook(const std::string& isbn,const int* relatedBooks, std::size_t count) {
    Book* book = findBookByIsbn(isbn);
    if (book == nullptr) {
        std::cout << "Book with ISBN " << isbn << " not found!" << std::endl;
        return false;
    }

    book->setRelatedBook(count, relatedBooks);
    std::cout << "Related books added to " << book->getTitle() << std::endl;
    return true;
}

Book* Library::findBookByIsbn(const std::string& isbn) {
    auto it = std::find_if(books.begin(), books.end(),
        [&isbn](const Book& book) { return book.getIsbn() == isbn; });

    return (it != books.end()) ? &(*it) : nullptr;
}

std::vector<Book*> Library::findBooksByTitle(const std::string& title) {
    std::vector<Book*> result;
    for (auto& book : books) {
        if (book.getTitle().find(title) != std::string::npos) {
            result.push_back(&book);
        }
    }
    return result;
}

std::vector<Book*> Library::findBooksByAuthor(const std::string& author) {
    std::vector<Book*> result;
    for (auto& book : books) {
        if (book.getAuthor().find(author) != std::string::npos) {
            result.push_back(&book);
        }
    }
    return result;
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
        std::cout << std::left << std::setw(5) << book.getBookId()
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

void Library::displayAvailableBooks() const {
    std::cout << "\n=== AVAILABLE BOOKS ===" << std::endl;
    bool hasAvailable = false;

    for (const auto& book : books) {
        if (book.getIsAvailable()) {
            if (!hasAvailable) {
                std::cout << std::left << std::setw(5) << "id"
                          << std::setw(20) << "ISBN"
                          << std::setw(30) << "Title"
                          << std::setw(20) << "Author"
                          << std::setw(15) << "Genre"
                          << std::setw(6) << "Year" << std::endl;
                std::cout << std::string(91, '-') << std::endl;
                hasAvailable = true;
            }

            std::cout << std::left << std::setw(5) << book.getBookId()
                      << std::setw(20) << book.getIsbn()
                      << std::setw(30) << book.getTitle()
                      << std::setw(20) << book.getAuthor()
                      << std::setw(15) << book.getGenre()
                      << std::setw(6) << book.getPublicationYear() << std::endl;
        }
    }

    if (!hasAvailable) {
        std::cout << "No books available for borrowing." << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

void Library::displayBorrowedBooks() const {
    std::cout << "\n=== BORROWED BOOKS ===" << std::endl;
    bool hasBorrowed = false;

    for (const auto& book : books) {
        if (!book.getIsAvailable()) {
            if (!hasBorrowed) {
                std::cout << std::left << std::setw(5) << "id"
                          << std::setw(20) << "ISBN"
                          << std::setw(30) << "Title"
                          << std::setw(15) << "Borrowed By"
                          << std::setw(12) << "Due Date" << std::endl;
                std::cout << std::string(77, '-') << std::endl;
                hasBorrowed = true;
            }

            std::cout << std::left << std::setw(5) << book.getBookId()
                      << std::setw(20) << book.getIsbn()
                      << std::setw(30) << book.getTitle()
                      << std::setw(15) << book.getBorrowedBy()
                      << std::setw(12) << Book::timeToString(book.getDueDate()) << std::endl;
        }
    }

    if (!hasBorrowed) {
        std::cout << "No books currently borrowed." << std::endl;
    }
    std::cout << "======================" << std::endl;
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
        std::cout << "Due date: " << Book::timeToString(book->getDueDate()) << std::endl;
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

    // Check for overdue and calculate fine
    if (book->isOverdue()) {
        int daysOverdue = book->getDaysOverdue();
        double fine = daysOverdue * 1.0; // $1 per day
        std::cout << "Book is overdue by " << daysOverdue << " days." << std::endl;
        std::cout << "Fine of $" << std::fixed << std::setprecision(2) << fine << " added to account." << std::endl;
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

void Library::displayOverdueBooks() const {
    std::cout << "\n=== OVERDUE BOOKS ===" << std::endl;
    bool hasOverdue = false;

    for (const auto& book : books) {
        if (!book.getIsAvailable() && book.isOverdue()) {
            if (!hasOverdue) {
                std::cout << std::left << std::setw(5) << "id"
                          << std::setw(20) << "ISBN"
                          << std::setw(30) << "Title"
                          << std::setw(15) << "Borrowed By"
                          << std::setw(12) << "Due Date"
                          << std::setw(10) << "Days Late" << std::endl;
                std::cout << std::string(87, '-') << std::endl;
                hasOverdue = true;
            }

            std::cout << std::left << std::setw(5) << book.getBookId()
                      << std::setw(20) << book.getIsbn()
                      << std::setw(30) << book.getTitle()
                      << std::setw(15) << book.getBorrowedBy()
                      << std::setw(12) << Book::timeToString(book.getDueDate())
                      << std::setw(10) << book.getDaysOverdue() << std::endl;
        }
    }

    if (!hasOverdue) {
        std::cout << "No overdue books." << std::endl;
    }
    std::cout << "=====================" << std::endl;
}

void Library::calculateFines() {
    std::cout << "\n=== CALCULATING FINES ===" << std::endl;
    int finesCalculated = 0;

    for (const auto& book : books) {
        if (!book.getIsAvailable() && book.isOverdue()) {
            int daysOverdue = book.getDaysOverdue();
            double fine = daysOverdue * 1.0; // $1 per day

            std::cout << "Fine: $" << std::fixed << std::setprecision(2) << fine
                        << " (" << daysOverdue << " days overdue)" << std::endl;
            finesCalculated++;
            
        }
    }

    if (finesCalculated == 0) {
        std::cout << "No fines to calculate." << std::endl;
    } else {
        std::cout << "Total fines calculated: " << finesCalculated << std::endl;
    }
    std::cout << "=========================" << std::endl;
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

// Statistics and reports
void Library::displayLibraryStats() const {
    std::cout << "\n=== LIBRARY STATISTICS ===" << std::endl;
    std::cout << "Library Name: " << libraryName << std::endl;
    std::cout << "Total Books: " << getTotalBooks() << std::endl;
    std::cout << "Available Books: " << getAvailableBooks() << std::endl;
    std::cout << "Borrowed Books: " << getBorrowedBooks() << std::endl;
    // Calculate overdue books
    int overdueCount = 0;
    for (const auto& book : books) {
        if (!book.getIsAvailable() && book.isOverdue()) {
            overdueCount++;
        }
    }
    std::cout << "Overdue Books: " << overdueCount << std::endl;
}



int Library::getTotalBooks() const { return books.size(); }
int Library::getAvailableBooks() const {
    return std::count_if(books.begin(), books.end(),
        [](const Book& book) { return book.getIsAvailable(); });
}
int Library::getBorrowedBooks() const {
    return std::count_if(books.begin(), books.end(),
        [](const Book& book) { return !book.getIsAvailable(); });
}

// Utility functions
std::string Library::getLibraryName() const { return libraryName; }
void Library::setLibraryName(const std::string& name) { this->libraryName = name; }

void Library::displayMenu() const {
    std::cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===" << std::endl;
    std::cout << "1. Display all books" << std::endl;
    std::cout << "2. Display available books" << std::endl;
    std::cout << "3. Display borrowed books" << std::endl;
    std::cout << "4. Search books" << std::endl;
    std::cout << "5. Borrow book" << std::endl;
    std::cout << "6. Return book" << std::endl;
    std::cout << "7. Display related books" << std::endl;
    std::cout << "8. Library statistics" << std::endl;
    std::cout << "9. Librarian menu" << std::endl;
    std::cout << "10. Save data" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "==================================" << std::endl;
}

void Library::displayAdminMenu() const {
    std::cout << "\n=== LIBRARIAN ADMIN MENU ===" << std::endl;
    std::cout << "1. Add new book" << std::endl;
    std::cout << "2. Remove book" << std::endl;
    std::cout << "3. View overdue books" << std::endl;
    std::cout << "4. Calculate fines" << std::endl;
    std::cout << "5. Add related books" << std::endl;
    std::cout << "6. Save all data" << std::endl;
    std::cout << "0. Back to main menu" << std::endl;
    std::cout << "============================" << std::endl;
}
// Data validation
bool Library::isValidIsbn(const std::string& isbn) const {
    // Simple ISBN validation - check if it's not empty and has reasonable length
    return !isbn.empty() && isbn.length() >= 10 && isbn.length() <= 17;
}


