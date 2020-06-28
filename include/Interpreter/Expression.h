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
    Expression(Token* token, Type* type);

    Expression* gen();
    Expression* reduce();
    void jumping(int t, int f);
    void emitJumps(std::string test, int t, int f);
    void emitAsmJumps(Expression* x1, Expression* x2, Token* op, int t, int f);

    Type* type() const;
    Token* operand() const;

    std::string toString();

    enum ObjTypes {
        EXPRESSION,
        ARITHMETIC,
        CONSTANT,
        LOGICAL,
        RELATION,
        ACCESS,
        TEMP,
        NOT,
        AND,
        OR,
        UNARY
    };

    ObjTypes m_objType = EXPRESSION;

    virtual ~Expression() = default;

protected:
    Type* m_type;

private:
    Token* m_operand;
};

#endif //ECOMPILER_EXPRESSION_H
