#include "AstPrinter.h"
#include "Parser.h"
#include "../include/Reader.h"
#include "../include/Tokenizer.h"

int main() {
    FileReader file_reader("../test/source");
    Tokenizer tokenizer(file_reader.read());
    Parser parser(tokenizer);
    AstPrinter ast_printer(std::make_shared<ConsoleWriter>());
    parser.parse_program_decl()->accept(ast_printer);
    return 0;
}
