//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_EXPRESSION_H
#define ECOMPILER_EXPRESSION_H

#include "Node.h"
#include "../Lexer/Token.h"
#include "../SymbolTable/Type.h"

class Expression : public Node {
public:
    Expression(Token& token, Type& type);

    Expression* gen();
    Expression* reduce();
    void jumping(int to, int from);
    void emitJumps(std::string test, int to, int from);

    Type& type() const;
    Token& operand() const;

    std::string toString();

private:
    Type* m_type;
    Token* m_operand;
};

#endif //ECOMPILER_EXPRESSION_H
