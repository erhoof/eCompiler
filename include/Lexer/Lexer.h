//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_LEXER_H
#define ECOMPILER_LEXER_H

#include <unordered_map>
#include "Word.h"

class Lexer {
public:
    Lexer();

    Token* scan();

    static int line();
    char peek() const;
    const std::unordered_map<std::string, Word*> &words() const;

    static int m_line;

private:
    char m_peek = ' ';
    std::unordered_map<std::string, Word*> m_words;

    void reserve(Word& word);
    void readChar();
    bool readChar(char c);
};

#endif //ECOMPILER_LEXER_H
