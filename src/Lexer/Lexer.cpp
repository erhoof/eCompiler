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
#include "../../include/Lexer/String.h"

int Lexer::m_line = 1;

Lexer::Lexer() {
    Logger::instance().log("Lexer", "initializing lexer...");
    // Keywords
    reserve(*(new Word("if",      Tag::IF)));
    reserve(*(new Word("else",    Tag::ELSE)));
    reserve(*(new Word("while",   Tag::WHILE)));
    reserve(*(new Word("do",      Tag::DO)));
    reserve(*(new Word("break",   Tag::BREAK)));
    reserve(*(new Word("read",    Tag::READ)));
    reserve(*(new Word("write",   Tag::WRITE)));
    reserve(*(new Word("var",     Tag::VAR)));

    // Bools
    reserve(*WordTable::instance().w_true);
    reserve(*WordTable::instance().w_false);

    // Types
    reserve(*TypeTable::instance().t_int);
    reserve(*TypeTable::instance().t_float);
    reserve(*TypeTable::instance().t_bool);
    reserve(*TypeTable::instance().t_char);
}

int Lexer::line(){
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
    //Logger::instance().log("Lexer", "scan func called");

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

    if (m_peek == '"') {
        std::string line;
        readChar();

        while (m_peek != '"') {
            line += Logger::string(m_peek);
            readChar();
        }
        readChar();

        Logger::instance().log("Lexer", "new String - \"" + line + "\"");
        return new String(line);
    }

    if (isdigit(m_peek)) {
        int v = 0;

        do {
            v = 10*v + (m_peek - '0');
            readChar();
        } while (isdigit(m_peek));

        if (m_peek != '.') {
            Logger::instance().log("Lexer", "new Num - " + std::to_string(v));
            return new Num(v);
        }

        float x = v;
        float d = 10;

        for (;;) {
            readChar();

            if (!isdigit(m_peek))
                break;

            x = x + (float)(m_peek - '0')/d;
            d *= 10;
        }

        Logger::instance().log("Lexer", "new Real - " + std::to_string(x));

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

        Logger::instance().log("Lexer", "new Word - " + out);
        return word;
    }

    auto token = new Token(m_peek);
    m_peek = ' ';

    return token;
}
