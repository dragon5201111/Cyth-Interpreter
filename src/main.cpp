#include <iostream>

#include "AstPrinter.h"
#include "Parser.h"
#include "../include/Reader.h"
#include "../include/Tokenizer.h"

int main() {
    FileReader file_reader("../test/source");
    Tokenizer tokenizer(file_reader.read());
    Parser parser(tokenizer);
    std::unique_ptr<Expr> expr = parser.parse_expr();
    AstPrinter ast_printer;
    expr->accept(ast_printer);
    return 0;
}
