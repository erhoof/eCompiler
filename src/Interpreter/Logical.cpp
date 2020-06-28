//
// Created by Pavel Bibichenko on 21.06.2020.
//

#include "../../include/Interpreter/Logical.h"
#include "../../include/SymbolTable/TypeTable.h"
#include "../../include/Interpreter/Temp.h"
#include "../../include/Interpreter/Relation.h"
#include "../../include/IO/Logger.h"

Logical::Logical(Token* token, Expression* x1, Expression* x2, ObjTypes lt)
    : Expression(token, TypeTable::instance().t_bool) {

    m_expr1 = x1;
    m_expr2 = x2;
    m_objType = lt;

    // Realtion
    switch(m_objType) {
        case RELATION:
            m_type = dynamic_cast<Relation*>(this)->check(expr1()->type(), expr2()->type());
            break;
        default:
            m_type = check(expr1()->type(), expr2()->type());
    }

    if (m_type == nullptr)
        error("type definition error (logical)");
}

Type* Logical::check(Type* p1, Type* p2) const {
    if (p1 == TypeTable::instance().t_bool &&
        p2 == TypeTable::instance().t_bool)
        return TypeTable::instance().t_bool;
    else
        return nullptr;
}

Expression* Logical::gen() {
    int f = newLabel();
    int a = newLabel();

    auto temp = new Temp(m_type);
    temp->m_objType = ObjTypes::TEMP;
    this->jumping(0, f);

    emit(temp->toString() + " = true"); // this
    aemit("mov eax, [" + temp->toString() + "]"); // to
    Logger::instance().alog("or eax, 0x01"); // this
    aemit("mov [" + temp->toString() + "], eax"); // <<

    emit("goto L" + std::to_string(a));
    aemit("jmp L" + std::to_string(a));
    emitLabel(f);

    emit(temp->toString() + " = false");
    aemit("mov eax, [" + temp->toString() + "]"); // to
    Logger::instance().alog("and eax, 0xFFFFFFFE");
    aemit("mov [" + temp->toString() + "], eax"); // <<
    emitLabel(a);

    return temp;
}

std::string Logical::toString() const {
    std::string out = expr1()->toString() + " " + operand()->toString() + " " + expr2()->toString();

    return out;
}

Expression* Logical::expr1() const {
    return m_expr1;
}

Expression* Logical::expr2() const {
    return m_expr2;
}
