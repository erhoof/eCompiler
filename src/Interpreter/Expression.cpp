//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Interpreter/Expression.h"
#include "../../include/Interpreter/Arithmetic.h"
#include "../../include/Interpreter/Temp.h"
#include "../../include/Interpreter/Logical.h"
#include "../../include/Interpreter/Relation.h"
#include "../../include/Interpreter/Unary.h"
#include "../../include/Interpreter/Access.h"
#include "../../include/Interpreter/And.h"
#include "../../include/Interpreter/Or.h"
#include "../../include/Interpreter/Not.h"
#include "../../include/Interpreter/Constant.h"
#include "../../include/Lexer/Tag.h"

#include <iostream>

Expression::Expression(Token* token, Type* type) {
    m_operand = token;
    m_type = type;
}

Expression* Expression::gen() {
    switch(m_objType) {
        case ACCESS:
            return dynamic_cast<Access*>(this)->gen();
        case ARITHMETIC:
            return dynamic_cast<Arithmetic*>(this)->gen();
        case LOGICAL:
            return dynamic_cast<Logical*>(this)->gen();
        case UNARY:
            return dynamic_cast<Unary*>(this)->gen();
        default:
            return this;
    }
}

Expression* Expression::reduce() {
    switch(m_objType) {
        case ARITHMETIC:
            return dynamic_cast<Arithmetic*>(this)->reduce();
        default:
            return this;
    }
}

void Expression::jumping(int t, int f) {
    switch (m_objType) {
        case ACCESS:
            dynamic_cast<Access*>(this)->jumping(t, f);
            break;
        case AND:
            dynamic_cast<And*>(this)->jumping(t, f);
            break;
        case CONSTANT:
            dynamic_cast<Constant*>(this)->jumping(t, f);
            break;
        case NOT:
            dynamic_cast<Not*>(this)->jumping(t, f);
            break;
        case OR:
            dynamic_cast<Or*>(this)->jumping(t, f);
            break;
        case ObjTypes::RELATION:
            dynamic_cast<Relation*>(this)->jumping(0, f);
            break;
        default:
            emitJumps(toString(), t, f);
            emitBasicAsmJumps(toString(), t, f);
            //emitAsmJumps(this, nullptr, operand(), t, f);
    }
}

void Expression::emitJumps(std::string test, int t, int f) {
    if (t != 0 && f != 0) {
        emit("if " + test + " goto L" + std::to_string(t));
        emit("goto L" + std::to_string(f));
    } else if (t != 0) {
        emit ("if " + test + " goto L" + std::to_string(t));
    } else if (f != 0) {
        emit("iffalse " + test + " goto L" + std::to_string(f));
    }
}

void Expression::emitBasicAsmJumps(std::string test, int t, int f) {
    if (test[0] == '!') {
        test.erase(0, 1);
        if (test == "true") {
            if (t != 0 && f != 0) {
                aemit("jmp L" + std::to_string(f));
            } else if (f != 0) {
                aemit("jmp L" + std::to_string(f));
            }
        } else if (test == "false") {
            if (t != 0 && f != 0) {
                aemit("jmp L" + std::to_string(t));
                aemit("jmp L" + std::to_string(f));
            } else if (t != 0) {
                aemit("jmp L" + std::to_string(t));
            }
        } else { // TODO: CHECK LATER PLEASE!! I WAS TOO SLEEPY!
            if (t != 0 && f != 0) {
                //emit("if " + test + " goto L" + std::to_string(t));
                //emit("goto L" + std::to_string(f));
                aemit("mov eax, [" + test + "]"); // ?
                aemit("cmp eax, 0xFFFFFFFE");
                aemit("je L" + std::to_string(t));
                aemit("jmp L" + std::to_string(f));
            } else if (t != 0) {
                //emit ("if " + test + " goto L" + std::to_string(t));
                aemit("mov eax, [" + test + "]"); // ?
                aemit("cmp eax, 0xFFFFFFFE");
                aemit("je L" + std::to_string(t));
            } else if (f != 0) {
                //emit("iffalse " + test + " goto L" + std::to_string(f));
                aemit("mov eax, [" + test + "]"); // ?
                aemit("cmp eax, 0xFFFFFFFE");
                aemit("jne L" + std::to_string(f)); // if ? not eq to true -> go F
            }
        }
    } else {
        if (test == "true") {
            if (t != 0 && f != 0) {
                aemit("jmp L" + std::to_string(t));
                aemit("jmp L" + std::to_string(f));
            } else if (t != 0) {
                aemit("jmp L" + std::to_string(t));
            }
        } else if (test == "false") {
            if (t != 0 && f != 0) {
                aemit("jmp L" + std::to_string(f));
            } else if (f != 0) {
                aemit("jmp L" + std::to_string(f));
            }
        } else {
            if (t != 0 && f != 0) {
                //emit("if " + test + " goto L" + std::to_string(t));
                //emit("goto L" + std::to_string(f));
                aemit("mov eax, [" + test + "]"); // ?
                aemit("cmp eax, 0x01");
                aemit("je L" + std::to_string(t));
                aemit("jmp L" + std::to_string(f));
            } else if (t != 0) {
                //emit ("if " + test + " goto L" + std::to_string(t));
                aemit("mov eax, [" + test + "]"); // ?
                aemit("cmp eax, 0x01");
                aemit("je L" + std::to_string(t));
            } else if (f != 0) {
                //emit("iffalse " + test + " goto L" + std::to_string(f));
                aemit("mov eax, [" + test + "]"); // ?
                aemit("cmp eax, 0x01");
                aemit("jne L" + std::to_string(f)); // if ? not eq to true -> go F
            }
        }
    }
}

