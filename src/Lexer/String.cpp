//
// Created by Pavel Bibichenko on 27.06.2020.
//

#include "../../include/Lexer/String.h"
#include "../../include/Lexer/Tag.h"

String::String(std::string value) : Token(Tag::STRING) {
    m_value = value;
}

std::string String::toString() const {
    return m_value;
}