//
// Created by Pavel Bibichenko on 25/06/2020.
//

#ifndef ECOMPILER_STATEMENT_H
#define ECOMPILER_STATEMENT_H

#include "../Node.h"

class Statement : public Node {
public:
    Statement() = default;

    virtual void gen(int b, int a);

    static Statement* Null;
    static Statement* Enclosing;

    int after() const;

private:
    int m_after = 0;
};

#endif //ECOMPILER_STATEMENT_H
