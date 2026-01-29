#include "../include/Book.h"
#include <algorithm>
#include <iomanip>
#include <sstream>

int Book::cnt = 0;

// Default constructor for Book class
Book::Book()
    : bookId(++cnt)
    , relatedBookCount(0)
    , relatedBookId(nullptr)
    , isbn("")
    , title("")
    , author("")
    , genre("")
    , publicationYear(0)
    , isAvailable(true)
    , borrowedBy("")
    , borrowDate(0)
    , dueDate(0)
{
}
Book::Book(std::size_t relatedbookcount, const std::string& isbn, const std::string& title,
    const std::string& author, const std::string& genre, int year)
    : bookId(++cnt)
    , relatedBookCount(relatedbookcount)
    , relatedBookId(relatedBookCount > 0 ? new int[relatedBookCount]() : nullptr)
    , isbn(isbn)
    , title(title)
    , author(author)
    , genre(genre)
    , publicationYear(year)
    , isAvailable(true)
    , borrowedBy("")
    , borrowDate(0)
    , dueDate(0)
{
}

/**
 * @brief Implement these constructors and destructor for Book class
 * @param isbn Book's ISBN
 * @param title Book's title
 * @param author Book's author
 * @param genre Book's genre
 * @param year Publication year
 * @param bookId Unique book identifier.
 * The variable bookId is the identifiers of all books purchased by the library.
 * For every ISBN, there is a unique corresponding Book ID.
 * If the library acquires a second copy of the same book,
 * it should have a same identifier.
 * @todo Implement the following 5 functions.
 */

// copy constructor
Book::Book(const Book& other)
    : bookId(other.bookId)
    // , relatedBookId(other.relatedBookCount > 0 ? new int[other.relatedBookCount] : nullptr)
    , relatedBookCount(other.relatedBookCount)
    , isbn(other.isbn)
    , title(other.title)
    , author(other.author)
    , genre(other.genre)
    , publicationYear(other.publicationYear)
    , isAvailable(true)
    , borrowedBy("")
    , borrowDate(0)
    , dueDate(0)
{
    if (other.relatedBookCount > 0) {
        relatedBookId = new int[other.relatedBookCount];
        for (std::size_t i = 0; i < other.relatedBookCount; ++i)
            relatedBookId[i] = other.relatedBookId[i];
    }
};

// move constructor
Book::Book(Book&& other) noexcept
    : bookId(other.bookId)
    // , relatedBookId(other.relatedBookId)
    , relatedBookCount(other.relatedBookCount)
    , isbn(other.isbn)
    , title(other.title)
    , author(other.author)
    , genre(other.genre)
    , publicationYear(other.publicationYear)
    , isAvailable(other.isAvailable)
    , borrowedBy(other.borrowedBy)
    , borrowDate(other.borrowDate)
    , dueDate(other.dueDate)
{
    if (other.relatedBookCount > 0)
        relatedBookId = other.relatedBookId;
    other.bookId = 0;
    other.relatedBookId = nullptr;
    other.relatedBookCount = 0;
    other.isbn = "";
    other.title = "";
    other.author = "";
    other.genre = "";
    other.publicationYear = 0;
    other.isAvailable = false;
    other.borrowedBy = "";
    other.borrowDate = 0;
    other.dueDate = 0;
};

// copy assignment operator
Book& Book::operator=(const Book& other)
{
    int* new_relatedBookId = new int[other.relatedBookCount];
    for (std::size_t i = 0; i < other.relatedBookCount; ++i)
        new_relatedBookId[i] = other.relatedBookId[i];
    delete[] relatedBookId;
    relatedBookId = new_relatedBookId;
    bookId = other.bookId;
    relatedBookCount = other.relatedBookCount;
    isbn = other.isbn;
    title = other.title;
    author = other.author;
    genre = other.genre;
    publicationYear = other.publicationYear;
    isAvailable = true;
    borrowedBy = "";
    borrowDate = 0;
    dueDate = 0;
    return *this;
};

// move assignment operator
Book& Book::operator=(Book&& other) noexcept
{
    if (this != &other) {
        delete[] relatedBookId;
        bookId = other.bookId;
        relatedBookId = other.relatedBookId;
        relatedBookCount = other.relatedBookCount;
        isbn = other.isbn;
        title = other.title;
        author = other.author;
        genre = other.genre;
        publicationYear = other.publicationYear;
        isAvailable = other.isAvailable;
        borrowedBy = other.borrowedBy;
        borrowDate = other.borrowDate;
        dueDate = other.dueDate;
        other.bookId = 0;
        other.relatedBookId = nullptr;
        other.relatedBookCount = 0;
        other.isbn = "";
        other.title = "";
        other.author = "";
        other.genre = "";
        other.publicationYear = 0;
        other.isAvailable = false;
        other.borrowedBy = "";
        other.borrowDate = 0;
        other.dueDate = 0;
    }
    return *this;
};
// destructor
Book::~Book() { delete[] relatedBookId; };

