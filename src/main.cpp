#include "AstPrinter.h"
#include "Interpreter.h"
#include "Parser.h"
#include "../include/Reader.h"
#include "../include/Tokenizer.h"

int main() {
    FileReader file_reader("../test/source");
    Tokenizer tokenizer(file_reader.read());
    Parser parser(tokenizer);
    AstPrinter ast_printer(std::make_shared<ConsoleWriter>());
    Interpreter interpreter;
    const auto program_decl = parser.parse_program_decl();
    //program_decl->accept(ast_printer);
    program_decl->accept(interpreter);
    return 0;
}
