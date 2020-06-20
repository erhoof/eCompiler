//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Lexer/Lexer.h"
#include "../../include/Lexer/Tag.h"
#include "../../include/Lexer/WordTable.h"
#include "../../include/IO/Logger.h"
#include "../../include/Core/Core.h"
#include "../../include/Lexer/Num.h"
#include "../../include/Lexer/Real.h"
#include "../../include/SymbolTable/TypeTable.h"

Lexer::Lexer() {
    Logger::instance().log("Lexer", "initializing lexer...");
    // Keywords
    reserve(*(new Word("if",      Tag::IF)));
    reserve(*(new Word("else",    Tag::ELSE)));
    reserve(*(new Word("while",   Tag::WHILE)));
    reserve(*(new Word("do",      Tag::DO)));
    reserve(*(new Word("break",   Tag::BREAK)));

    // Bools
    reserve(*WordTable::instance().w_true);
    reserve(*WordTable::instance().w_false);

    // Types
    reserve(*TypeTable::instance().t_int);
    reserve(*TypeTable::instance().t_float);
    reserve(*TypeTable::instance().t_bool);
    reserve(*TypeTable::instance().t_char);
}

int Lexer::line() const {
    return m_line;
}

char Lexer::peek() const {
    return m_peek;
}

const std::unordered_map<std::string, Word*> &Lexer::words() const {
    return m_words;
}

void Lexer::reserve(Word& word) {
    m_words.insert(std::pair<std::string, Word*>(word.lexeme(), &word));
    Logger::instance().log("Lexer", "reserving word - " + word.lexeme());
}

void Lexer::readChar() {
    m_peek = Core::instance().nextChar();
}

bool Lexer::readChar(char c) {
    readChar();

    if (m_peek != c)
        return false;

    m_peek = ' ';
    return true;
}

Token* Lexer::scan() {
    for ( ;; readChar()) {
        if (m_peek == ' ' || m_peek == '\t')
            continue;
        else if (m_peek == '\n')
            m_line++;
        else
            break;
    }

    switch (m_peek) {
        case '&':
            if (readChar('&'))
                return WordTable::instance().w_and;
            else
                return (new Token('&'));
        case '|':
            if (readChar('|'))
                return WordTable::instance().w_or;
            else
                return (new Token('|'));
        case '=':
            if (readChar('='))
                return WordTable::instance().w_eq;
            else
                return (new Token('='));
        case '!':
            if (readChar('='))
                return WordTable::instance().w_ne;
            else
                return (new Token('!'));
        case '<':
            if (readChar('='))
                return WordTable::instance().w_le;
            else
                return (new Token('<'));
        case '>':
            if (readChar('='))
                return WordTable::instance().w_ge;
            else
                return (new Token('>'));
    }

    if (isdigit(m_peek)) {
        int v = 0;

        do {
            v = 10*v + (m_peek - '0');
            readChar();
        } while (isdigit(m_peek));

        if (m_peek != '.')
            return new Num(v);

        float x = v;
        float d = 10;

        for (;;) {
            readChar();

            if (!isdigit(m_peek))
                break;

            x = x + (float)(m_peek - '0')/d;
            d *= 10;
        }

        return new Real(x);
    }

    if (isalpha(m_peek)) {
        std::string out;
        do {
            out += m_peek;
            readChar();
        } while(isdigit(m_peek) || isalpha(m_peek));

        auto search = m_words.find(out);
        if (search != m_words.end())
            return search->second;

        auto word = new Word(out, Tag::ID);
        m_words.insert(std::pair<std::string, Word*>(out, word));

        return word;
    }

    auto token = new Token(m_peek);
    m_peek = ' ';

    return token;
}
