//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_ENV_H
#define ECOMPILER_ENV_H

#include <unordered_map>
#include "../Lexer/Token.h"
#include "../Interpreter/Id.h"

// TODO: REDO WITH IDS!!!

class Env {
public:
    explicit Env(Env* prev);
    void put(Token* token, Id* id);
    Id* get(Token& token);

protected:
    Env* m_prev;

private:
    std::unordered_map<Token*, Id*> m_table;
};

#endif //ECOMPILER_ENV_H
