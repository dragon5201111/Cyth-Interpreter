#include <getopt.h>
#include "Interpreter.h"
#include "Parser.h"
#include "../include/Reader.h"
#include "../include/Tokenizer.h"
#include "AstPrinter.h"

void usage();
void print_usage_option(const std::string& option, const std::string& description);
void run_source(const std::string& source, bool print_ast);
void run_prompt();

int main(const int argc, char ** argv) {
    bool print_ast = false;
    std::string source;

    constexpr option options[] = {
        {"print-ast", 0, nullptr, 'a'},
        {"help", 0, nullptr, 'h'},
        {nullptr, 0, nullptr, 0},
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "s:h", options, nullptr)) != -1) {
        if (opt == 's') {
            source = std::string(optarg);
        }else if (opt == 'a') {
            print_ast = true;
        }else if (opt == '?' || opt == 'h') {
            if (opt == '?') std::cout << "Unknown option: "<< argv[optind - 1] <<std::endl;
            usage();
            return EXIT_FAILURE;
        }
    }

    if (!source.empty()) {
        run_source(source, print_ast);
    }else {
        run_prompt();
    }

    return EXIT_SUCCESS;
}

void usage() {
    std::cout << "Usage: Interpreter [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    print_usage_option("-s", "Specify source file to execute.");
    print_usage_option("--print-ast", "Print the ast of the source file to stdout.");
}

void print_usage_option(const std::string& option, const std::string& description){
    std::cout.width(20);
    std::cout.setf(std::ios::left);
    std::cout << option;
    std::cout << description << std::endl;
}

void run_source(const std::string& source, bool print_ast) {
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
}

void run_prompt() {
    std::cout << "TODO: Implement REPL" << std::endl;
}
