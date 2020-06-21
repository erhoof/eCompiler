//
// Created by Pavel Bibichenko on 21.06.2020.
//

#include "../../include/Interpreter/And.h"

And::And(Token& token, Expression* x1, Expression* x2) : Logical(token, x1, x2) {}

void And::jumping(int t, int f) {
    int label = f != 0 ? f : newLabel();
    expr1()->jumping(0, label);
    expr2()->jumping(t, f);

    if (f == 0)
        emitLabel(label);
}
