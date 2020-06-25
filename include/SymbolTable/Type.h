//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_TYPE_H
#define ECOMPILER_TYPE_H

#include "../Lexer/Word.h"

class Type : public Word {
public:
    Type(std::string str, int tag, int width);

    int width() const;

    static bool numeric(Type* p);
    static Type* max(Type* p1, Type* p2);

    bool operator==(const Type& cmp) const;

private:
    int m_width = 0;
};

#endif //ECOMPILER_TYPE_H
