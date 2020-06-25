//
// Created by Pavel Bibichenko on 21.06.2020.
//

#include "../../include/Interpreter/Logical.h"
#include "../../include/SymbolTable/TypeTable.h"
#include "../../include/Interpreter/Temp.h"

Logical::Logical(Token* token, Expression* x1, Expression* x2)
    : Expression(token, TypeTable::instance().t_bool) {

    m_type = check(expr1()->type(), expr2()->type());
    if (m_type == nullptr)
        error("type definition error");

    m_expr1 = x1;
    m_expr2 = x2;
}

Type* Logical::check(Type* p1, Type* p2) const {
    if (p1 == TypeTable::instance().t_bool &&
        p2 == TypeTable::instance().t_bool)
        return TypeTable::instance().t_bool;
    else
        return nullptr;
}

Expression* Logical::gen() {
    int f = newLabel();
    int a = newLabel();

    auto temp = new Temp(m_type);
    this->jumping(0, f);

    emit(temp->toString() + " = true");
    emit("goto L" + std::to_string(a));
    emitLabel(f);
    emit(temp->toString() + " = false");
    emitLabel(a);

    return temp;
}

std::string Logical::toString() const {
    std::string out = expr1()->toString() + " " + operand()->toString() + " " + expr2()->toString();

    return out;
}

Expression* Logical::expr1() const {
    return m_expr1;
}

Expression* Logical::expr2() const {
    return m_expr2;
}
