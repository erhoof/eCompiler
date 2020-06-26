//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Node.h"
#include "../../include/Lexer/Lexer.h"
#include "../../include/IO/Logger.h"
#include "../../include/Core/Core.h"

int Node::m_labels = 0;

Node::Node() {
    m_lexerLine = Lexer::line();
}

int Node::newLabel() {
    return ++m_labels;
}

void Node::emitLabel(int i) {
    std::string out = "L" + std::to_string(i) + ":";
    Logger::instance().nlog(out);
}

void Node::emit(std::string str) {
    Logger::instance().log(str);
}

void Node::error(std::string str) const {
    Logger::instance().log("Interpreter", "error. line: " + std::to_string(m_lexerLine) + ": " + str);
    Core::instance().dumpCore("interpreter has caused a core dump.");
}
