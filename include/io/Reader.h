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
        open(in_file);
    }

    explicit FileReader() = default;

    ~FileReader() override {
        if (file.is_open()) {
            file.close();
        }
    }

    void reopen(const std::string& in_file);
    void open(const std::string& in_file);

    std::string rread(const std::string& in_file);
    std::string read() override;
};
