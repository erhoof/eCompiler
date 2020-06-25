//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_BREAK_H
#define ECOMPILER_BREAK_H

#include "Statement.h"

class Break : public Statement {
public:
    Break();

    void gen(int b, int a);

    Statement* stmt();
private:
    Statement* m_stmt;
};

#endif //ECOMPILER_BREAK_H
