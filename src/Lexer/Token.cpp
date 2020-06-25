//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Lexer/Token.h"
#include "../../include/IO/Logger.h"

Token::Token(int tag) {
    Logger::instance().log("Lexer", "new token: " + Logger::string(tag));

    m_tag = tag;
}

std::string Token::toString() const {
    std::string out(1, (char)m_tag);

    return out;
}

int Token::tag() const {
    return m_tag;
}

