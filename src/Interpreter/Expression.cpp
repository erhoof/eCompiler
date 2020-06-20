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

void Expression::jumping(int to, int from) {
    emitJumps(toString(), to, from);
}

void Expression::emitJumps(std::string test, int to, int from) {
    if (to != 0 && from != 0) {
        emit("if " + test + " goto L" + std::to_string(to));
        emit("goto L" + std::to_string(from));
    } else if (to != 0) {
        emit ("if " + test + " goto L" + std::to_string(to));
    } else if (from != 0) {
        emit("iffalse " + test + " goto L" + std::to_string(from));
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

