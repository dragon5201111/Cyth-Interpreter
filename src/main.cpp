#include "Interpreter.h"
#include "Parser.h"
#include "../include/Reader.h"
#include "../include/Tokenizer.h"
#include <getopt.h>

int main(int argc, char ** argv) {
    std::string source;

    int opt;
    while ((opt = getopt_long(argc, argv, "s:", nullptr, nullptr)) != -1) {
        if (opt == 's') {
            source = std::string(optarg);
        }
    }

    if (source.empty()) {
        throw std::runtime_error("Source is empty.");
    }

    FileReader file_reader(source);
    Tokenizer tokenizer(file_reader.read());
    Parser parser(tokenizer);
    Interpreter interpreter;
    parser.parse_program_decl()->accept(interpreter);

    return 0;
}
