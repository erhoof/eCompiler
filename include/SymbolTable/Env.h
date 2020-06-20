//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_ENV_H
#define ECOMPILER_ENV_H

#include <unordered_map>
#include "../Lexer/Token.h"

// TODO: REDO WITH IDS!!!

class Env {
    explicit Env(Env* prev);
    void put(Token *token, int id);
    int get(Token &token);

protected:
    Env* m_prev;

private:
    std::unordered_map<Token*, int> m_table;
};

#endif //ECOMPILER_ENV_H
