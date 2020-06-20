//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_REAL_H
#define ECOMPILER_REAL_H

#include "Token.h"

class Real : public Token {
public:
    explicit Real(float value);

    float value() const;

    std::string toString() const;

private:
    float m_value;
};

#endif //ECOMPILER_REAL_H
