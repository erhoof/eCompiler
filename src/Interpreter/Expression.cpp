//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Expression.h"

Expression::Expression(Token& token, Type& type) {
    m_operand = &token;
    m_type = &type;
}

Expression* Expression::gen() {
    return this;
}

Expression* Expression::reduce() {
    return this;
}

void Expression::jumping(int t, int f) {
    emitJumps(toString(), t, f);
}

void Expression::emitJumps(std::string test, int t, int f) {
    if (t != 0 && f != 0) {
        emit("if " + test + " goto L" + std::to_string(t));
        emit("goto L" + std::to_string(f));
    } else if (t != 0) {
        emit ("if " + test + " goto L" + std::to_string(t));
    } else if (f != 0) {
        emit("iffalse " + test + " goto L" + std::to_string(f));
    }
}

std::string Expression::toString() {
    return m_operand->toString();
}

Type& Expression::type() const {
    return *m_type;
}

Token& Expression::operand() const {
    return *m_operand;
}

