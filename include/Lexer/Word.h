//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_WORD_H
#define ECOMPILER_WORD_H

#include "Token.h"

class Word : public Token {
public:
    Word(std::string s, int tag);
    std::string toString() const;

    const std::string &lexeme() const;
private:
    std::string m_lexeme;
};

#endif //ECOMPILER_WORD_H
