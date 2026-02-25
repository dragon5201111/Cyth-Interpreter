#include "Reader.h"
#include <sstream>

void FileReader::reopen(const std::string &in_file) {
    if (file.is_open()) {
        file.close();
    }

    open(in_file);
}

void FileReader::open(const std::string &in_file) {
    file.open(in_file, std::ios::in);

    if (!file.is_open()) {
        throw std::runtime_error("File could not be opened or doesn't exist.");
    }
}

std::string FileReader::rread(const std::string &in_file) {
    reopen(in_file);
    std::string read_result = read();
    file.close();
    return read_result;
}

std::string FileReader::read() {
    if (!file.is_open()) {
        throw std::runtime_error("File not opened, cannot read.");
    }

    std::ostringstream string_stream;
    string_stream << file.rdbuf();
    return string_stream.str();
}
