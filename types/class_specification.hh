#pragma once

#include <cassert>
#include <string>
#include <unordered_map>
#include <utility>

#include "i_type.hh"
#include "method_scpecification.hh"
#include "variable_specification.hh"


class TClassSpecification {
public:
    explicit TClassSpecification(TClassSpecification* extends = nullptr) {
        assert(extends == nullptr);// TODO Extends
    }

    void AddVariable(const std::string& name, std::unique_ptr<IType> type, bool isStatic = false) {
        if (Variables_.contains(name)) {
            throw std::logic_error{"Compilation Error: Variable redefinition"};// TODO Errors
        }
        Variables_[name] = std::make_unique<TVariableSpecification>(std::move(type), isStatic);
    }

    void AddMethod(const std::string& name, std::unique_ptr<TMethodSpecification>&& method) {
        if (Methods_.contains(name)) {
            throw std::logic_error{"Compilation Error: Method redefinition"};// TODO Errors
        }
        Methods_[name] = std::move(method);
    }

    [[nodiscard]] TVariableSpecification* Variable(const std::string& name) const {
        if (Variables_.contains(name)) {
            return Variables_.at(name).get();
        }
        throw std::logic_error{"Compilation Error: Undefined symbol"};// TODO Compilation Errors
    }

    [[nodiscard]] TMethodSpecification* Method(const std::string& name) const {
        if (Methods_.contains(name)) {
            return Methods_.at(name).get();
        }
        throw std::logic_error{"Compilation Error: Undefined symbol"};// TODO
    }

private:
    std::unordered_map<std::string, std::unique_ptr<TVariableSpecification>> Variables_;
    std::unordered_map<std::string, std::unique_ptr<TMethodSpecification>> Methods_;
};