// Getters implementation
int Book::getBookId() const { return bookId; }
std::string Book::getIsbn() const { return isbn; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getGenre() const { return genre; }
int Book::getPublicationYear() const { return publicationYear; }
bool Book::getIsAvailable() const { return isAvailable; }
std::string Book::getBorrowedBy() const { return borrowedBy; }
std::time_t Book::getBorrowDate() const { return borrowDate; }
std::time_t Book::getDueDate() const { return dueDate; }

// Setters implementation
void Book::setTitle(const std::string& title) { this->title = title; }
void Book::setAuthor(const std::string& author) { this->author = author; }
void Book::setGenre(const std::string& genre) { this->genre = genre; }
void Book::setPublicationYear(int year) { this->publicationYear = year; }

/**
 * @brief Set related books
 * @param count Number of related books
 * @param relatedBooks Array of related book IDs
 * @note This function should allocate memory for relatedBookId
 * Take care of the condition when relatedBooks is nullptr or count is 0.
 */
void Book::setRelatedBook(std::size_t count, const int* relatedBooks)
{
    delete[] relatedBookId;
    if (relatedBooks != nullptr && count != 0) {
        // relatedBookId = new int[count]{relatedBooks};
        relatedBookId = new int[count];
        for (std::size_t i = 0; i < count; ++i)
            relatedBookId[i] = relatedBooks[i];
    } else {
        relatedBookId = nullptr;
    }
    relatedBookCount = count;
};

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
bool Book::borrowBook(const std::string& memberId, int borrowDays)
{
    if (isAvailable) {
        borrowDate = std::time(nullptr);
        dueDate = addDays(borrowDate, borrowDays);
        isAvailable = false;
        borrowedBy = memberId;
        return true;
    } else
        return false;
};

// Return a borrowed book
// True if book was successfully returned
bool Book::returnBook()
{
    if (isAvailable) {
        return false;
    }

    isAvailable = true;
    borrowedBy = "";
    borrowDate = 0;
    dueDate = 0;
    return true;
}

// Check if book is overdue
bool Book::isOverdue() const
{
    if (isAvailable || dueDate == 0) {
        return false;
    }
    return std::time(nullptr) > dueDate;
}

// Get number of days overdue
// Number of days overdue (0 if not overdue)
int Book::getDaysOverdue() const
{
    if (!isOverdue()) {
        return 0;
    }

    std::time_t now = std::time(nullptr);
    double seconds = std::difftime(now, dueDate);
    return static_cast<int>(seconds / (24 * 60 * 60));
}

// Display book information
void Book::displayInfo() const
{
    std::cout << "Book ID: " << bookId << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Genre: " << genre << std::endl;
    std::cout << "Year: " << publicationYear << std::endl;
    std::cout << "Status: " << (isAvailable ? "Available" : "Borrowed") << std::endl;

    if (!isAvailable) {
        std::cout << "Borrowed by: " << borrowedBy << std::endl;
        std::cout << "Borrow date: " << timeToString(borrowDate) << std::endl;
        std::cout << "Due date: " << timeToString(dueDate) << std::endl;
        if (isOverdue()) {
            std::cout << "OVERDUE by " << getDaysOverdue() << " days!" << std::endl;
        }
    }
}
void Book::displayRelatedBooks() const
{
    if (relatedBookCount > 0) {
        std::cout << "Related Books:" << std::endl;
        for (std::size_t i = 0; i < relatedBookCount; ++i) {
            std::cout << relatedBookId[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No related books." << std::endl;
    }
}

// Convert book to string representation
std::string Book::toString() const
{
    std::ostringstream oss;
    oss << bookId << "|" << relatedBookCount << "|" << isbn << "|" << title << "|" << author << "|" << genre
        << "|" << publicationYear << "|" << (isAvailable ? "1" : "0")
        << "|" << borrowedBy << "|" << borrowDate << "|" << dueDate;
    return oss.str();
}

/**
 * @brief Compare two books for equality
 * @param other Another book to compare with
 * @return True if books have the same ISBN
 */
bool Book::operator==(const Book& other) const { return isbn == other.isbn; };

// Convert time_t to string representation
std::string Book::timeToString(std::time_t time)
{
    if (time == 0) {
        return "N/A";
    }

    std::tm* tm = std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::time_t Book::addDays(std::time_t date, int days)
{
    return date + (days * 24 * 60 * 60);
}