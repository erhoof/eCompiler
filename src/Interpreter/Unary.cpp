//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Unary.h"
#include "../../include/SymbolTable/TypeTable.h"

Unary::Unary(Token* token, Expression* expr)
    : Operand(token, TypeTable::instance().t_bool) {

    m_type = Type::max(TypeTable::instance().t_int, expr->type());
    if (m_type == nullptr)
        error("type definition error (unary)");

    m_expr = expr;
}

Expression* Unary::gen() {
    Expression* ex = new Unary(operand(), expr()->reduce());
    ex->m_objType = UNARY;
    return ex;
}

std::string Unary::toString() {
    std::string out = operand()->toString() + " " + expr()->toString();

    return out;
}

Expression* Unary::expr() const {
    return m_expr;
}
