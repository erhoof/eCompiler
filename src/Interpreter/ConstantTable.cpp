//
// Created by Pavel Bibichenko on 21.06.2020.
//

#include "../../include/Interpreter/Constant.h"
#include "../../include/Interpreter/ConstantTable.h"
#include "../../include/Lexer/WordTable.h"
#include "../../include/SymbolTable/TypeTable.h"

ConstantTable &ConstantTable::instance() {
    static ConstantTable ConstantTable;
    return ConstantTable;
}

ConstantTable::ConstantTable() {
    c_true = new Constant(*WordTable::instance().w_true, *TypeTable::instance().t_bool);
    c_false = new Constant(*WordTable::instance().w_false, *TypeTable::instance().t_bool);
}