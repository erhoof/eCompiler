//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_NUM_H
#define ECOMPILER_NUM_H

#include "Token.h"

class Num : public Token {
public:
    explicit Num(int value);

    std::string toString() const;
    int value() int;

private:
    int m_value;
};

#endif //ECOMPILER_NUM_H
