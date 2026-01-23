#include <iostream>

#include "../include/Reader.h"
#include "../include/Tokenizer.h"

int main() {
    FileReader file_reader("../test/source");
    Tokenizer tokenizer(file_reader.read());
    for (const auto& token: tokenizer.collect()) {
        std::cout << token << std::endl;
    }
    return 0;
}
