//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Expression.h"
#include "../../include/Interpreter/Arithmetic.h"
#include "../../include/Interpreter/Temp.h"
#include "../../include/Interpreter/Logical.h"
#include "../../include/Interpreter/Relation.h"
#include "../../include/Interpreter/Unary.h"
#include "../../include/Interpreter/Access.h"
#include "../../include/Interpreter/And.h"
#include "../../include/Interpreter/Or.h"
#include "../../include/Interpreter/Not.h"
#include "../../include/Interpreter/Constant.h"

#include <iostream>

Expression::Expression(Token* token, Type* type) {
    m_operand = token;
    m_type = type;
}

Expression* Expression::gen() {
    switch(m_objType) {
        case ACCESS:
            return dynamic_cast<Access*>(this)->gen();
        case ARITHMETIC:
            return dynamic_cast<Arithmetic*>(this)->gen();
        case LOGICAL:
            return dynamic_cast<Logical*>(this)->gen();
        case UNARY:
            return dynamic_cast<Unary*>(this)->gen();
        default:
            return this;
    }
}

Expression* Expression::reduce() {
    switch(m_objType) {
        case ARITHMETIC:
            return dynamic_cast<Arithmetic*>(this)->reduce();
        default:
            return this;
    }
}

void Expression::jumping(int t, int f) {
    switch (m_objType) {
        case ACCESS:
            dynamic_cast<Access*>(this)->jumping(t, f);
            break;
        case AND:
            dynamic_cast<And*>(this)->jumping(t, f);
            break;
        case CONSTANT:
            dynamic_cast<Constant*>(this)->jumping(t, f);
            break;
        case NOT:
            dynamic_cast<Not*>(this)->jumping(t, f);
            break;
        case OR:
            dynamic_cast<Or*>(this)->jumping(t, f);
            break;
        case ObjTypes::RELATION:
            dynamic_cast<Relation*>(this)->jumping(0, f);
            break;
        default:
            emitJumps(toString(), t, f);
    }
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
    std::string out;

    switch(m_objType) {
        case ACCESS:
            out = dynamic_cast<Access*>(this)->toString();
            break;
        case ObjTypes::ARITHMETIC:
            out = dynamic_cast<Arithmetic*>(this)->toString();
            break;
        case ObjTypes::TEMP:
            out = dynamic_cast<Temp*>(this)->toString();
            break;
        case ObjTypes::LOGICAL:
            out = dynamic_cast<Logical*>(this)->toString();
            break;
        case ObjTypes::UNARY:
            out = dynamic_cast<Unary*>(this)->toString();
            break;
        case NOT:
            out = dynamic_cast<Not*>(this)->toString();
            break;
        default:
            out = m_operand->toString();
    }

    return out;
}

Type* Expression::type() const {
    return m_type;
}

Token* Expression::operand() const {
    return m_operand;
}

