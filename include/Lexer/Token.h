//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_TOKEN_H
#define ECOMPILER_TOKEN_H

#include <string>

class Token {
public:
    explicit Token(int tag);

    std::string toString() const;
    int tag() const;

private:
    int m_tag;
};

#endif //ECOMPILER_TOKEN_H
