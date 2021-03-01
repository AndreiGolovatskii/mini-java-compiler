#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL yy::parser::symbol_type Scanner::ScanToken()

#include "parser.hh"

class TDriver;

class Scanner : public yyFlexLexer {
public:
    Scanner(TDriver& driver) : driver(driver) {}
    virtual ~Scanner() {}
    virtual yy::parser::symbol_type ScanToken();
    TDriver& driver;
};