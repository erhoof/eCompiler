//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../../include/Interpreter/Constructions/SetElement.h"

SetElement::SetElement(Access* x, Expression* y) {
    m_array = x->array();
    m_index = x->index();
    m_expr = y;

    if (check(&x->type(), &m_expr->type()) == nullptr)
        error("type definiton error");
}

Type* SetElement::check(Type* t1, Type* t2) {
    if (t1 == t2 || (Type::numeric(*t1) && Type::numeric(*t2)))
        return t2;

    return nullptr;
}

void SetElement::gen(int b, int a) {
    std::string s1 = m_index->reduce()->toString();
    std::string s2 = m_expr->reduce()->toString();
    std::string out = array()->toString() + " [ " + s1 + " ] = " + s2;

    emit(out);
}

Id* SetElement::array() {
    return m_array;
}

Expression* SetElement::index() {
    return m_index;
}

Expression* SetElement::expr() {
    return m_expr;
}
