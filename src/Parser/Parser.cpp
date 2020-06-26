//
// Created by Pavel Bibichenko on 25/06/2020.
//

#include "../../include/Parser/Parser.h"

#include <iostream>

#include "../../include/Core/Core.h"
#include "../../include/Lexer/Tag.h"
#include "../../include/IO/Logger.h"
#include "../../include/Interpreter/Constructions/Statement.h"
#include "../../include/SymbolTable/Array.h"
#include "../../include/Lexer/Num.h"
#include "../../include/Interpreter/Or.h"
#include "../../include/Interpreter/And.h"
#include "../../include/Interpreter/Constructions/Sequence.h"
#include "../../include/Interpreter/Constructions/Else.h"
#include "../../include/Interpreter/Constructions/If.h"
#include "../../include/Interpreter/Constructions/While.h"
#include "../../include/Interpreter/Constructions/Do.h"
#include "../../include/Interpreter/Constructions/Break.h"
#include "../../include/Interpreter/Constructions/Set.h"
#include "../../include/Interpreter/Constructions/SetElement.h"
#include "../../include/Interpreter/Relation.h"
#include "../../include/Interpreter/Arithmetic.h"
#include "../../include/Interpreter/Unary.h"
#include "../../include/Lexer/WordTable.h"
#include "../../include/Interpreter/Not.h"
#include "../../include/Interpreter/Constant.h"
#include "../../include/SymbolTable/TypeTable.h"
#include "../../include/Interpreter/ConstantTable.h"

Parser::Parser(Lexer* lexer) {
    Logger::instance().log("Parser", "created instance.");

    m_lexer = lexer;

    move();
}

void Parser::move() {
    m_look = m_lexer->scan();
}

void Parser::error(std::string out) {
    //Logger::instance().log("Parser", "errorЖ line: " + std::to_string(m_lexer->line()) + ": " + out);
    Logger::instance().flog(std::to_string(m_lexer->line()) + ": error: " + out);
    Core::instance().dumpCore("parser has caused a core dump.");
}

void Parser::match(int tag) {
    if (m_look->tag() == tag)
        move();
    else
        error("syntax error");
}

// Beginning of syntax parsing
void Parser::program() {
    Statement* s = block();

    int begin = s->newLabel();
    int after = s->newLabel();

    s->emitLabel(begin);
    s->gen(begin, after);
    s->emitLabel(after);
}

// block -> {decls stmts}
Statement* Parser::block() {
    match('{');
    auto savedEnv = m_top; // old -> new Symbol Table
    m_top = new Env(m_top);

    declarations();
    auto s = statements();

    match('}');
    m_top = savedEnv;

    return s;
}

void Parser::declarations() {
    while(m_look->tag() == Tag::BASIC) {
        Type* t = type();
        auto token = m_look;

        match(Tag::ID);
        match(';');

        //    Id(Word& id, Type& type, int offset);
        auto id = new Id((Word*)token, t, m_used);

        m_top->put(token, id);
        m_used += t->width();
    }
}

Type* Parser::type() {
    auto t = (Type*)m_look;

    match(Tag::BASIC);
    if (m_look->tag() != '[') // T -> basic
        return t;
    else
        return dimensionals(t); // Array
}

Type* Parser::dimensionals(Type *t) {
    match('[');
    auto token = m_look;

    match(Tag::NUM);
    match(']');

    if (m_look->tag() == '[')
        t = dimensionals(t);

    return new Array( ((Num*)token)->value(), *t );
}

// Statements
Statement* Parser::statements() {
    if (m_look->tag() == '}')
        return Statement::Null;
    else
        return new Sequence(statement(), statements());
}

Statement* Parser::statement() {
    Expression* x;
    Statement* s;
    Statement* s1;
    Statement* s2;
    Statement* savedStmt; // for break level up

    Logger::instance().log("Parser", "statement:" + Logger::string(m_look->tag()));

    switch(m_look->tag()) {
        case ';':
            Logger::instance().log("Parser", "m_look -> ;");
            move();
            return Statement::Null;
        case Tag::C_IF: {
            Logger::instance().log("Parser", "m_look -> IF");
            match(Tag::IF);
            match('(');
            x = boolean();
            match(')');
            s1 = statement();
            if (m_look->tag() != Tag::ELSE)
                return new If(x, s1);
            match(Tag::ELSE);
            s2 = statement();
            return new Else(x, s1, s2);
        }
        case Tag::C_WHILE: {
            auto whileNode = new While();
            savedStmt = Statement::Enclosing;
            Statement::Enclosing = whileNode;
            match(Tag::WHILE);
            match('(');
            x = boolean();
            match(')');
            s1 = statement();
            whileNode->init(x, s1);
            Statement::Enclosing = savedStmt; // reset
            return whileNode;
        }
        case Tag::C_DO: {
            auto doNode = new Do();
            savedStmt = Statement::Enclosing;
            Statement::Enclosing = doNode;
            match(Tag::DO);
            s1 = statement();
            match(Tag::WHILE);
            match('(');
            x = boolean();
            match(')');
            match(';');
            doNode->init(s1, x);
            Statement::Enclosing = savedStmt; // reset
            return doNode;
        }
        case Tag::C_BREAK: {
            match(Tag::BREAK);
            match(';');
            return new Break();
        }
        case '{':
            Logger::instance().log("Parser", "m_look -> BLOCK {");
            return block();
        default:
            Logger::instance().log("Parser", "m_look -> ASSIGNING");
            return assign();
    }
}

