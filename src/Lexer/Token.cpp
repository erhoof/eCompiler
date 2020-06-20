//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Lexer/Token.h"

Token::Token(int tag) {
    m_tag = tag;
}

std::string Token::toString() const {
    std::string out(1, (char)m_tag);

    return out;
}

