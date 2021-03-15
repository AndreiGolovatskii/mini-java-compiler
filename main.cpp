#include <iostream>

#include "driver.hh"
#include "yaml_visitor.hh"

int main(int argc, char* argv[]) {
    TDriver driver;
    driver.parse(argv[1]);

    TYamlVisitor visitor;
    driver.Program_->Accept(&visitor);
    visitor.Print(std::cout);
    return 0;
}
