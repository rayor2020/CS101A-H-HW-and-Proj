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

#include <iostream>
#include <string>
#include "../include/Library.h"
#include "../include/Utils.h"

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
    library.run();

    return 0;
}
