//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Operand.h"
#include "../../include/Interpreter/Temp.h"

Operand::Operand(Token* token, Type* type) : Expression(token, type) {}

Expression* Operand::reduce() {
    auto x = gen();
    auto t = new Temp(type());
    t->m_objType = TEMP;
    emit(t->toString() + " = " + x->toString());
    return t;
}
