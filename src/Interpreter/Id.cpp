//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Id.h"

Id::Id(Word* id, Type* type, int offset) : Expression(id, type) {
    m_offset = offset;
}

int Id::offset() const {
    return m_offset;
}
