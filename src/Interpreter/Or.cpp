//
// Created by Pavel Bibichenko on 21.06.2020.
//

#include "../../include/Interpreter/Or.h"

Or::Or(Token& token, Expression* x1, Expression* x2) : Logical(token, x1, x2) {}

void Or::jumping(int t, int f) {
    int label = t != 0 ? t : newLabel();

    expr1()->jumping(label, 0);
    expr2()->jumping(t, f);

    if (t == 0)
        emitLabel(label);
}
