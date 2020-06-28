//
// Created by Pavel Bibichenko on 27.06.2020.
//

#include "../../../include/Interpreter/Constructions/Write.h"
#include "../../../include/IO/Logger.h"
#include "../../../include/SymbolTable/TypeTable.h"

Write::Write(Expression* x) {
    m_expr = x;
}

void Write::gen(int b, int a) {

    /*if (m_expr->type() == TypeTable::instance().t_str) {

    } else if (m_expr->type() == TypeTable::instance().t_int) {
        emit("write: " + m_expr->toString());

        for (const auto& v : Logger::instance().m_vars) {
            if (m_expr->toString() == v.name) {
                //aemit("mov eax, " + v.name);
                aemit("mov eax, [" + v.name + "]");
                aemit("push eax");
                aemit("push fmtd");
                aemit("call printf");
                aemit("add esp, 8"); // Restore stack pointer after
                break;
            }
        }
    } else if (m_expr->type() == TypeTable::instance().t_float) {
        emit("write: " + m_expr->toString());

        for (const auto& v : Logger::instance().m_vars) {
            if (m_expr->toString() == v.name) {
                //aemit("mov eax, " + v.name);
                aemit("mov eax, [" + v.name + "]");
                aemit("push eax");
                aemit("push fmtf");
                aemit("call printf");
                aemit("add esp, 8"); // Restore stack pointer after
                break;
            }
        }
    }*/

    std::string formatString;

    if (m_expr->type() == TypeTable::instance().t_str) {
        emit("write: \"" + m_expr->toString()+"\"");
        if (!Logger::instance().m_passages) {
            Logger::instance().m_lines.push_back(m_expr->toString()); // Add line to ASM vars
            return;
        }
        int numb = Logger::instance().getLineNumb();

        // ASM CODE
        aemit("mov eax, 4"); // sys call
        aemit("mov ebx, 1"); // file descriptor
        aemit("mov ecx, line" + std::to_string(numb));
        aemit("mov edx, lenLine" + std::to_string(numb));
        aemit("int 80h");
        return;
    }

    int size = 4 + m_expr->type()->width();
    emit("write: " + m_expr->toString());

    if (m_expr->type() == TypeTable::instance().t_float)
        formatString = "fmtf";
    else if (m_expr->type() == TypeTable::instance().t_bool)
        formatString = "fmtb";
    else if (m_expr->type() == TypeTable::instance().t_int)
        formatString = "fmtd";
    else if (m_expr->type() == TypeTable::instance().t_char)
        formatString = "fmtc";

    for (const auto& v : Logger::instance().m_vars) {
        if (m_expr->toString() == v.name) {
            //aemit("mov eax, " + v.name);
            aemit("mov eax, [" + v.name + "]");
            aemit("push eax");
            aemit("push " + formatString);
            aemit("call printf");
            aemit("add esp, " + std::to_string(size)); // Restore stack pointer after
            break;
        }
    }
}