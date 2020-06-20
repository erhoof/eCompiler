//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Lexer/WordTable.h"
#include "../../include/Lexer/Word.h"
#include "../../include/Lexer/Tag.h"

WordTable &WordTable::instance() {
    static WordTable wordTable;
    return wordTable;
}

WordTable::WordTable() {
    w_and   = new Word("&&",      Tag::AND);
    w_or    = new Word("||",      Tag::OR);
    w_eq    = new Word("==",      Tag::EQ);
    w_ne    = new Word("!=",      Tag::NE);
    w_le    = new Word("<=",      Tag::LE);
    w_ge    = new Word(">=",      Tag::GE);
    w_minus = new Word("minus",   Tag::MINUS);
    w_true  = new Word("true",    Tag::TRUE);
    w_false = new Word("false",   Tag::FALSE);
    w_temp  = new Word("t",       Tag::TEMP);
}
