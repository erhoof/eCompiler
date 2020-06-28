//
// Created by Pavel Bibichenko on 20.06.2020.
//

#ifndef ECOMPILER_TAG_H
#define ECOMPILER_TAG_H

class Tag {
public:
    enum Constants {
        C_AND    = 256,
        C_ELSE   = 260,
        C_ID     = 264,
        C_MINUS  = 268,
        C_REAL   = 272,
        C_BASIC  = 257,
        C_EQ     = 261,
        C_IF     = 265,
        C_NE     = 269,
        C_TEMP   = 273,
        C_BREAK  = 258,
        C_FALSE  = 262,
        C_INDEX  = 266,
        C_NUM    = 270,
        C_TRUE   = 274,
        C_DO     = 259,
        C_GE     = 263,
        C_LE     = 267,
        C_OR     = 271,
        C_WHILE  = 275,
        C_READ   = 290,
        C_WRITE  = 291,
        C_STRING = 292,
        C_DQUOTE = 293
    };

    static int
        AND,
        ELSE,
        ID,
        MINUS,
        REAL,
        BASIC,
        EQ,
        IF,
        NE,
        TEMP,
        BREAK,
        FALSE,
        INDEX,
        NUM,
        TRUE,
        DO,
        GE,
        LE,
        OR,
        WHILE,
        READ,
        WRITE,
        STRING,
        DQUOTE;
};

#endif //ECOMPILER_TAG_H
