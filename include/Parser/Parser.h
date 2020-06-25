//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_PARSER_H
#define ECOMPILER_PARSER_H

#include "../SymbolTable/Env.h"
#include "../Lexer/Lexer.h"
#include "../Interpreter/Constructions/Statement.h"
#include "../Interpreter/Access.h"

class Parser {
public:
    Parser(Lexer* lexer);

    void program();

private:
    Lexer* m_lexer; // Lexer
    Token* m_look; // Preview

    Env* m_top = nullptr; // Current Symbol Table

    int m_used = 0; // Memory Consumption

    void move();
    void error(std::string out);
    void match(int tag);

    // Parser

    // Basic
    Statement* block(); // block -> {decls stmts}
    void declarations(); // D -> type ID
    Type* type(); // look.tag == Tag.BASIC check
    Type* dimensionals(Type* t); // [ ... ]

    // Statements
    Statement* statements();
    Statement* statement();
    Statement* assign();

    // Expressions
    Expression* boolean();
    Expression* join();
    Expression* equality();
    Expression* relation();
    Expression* expression();
    Expression* term();
    Expression* unary();
    Expression* factor();

    // Arrays
    Access* offset(Id* a);


};

#endif //ECOMPILER_PARSER_H
