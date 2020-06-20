//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Lexer/Word.h"

#include <utility>

const std::string &Word::lexeme() const {
    return m_lexeme;
}

Word::Word(std::string s, int tag) : Token(tag) {
    m_lexeme = std::move(s);
}

std::string Word::toString() const {
    return m_lexeme;
}
