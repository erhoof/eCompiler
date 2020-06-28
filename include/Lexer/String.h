//
// Created by Pavel Bibichenko on 27.06.2020.
//

#ifndef ECOMPILER_STRING_H
#define ECOMPILER_STRING_H

#include "Token.h"

class String : public Token {
public:
    explicit String(std::string value);

    std::string toString() const;

    std::string m_value;
};

#endif //ECOMPILER_STRING_H