void Expression::emitAsmJumps(Expression* x1, Expression* x2, Token* op, int t, int f) {
    std::string x1s = x1->toString();
    std::string x2s = x2->toString();
    if (isalpha(x1s[0])) // Check if x1 is var or constant and move it
        aemit("mov eax, [" + x1s + "]");
    else
        aemit("mov eax, " + x1s);
    if (isalpha(x2s[0])) // Check if x2 is var or constant and move it
        aemit("mov ebx, [" + x2s + "]");
    else
        aemit("mov ebx, " + x2s);

    if (t != 0 && f != 0) {
        //emit("if " + test + " goto L" + std::to_string(t));
        //emit("goto L" + std::to_string(f));
        aemit("cmp eax, ebx");

        switch(op->tag()) {
            case '<':
                aemit("jl l" + std::to_string(t)); // Jump Less
                break;
            case Tag::C_LE:
                aemit("jle L" + std::to_string(t)); // Jump Less/Equal
                break;
            case Tag::C_GE:
                aemit("jge L" + std::to_string(t)); // Jump Greater/Equal
                break;
            case '>':
                aemit("jg L" + std::to_string(t)); // Jump Greater
                break;
            case Tag::C_EQ:
                aemit("je L" + std::to_string(t)); // Jump Equal
                break;
            case Tag::C_NE:
                aemit("jne L" + std::to_string(t)); // Jump Not Equal
                break;
        }
        aemit("jmp L" + std::to_string(f));
    } else if (t != 0) {
        //emit ("if " + test + " goto L" + std::to_string(t));
        aemit("cmp eax, ebx");

        switch(op->tag()) {
            case '<':
                aemit("jl l" + std::to_string(t)); // Jump Less
                break;
            case Tag::C_LE:
                aemit("jle L" + std::to_string(t)); // Jump Less/Equal
                break;
            case Tag::C_GE:
                aemit("jge L" + std::to_string(t)); // Jump Greater/Equal
                break;
            case '>':
                aemit("jg L" + std::to_string(t)); // Jump Greater
                break;
            case Tag::C_EQ:
                aemit("je L" + std::to_string(t)); // Jump Equal
                break;
            case Tag::C_NE:
                aemit("jne L" + std::to_string(t)); // Jump Not Equal
                break;
        }
    } else if (f != 0) {
        //emit("iffalse " + test + " goto L" + std::to_string(f));
        aemit("cmp eax, ebx");

        switch(op->tag()) { // REVERSED FROM MAIN IF
            case Tag::C_GE: // <
                aemit("jg l" + std::to_string(f)); // Jump Less
                break;
            case '>': // LE
                aemit("jle L" + std::to_string(f)); // Jump Less/Equal
                break;
            case '<': // GE
                aemit("jge L" + std::to_string(f)); // Jump Greater/Equal
                break;
            case Tag::C_LE: // >
                aemit("jg L" + std::to_string(f)); // Jump Greater
                break;
            case Tag::C_NE: // EQ
                aemit("je L" + std::to_string(f)); // Jump Equal
                break;
            case Tag::C_EQ: // NE
                aemit("jne L" + std::to_string(f)); // Jump Not Equal
                break;
        }
    }
}

std::string Expression::toString() {
    std::string out;

    switch(m_objType) {
        case ACCESS:
            out = dynamic_cast<Access*>(this)->toString();
            break;
        case ObjTypes::ARITHMETIC:
            out = dynamic_cast<Arithmetic*>(this)->toString();
            break;
        case ObjTypes::TEMP:
            out = dynamic_cast<Temp*>(this)->toString();
            break;
        case ObjTypes::LOGICAL:
            out = dynamic_cast<Logical*>(this)->toString();
            break;
        case ObjTypes::UNARY:
            out = dynamic_cast<Unary*>(this)->toString();
            break;
        case NOT:
            out = dynamic_cast<Not*>(this)->toString();
            break;
        default:
            out = m_operand->toString();
    }

    return out;
}

Type* Expression::type() const {
    return m_type;
}

Token* Expression::operand() const {
    return m_operand;
}

