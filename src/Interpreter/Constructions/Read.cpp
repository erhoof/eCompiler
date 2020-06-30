//
// Created by Pavel Bibichenko on 27.06.2020.
//

#include "../../../include/Interpreter/Constructions/Read.h"
#include "../../../include/IO/Logger.h"
#include "../../../include/SymbolTable/TypeTable.h"

Read::Read(Expression* x) {
    m_expr = x;
}

void Read::gen(int b, int a) {
    if (!Logger::instance().m_passages)
        return;

    std::string formatString;
    if (m_expr->type() == TypeTable::instance().t_float)
        formatString = "fmtfi";
    else if (m_expr->type() == TypeTable::instance().t_bool)
        formatString = "fmtbi";
    else if (m_expr->type() == TypeTable::instance().t_int)
        formatString = "fmtdi";
    else if (m_expr->type() == TypeTable::instance().t_char)
        formatString = "fmtci";
    else if (m_expr->type() == TypeTable::instance().t_str)
        error("can't input string variable data!");

    int size = 4 + m_expr->type()->width();

    Expression* ex = m_expr->gen();
    std::string statement = ex->toString();
    emit("read: " + ex->toString());

    if (ex->toString().find('[') != std::string::npos) {
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
        aemit("mov ebx, dword [" + lhr + " + eax * " + std::to_string(ex->type()->width()) + "]");
        aemit("mov eax, ebx");
        aemit("push eax");
        aemit("push " + formatString);
        aemit("call printf");
        aemit("add esp, " + std::to_string(size)); // Restore stack pointer after
    } else {
        aemit("mov eax, " + ex->toString());
        aemit("push eax");
        aemit("push " + formatString);
        aemit("call scanf");
        aemit("add esp, " + std::to_string(size));
    }

    /*for (const auto& v : Logger::instance().m_vars) {
        if (m_expr->toString() == v.name) {
            //aemit("mov eax, " + v.name);
            aemit("mov eax, [" + v.name + "]");
            aemit("push eax");
            aemit("push " + formatString);
            aemit("call printf");
            aemit("add esp, " + std::to_string(size)); // Restore stack pointer after
            break;
        }
    }*/


}