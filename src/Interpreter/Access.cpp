//
// Created by Pavel Bibichenko on 24.06.2020.
//

#include "../../include/Interpreter/Access.h"
#include "../../include/Lexer/Tag.h"

Access::Access(Id* id, Expression* x, Type* type)
    : Operand(new Word("[]", Tag::INDEX), type) {

    m_array = id;
    m_index = x;
}

Id* Access::array() const {
    return m_array;
}

Expression* Access::index() const {
    return m_index;
}

Expression* Access::gen() {
    return new Access(m_array, m_index->reduce(), type());
}

void Access::jumping(int t, int f) {
    emitJumps(reduce()->toString(), t, f);
}

std::string Access::toString() {
    std::string out = array()->toString() + " [ " + m_index->toString() + " ]";

    return out;
}
