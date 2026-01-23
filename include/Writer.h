#pragma once
#include <fstream>
#include <string>

class Writer {
public:
    virtual ~Writer() = default;
    virtual void write(std::string message) = 0;
};

class ConsoleWriter final : public Writer {
public:
    void write(std::string message) override;
};

class FileWriter final : public Writer {
    std::ofstream file;
public:
    explicit FileWriter(const std::string& in_file, const bool append) {
        if (append) {
            file.open(in_file, std::ios::out | std::ios::app);
        }else {
            file.open(in_file, std::ios::out);
        }

        if (!file.is_open()) {
            throw std::runtime_error("File could not be opened or doesn't exist.");
        }
    }

    ~FileWriter() override {
        file.close();
    }

    void write(std::string message) override;
};