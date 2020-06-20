//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_WORDTABLE_H
#define ECOMPILER_WORDTABLE_H

#include "Word.h"

class WordTable {
public:
    static WordTable& instance();

    WordTable(const WordTable&) = delete;
    WordTable& operator=(const WordTable&) = delete;

    // Word Table
    Word* w_and;
    Word* w_or;
    Word* w_eq;
    Word* w_ne;
    Word* w_le;
    Word* w_ge;
    Word* w_minus;
    Word* w_true;
    Word* w_false;
    Word* w_temp;
private:
    WordTable();
};

#endif //ECOMPILER_WORDTABLE_H
