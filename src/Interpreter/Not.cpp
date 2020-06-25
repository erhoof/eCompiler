//
// Created by Pavel Bibichenko on 21.06.2020.
//

#include "../../include/Interpreter/Not.h"

Not::Not(Token* token, Expression* x2) : Logical(token, x2, x2) {}

void Not::jumping(int t, int f) {
    expr2()->jumping(f, t);
}

std::string Not::toString() const {
    std::string out =  operand()->toString() + " " + expr2()->toString();

    return out;
}
