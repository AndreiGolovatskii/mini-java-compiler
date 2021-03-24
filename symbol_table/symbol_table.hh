#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "class_specification.hh"

class TSymbolTable {
public:
    [[nodiscard]] TClassSpecification* Class(const std::string& name) const {
        if (ClassSpecifications_.contains(name)) {
            return ClassSpecifications_.at(name).get();
        }
        throw std::logic_error{"Compilation error: Undefined symbol"};// TODO Compilation Error
    }

    void AddClass(const std::string& name) {
        if (ClassSpecifications_.contains(name)) {
            throw std::logic_error{"Compilation error: Symbol redefinition"};// TODO Compilation Error
        }
        ClassSpecifications_[name] = std::make_unique<TClassSpecification>();
    }


private:
    std::unordered_map<std::string, std::unique_ptr<TClassSpecification>> ClassSpecifications_;
};