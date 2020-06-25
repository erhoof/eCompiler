//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_STMT_H
#define ECOMPILER_STMT_H

#include "../Node.h"

class Stmt : public Node {
public:
    Stmt() = default;

    virtual void gen(int b, int a);

    static Stmt* Null;
    static Stmt* Enclosing;

    int after() const;

private:
    int m_after = 0;
};

#endif //ECOMPILER_STMT_H
