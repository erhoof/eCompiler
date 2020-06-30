//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Node.h"
#include "../../include/Lexer/Lexer.h"
#include "../../include/IO/Logger.h"
#include "../../include/Core/Core.h"
#include "../../include/Interpreter/Id.h"
#include "../../include/SymbolTable/TypeTable.h"

int Node::m_labels = 0;

Node::Node() {
    m_lexerLine = Lexer::line();
}

int Node::newLabel() {
    return ++m_labels;
}

void Node::emitLabel(int i) {
    std::string out = "L" + std::to_string(i) + ":";
    Logger::instance().log(out);
    Logger::instance().nalog(out);
}

void Node::emit(std::string str) {
    Logger::instance().log(str);
}

void Node::aemit(std::string str) {
    Logger::instance().alog(str);
}

void Node::error(std::string str) const {
    Logger::instance().log("Interpreter", "error. line: " + std::to_string(m_lexerLine) + ": " + str);
    Core::instance().dumpCore("interpreter has caused a core dump.");
}

void Node::aExprEmit(void* id, std::string statement) {
    Id* m_id = (Id*)id;

    // Check if it's array
    if (statement.find("]") != std::string::npos) {
        Logger::instance().log("Interpreter", "it's an array!");

        int i = 0;
        std::string lhr;
        std::string rhr;
        bool nameSet = false;
        for (; i < statement.size(); i++) {
            if (statement[i] == ' ')
                continue;

            if (statement[i] == '[') {
                nameSet = true;
                continue;
            }

            if (statement[i] == ']')
                break;

            if (!nameSet) {
                lhr += statement[i];
            } else {
                rhr += statement[i];
            }
        }

        if (isalpha(rhr[0]))
            aemit("mov eax, [" + rhr + "]");
        else
            aemit("mov eax, " + rhr);

        //aemit("mov ebx, dword [" + array()->toString() + " + ebx * " + std::to_string(s2e->type()->width())  + "]")
        aemit("mov ebx, dword [" + lhr + " + eax * " + std::to_string(m_id->type()->width()) + "]");
        aemit("mov [" + m_id->toString() + "], ebx");

        return;
    }

    // Parse set
    std::string lhr;
    std::string rhr;
    std::string op;
    const char* cExprString = statement.c_str();
    int i = 0;
    if (cExprString[0] == '-') {
        lhr += '-';
        i++;
    }
    for (; i < statement.size(); i++) {
        if (cExprString[i] == ' ')
            continue;

        if (op.empty()) {
            if (cExprString[i] == '/' ||
                cExprString[i] == '*' ||
                cExprString[i] == '+' ||
                cExprString[i] == '-')
                op = cExprString[i];
            else
                lhr += cExprString[i];
        } else {
            rhr += cExprString[i];
        }
    }

    // Check for t's
    if (op.empty()) { // no complicated things
        if (lhr == "true") {
            Logger::instance().alog("mov eax, [" + m_id->toString() + "]");
            Logger::instance().alog("or eax, 0x01");
            Logger::instance().alog("mov [" + m_id->toString() + "], eax"); // place in place uwu
        } else if (lhr == "false") {
            Logger::instance().alog("mov eax, [" + m_id->toString() + "]");
            Logger::instance().alog("and eax, 0xFFFFFFFE");
            Logger::instance().alog("mov [" + m_id->toString() + "], eax"); // place in place uwu
        } else if (isalpha(lhr[0])) {
            Logger::instance().alog("mov eax, [" + lhr + "]");
            Logger::instance().alog("mov [" + m_id->toString() + "], eax");
        } else if (lhr[0] == '-' && isalpha(lhr[1])) { // - with var
            lhr.erase(0, 1); // remove first char (-)

            Logger::instance().alog("mov eax, [" + lhr + "]");
            Logger::instance().alog("imul eax, -1"); // mul eax by -1
            Logger::instance().alog("mov [" + m_id->toString() + "], eax"); // place in place uwu
        } else if (lhr[0] == '!') {
            lhr.erase(0, 1); // remove first char (!)
            if (lhr == "true") {
                Logger::instance().alog("mov eax, [" + m_id->toString() + "]");
                Logger::instance().alog("and eax, 0xFFFFFFFE");
            } else if (lhr == "false") {
                Logger::instance().alog("mov eax, [" + m_id->toString() + "]");
                Logger::instance().alog("or eax, 0x01");
            } else {
                Logger::instance().alog("mov eax, [" + lhr + "]");
                Logger::instance().alog("xor eax, 0x01"); // flip first bit
            }
            Logger::instance().alog("mov [" + m_id->toString() + "], eax"); // place in place uwu
        } else {
            Logger::instance().alog("mov eax, " + lhr);
            Logger::instance().alog("mov [" + m_id->toString() + "], eax");
        }
    } /*else if (lhr[0] == 't' && rhr[0] == 't') { // lhr + rhr is t's
        Logger::instance().alog("mov eax, [" + lhr + "]");
        Logger::instance().alog("mov ebx, [" + rhr + "]");
    } else if (lhr[0] == 't') { // only lhr
        Logger::instance().alog("mov eax, [" + lhr + "]");
        Logger::instance().alog("mov ebx, " + rhr);
    } else if (rhr[0] == 't' ){ // only rhr
        Logger::instance().alog("mov eax, " + lhr);
        Logger::instance().alog("mov ebx, [" + rhr + "]");
    } */else { // no t's

        if (isalpha(lhr[0]))
            Logger::instance().alog("mov eax, [" + lhr + "]");
        else
            Logger::instance().alog("mov eax, " + lhr);

        if (isalpha(rhr[0]))
            Logger::instance().alog("mov ebx, [" + rhr + "]"); // is it var on numb
        else
            Logger::instance().alog("mov ebx, " + rhr);
    }

    switch(op.c_str()[0]) {
        case '+': {
            if (m_id->type() == TypeTable::instance().t_float) {

            } else {
                Logger::instance().alog("add eax, ebx");
                Logger::instance().alog("mov [" + m_id->toString() + "], eax");
            }
            break;
        }
        case '-': {
            if (m_id->type() == TypeTable::instance().t_float) {

            } else {
                Logger::instance().alog("sub eax, ebx");
                Logger::instance().alog("mov [" + m_id->toString() + "], eax");
            }
            break;
        }
        case '*': {
            if (m_id->type() == TypeTable::instance().t_float) {

            } else {
                Logger::instance().alog("imul eax, ebx");
                Logger::instance().alog("mov [" + m_id->toString() + "], eax");
            }
            break;
        }
        case '/': {
            if (m_id->type() == TypeTable::instance().t_float) {

            } else {
                Logger::instance().alog("mov edx, 0");
                Logger::instance().alog("idiv ebx");
                Logger::instance().alog("mov [" + m_id->toString() + "], eax");
            }
            break;
        }
    }
}