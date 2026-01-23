#include "Writer.h"

#include <iostream>

void ConsoleWriter::write(const std::string message) {
    std::cout << message;
}

void FileWriter::write(const std::string message) {
    file << message;
}

