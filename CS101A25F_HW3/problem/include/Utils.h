#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

// Utility function prototypes
void clearScreen();
void pauseScreen();
int getIntInput(const std::string& prompt);
std::size_t getSizetInput(const std::string& prompt);
std::string getStringInput(const std::string& prompt);

#endif  // UTILS_H