Statement* Parser::assign() {
    Statement* stmt;
    Token* t = m_look;
    match(Tag::ID);

    auto id = m_top->get(t);
    if (id == nullptr) {
        error("'" + dynamic_cast<Word*>(t)->toString() + "' undeclared");
    }

    if (m_look->tag() == '=') { // S -> id = E
        Logger::instance().log("Parser", "assigning easy");
        move();
        Expression* x = boolean();
        stmt = new Set(id, x);
    } else {
        Logger::instance().log("Parser", "assigning comp");
        Access* x = offset(id);
        match('=');
        stmt = new SetElement(x, boolean());
    }

    match(';');
    return stmt;
}
// End of statements

// Expressions
Expression* Parser::boolean() {
    Expression* x = join();

    while(m_look->tag() == Tag::OR) {

        auto token = m_look;
        move();
        x = new Or(token, x, join());
    }

    return x;
}

Expression* Parser::join() {
    Expression* x = equality();

    while (m_look->tag() == Tag::AND) {
        auto token = m_look;
        move();
        x = new And(token, x, equality());
    }

    return x;
}

Expression* Parser::equality() {
    Expression* x = relation();

    while (m_look->tag() == Tag::EQ || m_look->tag() == Tag::NE) {
        auto token = m_look;
        move();
        x = new Relation(token, x, relation());
        static_cast<Relation*>(x)->m_objType = Logical::RELATION;
    }

    return x;
}

Expression* Parser::relation() {
    Expression* x = expression();

    switch(m_look->tag()) {
        case '<':
        case Tag::C_LE:
        case Tag::C_GE:
        case '>': {
            auto token = m_look;
            move();
            auto rel = new Relation(token, x, expression());
            rel->m_objType = Logical::RELATION;
            return rel;
        }
        default:
            return x;
    }
}

Expression* Parser::expression() {
    Expression* x = term();

    while(m_look->tag() == '+' || m_look->tag() == '-') {
        auto token = m_look;
        move();
        x = new Arithmetic(token, x, term());
        x->m_objType = Expression::ARITHMETIC;
    }

    return  x;
}

Expression* Parser::term() {
    Expression* x = unary();
    while(m_look->tag() == '*' || m_look->tag() == '/') {
        auto token = m_look;
        move();
        x = new Arithmetic(token, x, unary());
        x->m_objType = Expression::ARITHMETIC;
    }

    return x;
}

Expression* Parser::unary() {
    if (m_look->tag() == '-') {
        move();
        return new Unary(WordTable::instance().w_minus, unary());
    } else if (m_look->tag() == '!') {
        auto token = m_look;
        move();
        return new Not(token, unary());
    } else {
        return factor();
    }
}

Expression* Parser::factor() {
    Expression* x = nullptr;
    switch(m_look->tag()) {
        case '(': {
            move();
            x = boolean();
            match(')');
            return x;
        }
        case Tag::C_NUM: {
            x = new Constant(m_look, TypeTable::instance().t_int);
            x->m_objType = Expression::CONSTANT;
            move();
            return x;
        }
        case Tag::C_REAL: {
            x = new Constant(m_look, TypeTable::instance().t_float);
            move();
            return x;
        }
        case Tag::C_TRUE: {
            x = ConstantTable::instance().c_true;
            move();
            return x;
        }
        case Tag::C_FALSE: {
            x = ConstantTable::instance().c_false;
            move();
            return x;
        }
        case Tag::C_ID: {
            std::string out = m_look->toString();
            auto id = m_top->get(m_look);
            if (id == nullptr)
                error("'" + m_look->toString() + "' undeclared");
            move();
            if (m_look->tag() != '[')
                return id;
            else
                return offset(id);
        }
        default:
            error("syntax error");
            return x;
    }
}

// Arrays
Access* Parser::offset(Id* a) { // I -> [E] | [E] I
    Expression* i;
    Expression* w;
    Expression* t1;
    Expression* t2;
    Expression* loc;
    Type* type = a->type();

    // First index, I -> [E]
    match('[');
    i = boolean();
    match(']');
    type = dynamic_cast<Array*>(type)->type();
    w = new Constant(type->width());
    w->m_objType = Expression::CONSTANT;
    t1 = new Arithmetic(new Token('*'), i, w);
    t1->m_objType = Expression::ARITHMETIC;
    loc = t1;

    // Multiple array [][][]
    while(m_look->tag() == '[') {
        match('[');
        i = boolean();
        match(']');
        type = dynamic_cast<Array*>(type)->type();
        w = new Constant(type->width());
        w->m_objType = Expression::CONSTANT;
        t1 = new Arithmetic(new Token('*'), i, w);
        t1->m_objType = Expression::ARITHMETIC;
        t2 = new Arithmetic(new Token('+'), loc, t1);
        t2->m_objType = Expression::ARITHMETIC;
        loc = t2;
    }

    return new Access(a, loc, type);
}