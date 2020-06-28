//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../../include/Interpreter/Constructions/Set.h"
#include "../../../include/SymbolTable/TypeTable.h"
#include "../../../include/IO/Logger.h"

Set::Set(Id* id, Expression* x) {
    m_id = id;
    m_expr = x;

    if (check(id->type(), m_expr->type()) == nullptr)
        error("type definition error (set)");
}

Type* Set::check(Type *t1, Type *t2) {
    if (Type::numeric(t1) && Type::numeric(t2))
        return t2;
    else if (t1 == TypeTable::instance().t_bool &&
             t2 == TypeTable::instance().t_bool)
        return t2;
    else
        return nullptr;
}

void Set::gen(int b, int a) {
    //std::string out = id()->operand()->toString();
    //std::string out = id()->toString() + " = " + expr()->gen()->toString();
    //std::string out = (dynamic_cast<Word*>(id())->operand())->toString() + " = " + expr()->gen()->toString();
    std::string exprString = expr()->gen()->toString();
    std::string out = id()->toString() + " = " + exprString;

    emit(out);

    aExprEmit(id(), exprString);
}

Id* Set::id() {
    return m_id;
}

Expression* Set::expr() {
    return m_expr;
}
