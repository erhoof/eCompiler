//
// Created by Pavel Bibichenko on 21.06.2020.
//

#include "../../include/Interpreter/Constant.h"
#include "../../include/Lexer/Num.h"
#include "../../include/SymbolTable/TypeTable.h"
#include "../../include/Interpreter/ConstantTable.h"

Constant::Constant(Token& token, Type& type)
    : Expression(token, type) {}

Constant::Constant(int i)
    : Expression(*(new Num(i)), *TypeTable::instance().t_int) {}

void Constant::jumping(int t, int f) {
    if (this == ConstantTable::instance().c_true && t != 0)
        emit("goto L" + std::to_string(t));
    else if (this == ConstantTable::instance().c_false && f != 0)
        emit("goto L" + std::to_string(f));
}
