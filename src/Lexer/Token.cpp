//
// Created by Pavel Bibichenko on 20.06.2020.
//

#include "../../include/Lexer/Token.h"
#include "../../include/IO/Logger.h"
#include "../../include/Lexer/Num.h"
#include "../../include/Lexer/Real.h"
#include "../../include/Lexer/Word.h"
#include "../../include/Lexer/String.h"

Token::Token(int tag) {
    m_tag = tag;

    //Logger::instance().log("Lexer", "new token: " + toString());
}

/* */

std::string Token::toString() {
    std::string out;

    switch (m_tag) {
        case 272:
            out = dynamic_cast<Real*>(this)->toString();
            break;
        case 270:
            out = dynamic_cast<Num*>(this)->toString();
            break;
        case 274:
            out = "true";
            break;
        case 275:
            out = "while";
            break;
        case 262:
            out = "false";
            break;
        case 265:
            out = "if";
            break;
        case 260:
            out = "else";
            break;
        case 259:
            out = "do";
            break;
        case 268:
            out = "-";
            break;
        case 258:
            out = "break";
            break;
        case 264:
            out = static_cast<Word*>(this)->toString();
            break;
        case 257:
            out = "basic";
            break;
        case 256:
            out = "&&";
            break;
        case 261:
            out = "==";
            break;
        case 269:
            out = "!=";
            break;
        case 273:
            out = "t";
            break;
        case 266:
            out = "index";
            break;
        case 263:
            out = ">=";
            break;
        case 267:
            out = "<=";
            break;
        case 271:
            out = "||";
            break;
        case 290:
            out = "READ";
            break;
        case 291:
            out = "WRITE";
            break;
        case 292:
            out = static_cast<String*>(this)->toString();
            break;
        case 293:
            out = "DQUOTE";
            break;
        default:
            out = std::string(1, (char)m_tag);
            return out;
    }

    return out;
}

int Token::tag() const {
    return m_tag;
}

