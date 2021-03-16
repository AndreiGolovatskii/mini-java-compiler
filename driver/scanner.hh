#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL yy::parser::symbol_type TScanner::ScanToken()

#include "parser.hh"
class TDriver;

class TScanner : public yyFlexLexer {
public:
    explicit TScanner(TDriver& driver) : driver(driver) {}
    ~TScanner() override = default;
    virtual yy::parser::symbol_type ScanToken();
    TDriver& driver;
};