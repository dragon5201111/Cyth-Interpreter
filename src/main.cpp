#include <getopt.h>
#include <iostream>
#include "../include/interpreter/Interpreter.h"
#include "../include/ast/Parser.h"
#include "../include/io/Reader.h"
#include "../include/token/Tokenizer.h"
#include "../include/ast/AstPrinter.h"
#include "../include/io/Preproc.h"

int USAGE_WIDTH = 25;
char ESCAPED_ARG_PREFIX = '\\';

void usage();
void print_usage_option(const std::string& option, const std::string& description);
void run_source(const std::string& source, bool print_ast);
void run_prompt();

int main(const int argc, char ** argv) {
    std::vector<std::string> include_dirs;
    bool print_ast = false;
    bool print_preprocessed = false;
    std::string source;

    constexpr option options[] = {
        {"print-ast", 0, nullptr, 'a'},
        {"print-preprocessed", 0, nullptr, 'r'},
        {"help", 0, nullptr, 'h'},
        {nullptr, 0, nullptr, 0},
    };

    int opt;
    opterr = 0; // Avoid printing error for unknown option
    while ((opt = getopt_long(argc, argv, "s:hI:", options, nullptr)) != -1) {
        if (opt == 's') {
            source = std::string(optarg);
        }else if (opt == 'a') {
            print_ast = true;
        }else if (opt == 'r') {
            print_preprocessed = true;
        }else if (opt == 'I'){
            include_dirs.emplace_back(optarg);
        }else if (opt == 'h') {
            usage();
            return EXIT_SUCCESS;
        }
    }

    int64_t program_exit_status = EXIT_FAILURE;
    if (!source.empty()) {
        const auto console_writer = std::make_shared<ConsoleWriter>();

        Preprocessor preprocessor(include_dirs);
        const std::string preprocessed_source = preprocessor.preprocess(source);
        if (print_preprocessed) {
            console_writer->write(preprocessed_source);
            console_writer->write_ln();
        }

        Tokenizer tokenizer(preprocessed_source);
        Parser parser(tokenizer);
        Interpreter interpreter;

        const auto program_decl = parser.parse_program_decl();
        // Push unprocessed args into program
        program_decl->args.emplace_back(argv[0]);
        for (;optind < argc; optind++) {
            std::string arg(argv[optind]);
            if (arg.at(0) == ESCAPED_ARG_PREFIX) {
                arg.erase(arg.begin());
            }
            program_decl->args.emplace_back(arg);
        }

        if (print_ast) {
            AstPrinter ast_printer(console_writer);
            program_decl->accept(ast_printer);
        }

        program_exit_status = program_decl->accept(interpreter);
    }

    return static_cast<int>(program_exit_status);
}

void usage() {
    std::cout << "Usage: Cyth [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    print_usage_option("-s", "Specify source script to execute.");
    print_usage_option("-I", "Specify a directory to search for files specified by the include directive.");
    print_usage_option("--print-ast", "Print the ast of the source script specified by -s to the console.");
    print_usage_option("--print-preprocessed", "Print the source specified by -s after preprocessing occurs to the console.");
    std::cout << "Additional arguments will be ignored unless a parenthesized identifier is specified in the file given by -s (e.g., main (args) {...}).";
}

void print_usage_option(const std::string& option, const std::string& description){
    std::cout.width(USAGE_WIDTH);
    std::cout.setf(std::ios::left);
    std::cout << option;
    std::cout << description << std::endl;
}
