#include "driver.hh"
//#include "parser.hh"


int TDriver::parse(const std::string& f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(static_cast<int>(trace_parsing));
    int parse_result = static_cast<int>(parser());
    scan_end();
    return parse_result;
}

void TDriver::scan_begin() {
    scanner.set_debug(static_cast<int>(trace_scanning));
    if (file.empty() || file == "-") {
    } else {
        stream.open(file);
        scanner.yyrestart(&stream);
    }
}

void TDriver::scan_end() {
    stream.close();
}
