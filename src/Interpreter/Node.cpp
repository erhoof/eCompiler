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
    Logger::instance().log("OUT", "L" + std::to_string(i) + ":");
}

void Node::emit(std::string str) {
    Logger::instance().log("OUT", "\t" + str);
}

void Node::error(std::string str) const {
    Logger::instance().log("Interpreter", "error. line: " + std::to_string(m_lexerLine) + ": " + str);
    Core::instance().dumpCore("interpreter has caused a core dump.");
}
