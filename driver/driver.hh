#pragma once

#include <fstream>

#include "parser.hh"
#include "program.hh"
#include "scanner.h"


class TDriver {
public:
    explicit TDriver() : scanner(*this), parser(scanner, *this) {}

    int parse(const std::string& f);

    std::string file;
    bool trace_parsing  = false;
    bool trace_scanning = false;
    yy::location location;
    Scanner scanner;
    yy::parser parser;
    TProgramPtr Program_;


    void scan_begin();

    void scan_end();

    friend class Scanner;

private:
    std::ifstream stream;
};
