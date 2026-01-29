#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../include/Library.h"
#include "../include/Utils.h"

// TODO: add access specifiers (public, protected or private) to satisfy the requirements
// TODO: add (= 0, = default or = delete) to satisfy the requirements
// TODO: add (virtual, override) where it's needed
/**
 * @brief Represents a user (Either Member or Admin)
 */
class User {
    std::string userId;

    User(const std::string& id) : userId(id) {}
    User(const User& other);
    User& operator=(const User& other);
    ~User();
    const std::string& getUserId() { return userId; }
    int type();
    void menu(Library& library);
};

/**
 * @brief Represents a Member (Either VIP or not)
 */
class Member : public User {
    unsigned maxBooksAllowed;

    Member(const std::string& id);
    // TODO: implement ctor here. Member can borrow 2 books

    ~Member();

    int type() { return 0; };
    void borrowBook(Library& library, const std::string& isbn) {
        if (/* TODO: fix code here (Hint: use findBorrowedBooks) */) {
            std::cout << "Failed! You are not allowed to borrow more books!";
        } else if (!library.borrowBook(isbn, getUserId())) {
            std::cout << "Failed to borrow book. Please check the details." << std::endl;
        }
    }
    void returnBook(Library& library, const std::string& isbn) {
        if (!library.returnBook(isbn, getUserId())) {
            std::cout << "Failed to return book. Please check the details." << std::endl;
        }
    }
    void menu(Library& library) {
        int choice;
        bool running = true;
        while (running) {
            clearScreen();
            std::cout << "\n=== MEMBER MENU ===" << std::endl;
            std::cout << "1. Display all books" << std::endl;
            std::cout << "2. Display my borrowed books" << std::endl;
            std::cout << "3. Borrow book" << std::endl;
            std::cout << "4. Return book" << std::endl;
            std::cout << "5. Check VIP info" << std::endl;
            std::cout << "0. Exit" << std::endl;
            std::cout << "==================================" << std::endl;

            choice = getIntInput("Enter your choice: ");

            switch (choice) {
                case 1:
                    library.displayAllBooks();
                    pauseScreen();
                    break;

                case 2:
                    library.displayBorrowedBooks(getUserId());
                    pauseScreen();
                    break;

                case 3:
                    borrowBook(library, getStringInput("Enter book ISBN: "));
                    pauseScreen();
                    break;

                case 4:
                    returnBook(library, getStringInput("Enter book ISBN: "));
                    pauseScreen();
                    break;

                case 5:
                    if (/* TODO: fix code here */) {
                        std::cout << "You don't have VIP privileges." << std::endl;
                    } else {
                        std::cout << "You are entitled to VIP privileges." << std::endl;
                    }
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
    };
};

class VIPMember : public Member {
    VIPMember(const std::string& id);
    // TODO: implement ctor here. VIPMember can borrow 5 books

    ~VIPMember();
    int type() { return 1; };
};

class Admin : public User {
    Admin(const std::string& id);
    // TODO: implement ctor here. The permission to create Admin should be strictly restricted.

    ~Admin();
    friend void Library::loadSampleData();
    friend bool Library::loadUsersFromFile(const std::string& filename);

    int type() { return 2; };
    void menu(Library& library) {
        int choice;
        bool running = true;
        while (running) {
            clearScreen();
            std::cout << "\n=== ADMIN MENU ===" << std::endl;
            std::cout << "1. Display all books" << std::endl;
            std::cout << "2. Add book" << std::endl;
            std::cout << "3. Remove book" << std::endl;
            std::cout << "4. Change VIP identity of a Member" << std::endl;
            std::cout << "5. Add a new Admin" << std::endl;
            std::cout << "0. Exit" << std::endl;
            std::cout << "==================================" << std::endl;

            choice = getIntInput("Enter your choice: ");

            switch (choice) {
                case 1:
                    library.displayAllBooks();
                    pauseScreen();
                    break;

                case 2: {
                    std::string isbn = getStringInput("Enter ISBN: ");
                    std::string title = getStringInput("Enter title: ");
                    std::string author = getStringInput("Enter author: ");
                    std::string genre = getStringInput("Enter genre: ");
                    int year = getIntInput("Enter publication year: ");

                    Book newBook(isbn, title, author, genre, year);
                    library.addBook(newBook);
                    pauseScreen();
                    break;
                }

                case 3:
                    library.removeBook(getStringInput("Enter book ISBN: "));
                    pauseScreen();
                    break;

                // TODO: implement the function of Change VIP identity of a Member here.
                case 4: {
                    std::string id = getStringInput("Enter Member's ID: ");
                    /* TODO: fix code here */
                    if (/* TODO: fix code here */) {
                        std::cout << "Member not exist!";
                    } else if (/* TODO: fix code here */) {  // Change Member to VIPMember
                        /* TODO: fix code here */
                        std::cout << "Member " << id << " is now a VIPMember." << std::endl;
                    } else {  // Change VIPMember to Member
                        /* TODO: fix code here */
                        std::cout << "Member " << id << " is no longer VIP now." << std::endl;
                    }
                    /* TODO: fix code here */
                    pauseScreen();
                    break;
                }

                case 5: {
                    std::string userId = getStringInput("Enter new Admin userID: ");
                    if (library.findUserById(userId) != nullptr) {
                        std::cout << "User with ID " << userId << " already exists!" << std::endl;
                    } else {
                        library.users.push_back(new Admin(userId));
                        std::cout << "Admin added successfully: " << userId << std::endl;
                    }
                    pauseScreen();
                    break;
                }

                case 0:
                    running = false;
                    break;

                default:
                    std::cout << "Invalid choice! Please try again." << std::endl;
                    pauseScreen();
                    break;
            }
        }
    };
};
