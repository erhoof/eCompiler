//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Arithmetic.h"
#include "../../include/SymbolTable/TypeTable.h"

Arithmetic::Arithmetic(Token* token, Expression* x1, Expression* x2) :
    Operand(token, TypeTable::instance().t_bool) {

    m_expr1 = x1;
    m_expr2 = x2;

    m_type = Type::max(expr1()->type(), expr2()->type());

    if (m_type == nullptr)
        error("type definition error (ar)");
}

Expression* Arithmetic::gen() {
    Expression* expr = new Arithmetic(operand(), m_expr1->reduce(), m_expr2->reduce());
    expr->m_objType = ARITHMETIC;

    return expr;
}

std::string Arithmetic::toString() const {
    std::string out = expr1()->toString() + " " + operand()->toString() + " " + expr2()->toString();

    return out;
}

Expression* Arithmetic::expr1() const {
    return m_expr1;
}

Expression* Arithmetic::expr2() const {
    return m_expr2;
}
