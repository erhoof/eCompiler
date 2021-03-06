//
// Created by Pavel Bibichenko on 24.06.2020.
//

#include "../../include/Interpreter/Relation.h"
#include "../../include/Core/Extensions.h"
#include "../../include/SymbolTable/Array.h"
#include "../../include/SymbolTable/TypeTable.h"

Relation::Relation(Token* token, Expression* x1, Expression* x2) :
    Logical(token, x1, x2, RELATION) {}

Type* Relation::check(Type* p1, Type* p2) {
    /*if (instanceof<Array>(&p1) || instanceof<Array>(&p2))
        return nullptr;
    else if (p2 == p1)
        return TypeTable::instance().t_bool;
    else
        return nullptr; WTF ??? */

    if (p2 == p1)
        return TypeTable::instance().t_bool;

    return nullptr;
}

void Relation::jumping(int t, int f) {
    auto a = expr1()->reduce();
    auto b = expr2()->reduce();

    std::string test = a->toString() + " " + operand()->toString() + " " + b->toString();

    emitJumps(test, t, f);
}
