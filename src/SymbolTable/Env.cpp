//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/SymbolTable/Env.h"

Env::Env(Env* prev) {
    m_prev = prev;
}

void Env::put(Token* token, int id) {
    m_table.insert(std::pair<Token*, int>(token, id));
}

int Env::get(Token& token) {
    for (Env* e = this; e != nullptr; e = e->m_prev) {
        auto search = e->m_table.find(&token);
        if (search != e->m_table.end())
            return search->second;
    }

    return -1;
}
