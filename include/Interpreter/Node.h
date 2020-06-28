//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_NODE_H
#define ECOMPILER_NODE_H

#include <string>

class Node {
public:
    Node();

    int newLabel();
    void emitLabel(int i);
    void emit(std::string str);
    void aemit(std::string str);
    void aExprEmit(void* id, std::string statement);

    void error(std::string str) const;

    static int m_labels;

private:
    int m_lexerLine = 0;
};

#endif //ECOMPILER_NODE_H
