#include "Interpreter.h"
#include "Parser.h"
#include "../include/Reader.h"
#include "../include/Tokenizer.h"
#include <getopt.h>

#include "AstPrinter.h"

int main(int argc, char ** argv) {
    bool print_ast = false;
    std::string source;

    constexpr option options[] = {
        {"print-ast", 0, nullptr, 'a'}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "s:", options, nullptr)) != -1) {
        if (opt == 's') {
            source = std::string(optarg);
        }else if (opt == 'a') {
            print_ast = true;
        }
    }

    if (source.empty()) {
        throw std::runtime_error("Source is empty.");
    }

    FileReader file_reader(source);
    Tokenizer tokenizer(file_reader.read());
    Parser parser(tokenizer);
    Interpreter interpreter;

    const auto program_decl = parser.parse_program_decl();
    if (print_ast) {
        AstPrinter ast_printer(std::make_shared<ConsoleWriter>());
        program_decl->accept(ast_printer);
    }

    program_decl->accept(interpreter);
    return 0;
}
