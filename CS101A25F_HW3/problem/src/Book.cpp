#include "../include/Book.h"
#include <iomanip>
#include <sstream>

/**
 * @brief Constructor for Book class
 * @param isbn Book's ISBN
 * @param title Book's title
 * @param author Book's author
 * @param genre Book's genre
 * @param year Publication year
 * @param bookId Unique book identifier.
 * The variable bookId is used to record the identifiers of all books purchased by the library.
 * If the library acquires a second copy of the same book, it should have a same identifier.
 */

Book::Book(const std::string& isbn, const std::string& title, const std::string& author, const std::string& genre, int year)
    : isbn(isbn), title(title), author(author), genre(genre), publicationYear(year), isAvailable(true), borrowedBy("") {}

// Getters implementation
std::string Book::getIsbn() const {
    return isbn;
}
std::string Book::getTitle() const {
    return title;
}
std::string Book::getAuthor() const {
    return author;
}
std::string Book::getGenre() const {
    return genre;
}
int Book::getPublicationYear() const {
    return publicationYear;
}
bool Book::getIsAvailable() const {
    return isAvailable;
}
std::string Book::getBorrowedBy() const {
    return borrowedBy;
}

// Setters implementation
void Book::setTitle(const std::string& title) {
    this->title = title;
}
void Book::setAuthor(const std::string& author) {
    this->author = author;
}
void Book::setGenre(const std::string& genre) {
    this->genre = genre;
}
void Book::setPublicationYear(int year) {
    this->publicationYear = year;
}

/**
 * @brief Borrow a book
 * @param memberId ID of the member borrowing the book
 * @param borrowDays Number of days for borrowing (default 14)
 * @return True if book was successfully borrowed
 * @note If book is not available, the book cannot be borrowed.
 * If the book is successfully borrowed,
 * set isAvailable and borrowedBy to correct values,
 * borrowDate = std::time(nullptr),
 * use addDays() to calculate dueDate.
 */
bool Book::borrowBook(const std::string& memberId) {
    if (!isAvailable) {
        return false;
    }
    isAvailable = false;
    borrowedBy = memberId;
    return true;
}

/**
 * @brief Return a borrowed book
 * @return True if book was successfully returned
 */
bool Book::returnBook() {
    if (isAvailable) {
        return false;
    }
    isAvailable = true;
    borrowedBy = "";
    return true;
}

/**
 * @brief Display book information
 */
void Book::displayInfo() const {
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Genre: " << genre << std::endl;
    std::cout << "Year: " << publicationYear << std::endl;
    std::cout << "Status: " << (isAvailable ? "Available" : "Borrowed") << std::endl;
    if (!isAvailable) {
        std::cout << "Borrowed by: " << borrowedBy << std::endl;
    }
}

/**
 * @brief Convert book to string representation
 * @return String containing book details
 */
std::string Book::toString() const {
    std::ostringstream oss;
    oss << isbn << "|" << title << "|" << author << "|" << genre
        << "|" << publicationYear << "|" << (isAvailable ? "1" : "0")
        << "|" << borrowedBy << "|";
    return oss.str();
}

/**
 * @brief Compare two books for equality
 * @param other Another book to compare with
 * @return True if books have the same ISBN
 */
bool Book::operator==(const Book& other) const {
    return isbn == other.isbn;
}
