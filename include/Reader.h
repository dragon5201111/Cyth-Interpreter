#pragma once
#include <fstream>
#include <string>

class Reader {
public:
    virtual ~Reader() = default;
    virtual std::string read() = 0;
};

class FileReader final : public Reader {
    std::ifstream file;
public:
    explicit FileReader(const std::string& in_file) {
        file.open(in_file, std::ios::in);

        if (!file.is_open()) {
            throw std::runtime_error("File could not be opened or doesn't exist.");
        }
    }

    ~FileReader() override {
        file.close();
    }

    std::string read() override;
};
