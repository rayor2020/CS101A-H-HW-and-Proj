/**
 * @file main.cpp
 * @brief Main entry point for the Library Management System
 * @author Library Management System Team
 * @date 2024
 *
 * This file contains the main function and menu system for the
 * Library Management System. It demonstrates OOP principles including
 * inheritance, polymorphism, encapsulation, and composition.
 */

#include "../include/Library.h"
#include "../include/Book.h"
#include <iostream>
#include <string>
#include <limits>
#include <memory>

// Function prototypes
void clearScreen();
void pauseScreen();
int getIntInput(const std::string& prompt);
std::size_t getSizetInput(const std::string& prompt);
std::string getStringInput(const std::string& prompt);
void handleBookSearch(Library& library);
void handleBorrowBook(Library& library);
void handleReturnBook(Library& library);
void handleAddBook(Library& library);
void handleRemoveBook(Library& library);
void handleLibrarianMenu(Library& library);
void handleAddRelatedBook(Library& library);
void displayRelatedBooks(Library& library);

/**
 * @brief Main function - entry point of the program
 * @return 0 on successful execution
 */
int main() {
    // Display welcome message
    std::cout << "========================================" << std::endl;
    std::cout << "   WELCOME TO LIBRARY MANAGEMENT SYSTEM" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Demonstrating C++ OOP Principles:" << std::endl;
    std::cout << "- Inheritance (User -> Member, Librarian)" << std::endl;
    std::cout << "- Polymorphism (Virtual functions)" << std::endl;
    std::cout << "- Encapsulation (Private members, getters/setters)" << std::endl;
    std::cout << "- Composition (Library contains Books and Users)" << std::endl;
    std::cout << "========================================" << std::endl;

    pauseScreen();

    // Initialize library
    Library library("City Central Library");
    library.initializeLibrary();

    pauseScreen();

    int choice;
    bool running = true;

    while (running) {
        clearScreen();
        library.displayMenu();

        choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1:
                library.displayAllBooks();
                pauseScreen();
                break;

            case 2:
                library.displayAvailableBooks();
                pauseScreen();
                break;

            case 3:
                library.displayBorrowedBooks();
                pauseScreen();
                break;

            case 4:
                handleBookSearch(library);
                pauseScreen();
                break;

            case 5:
                handleBorrowBook(library);
                pauseScreen();
                break;

            case 6:
                handleReturnBook(library);
                pauseScreen();
                break;

            case 7:
                displayRelatedBooks(library);
                pauseScreen();
                break;


            case 8:
                library.displayLibraryStats();
                pauseScreen();
                break;

            case 9:
                handleLibrarianMenu(library);
                break;

            case 10:
                std::cout << "Saving data..." << std::endl;
                library.saveBooksToFile();
                std::cout << "Data saved successfully!" << std::endl;
                pauseScreen();
                break;

            case 0:
                std::cout << "Thank you for using Library Management System!" << std::endl;
                std::cout << "Saving data before exit..." << std::endl;
                library.saveBooksToFile();
                running = false;
                break;

            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                pauseScreen();
                break;
        }
    }

    return 0;
}

// Utility function implementations
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << "Invalid input! Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::size_t getSizetInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return static_cast<std::size_t>(value);
        } else {
            std::cout << "Invalid input! Please enter a non-negative number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

// Menu handler implementations
void handleBookSearch(Library& library) {
    std::string query = getStringInput("Enter search term (title, author, genre, or ISBN): ");
    auto results = library.searchBooks(query);

    if (results.empty()) {
        std::cout << "No books found matching '" << query << "'" << std::endl;
        return;
    }

    std::cout << "\n=== SEARCH RESULTS ===" << std::endl;
    std::cout << "Found " << results.size() << " book(s):" << std::endl;

    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << "\n" << (i + 1) << ". ";
        results[i]->displayInfo();
    }
    std::cout << "======================" << std::endl;
}


void handleBorrowBook(Library& library) {
    std::string isbn = getStringInput("Enter book ISBN: ");
    std::string memberId = getStringInput("Enter member ID: ");

    if (library.borrowBook(isbn, memberId)) {
        std::cout << "Book borrowed successfully!" << std::endl;
    } else {
        std::cout << "Failed to borrow book. Please check the details." << std::endl;
    }
}

void handleReturnBook(Library& library) {
    std::string isbn = getStringInput("Enter book ISBN: ");
    std::string memberId = getStringInput("Enter member ID: ");

    if (library.returnBook(isbn, memberId)) {
        std::cout << "Book returned successfully!" << std::endl;
    } else {
        std::cout << "Failed to return book. Please check the details." << std::endl;
    }
}

void handleAddBook(Library& library) {
    int relatedBookCount = getIntInput("Enter number of related books: ");
    std::string isbn = getStringInput("Enter ISBN: ");
    std::string title = getStringInput("Enter title: ");
    std::string author = getStringInput("Enter author: ");
    std::string genre = getStringInput("Enter genre: ");
    int year = getIntInput("Enter publication year: ");

    Book newBook(relatedBookCount,isbn, title, author, genre, year);
    library.addBook(newBook);
}

void handleRemoveBook(Library& library) {
    std::string isbn = getStringInput("Enter ISBN of book to remove: ");
    library.removeBook(isbn);
}

void handleAddRelatedBook(Library& library) {
    std::string isbn = getStringInput("Enter ISBN of book to add related book to: ");
    std::size_t count = getSizetInput("Enter number of related books to add: ");
    int* relatedBooks = nullptr;
    if (count > 0) {
        relatedBooks = new int[count]();
        for (std::size_t i = 0; i < count; ++i) {
            relatedBooks[i] = getIntInput("Enter related book ID :");
        }
    }
    library.addRelatedBook(isbn, relatedBooks, count);
    delete[] relatedBooks;
}

void displayRelatedBooks(Library& library) { 
    std::string query = getStringInput("Enter book ISBN: ");
    auto results = library.searchBooks(query);

    if (results.empty()) {
        std::cout << "No books found matching '" << query << "'" << std::endl;
        return;
    }
    std::cout << "\n=== RELATED BOOKS ===" << std::endl;
    results[0]->displayRelatedBooks();
}

void handleLibrarianMenu(Library& library) {
    int choice;
    bool inAdminMenu = true;

    while (inAdminMenu) {
        clearScreen();
        library.displayAdminMenu();

        choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1:
                handleAddBook(library);
                pauseScreen();
                break;

            case 2:
                handleRemoveBook(library);
                pauseScreen();
                break;

            case 3:
                library.displayOverdueBooks();
                pauseScreen();
                break;

            case 4:
                library.calculateFines();
                pauseScreen();
                break;

            case 5:
                handleAddRelatedBook(library);
                pauseScreen();
                break;

            case 6:
                std::cout << "Saving all data..." << std::endl;
                library.saveBooksToFile();
                std::cout << "Data saved successfully!" << std::endl;
                pauseScreen();
                break;

            case 0:
                inAdminMenu = false;
                break;

            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                pauseScreen();
                break;
        }
    }
}
