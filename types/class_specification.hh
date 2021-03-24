#pragma once

#include <cassert>
#include <string>
#include <unordered_map>
#include <utility>

#include "i_type.hh"

class TArgument {
public:
    TArgument(std::string name, std::unique_ptr<IType>&& type) : Name_(std::move(name)), Type_(std::move(type)) {}

private:
    std::string Name_;
    std::unique_ptr<IType> Type_;
};

class TMethodSpecification {
public:
    explicit TMethodSpecification(std::unique_ptr<IType>&& returnType, std::vector<TArgument>&& args,
                                  bool isStatic = false)
        : ReturnType_(std::move(returnType)), Args_(std::move(args)), IsStatic_(isStatic) {}

    [[nodiscard]] bool IsStatic() const {
        return IsStatic_;
    }

private:
    std::unique_ptr<IType> ReturnType_;
    std::vector<TArgument> Args_;
    bool IsStatic_;
};


class TVariableSpecification {
public:
    TVariableSpecification(std::unique_ptr<IType>&& type, bool isStatic) : Type_(std::move(type)), IsStatic_(isStatic) {
        assert(isStatic == false);// TODO Support static variable
    }

    [[nodiscard]] IType* Type() const {
        return Type_.get();
    }

    [[nodiscard]] bool IsStatic() const {
        return IsStatic_;
    }

private:
    std::unique_ptr<IType> Type_;
    bool IsStatic_;
};

class TClassSpecification {
public:
    explicit TClassSpecification(TClassSpecification* extends = nullptr) {
        assert(extends == nullptr);// TODO Extends
    }
    void AddVariable(const std::string& name, std::unique_ptr<IType> type, bool isStatic = false) {
        if (Variable_.contains(name)) {
            throw std::logic_error{"Compilation Error: Variable redefinition"};// TODO Errors
        }
        Variable_[name] = std::make_unique<TVariableSpecification>(std::move(type), isStatic);
    }


    void AddMethod(const std::string& name, std::unique_ptr<TMethodSpecification>&& method) {
        if (Methods_.contains(name)) {
            throw std::logic_error{"Compilation Error: Method redefinition"};// TODO Errors
        }
        Methods_[name] = std::move(method);
    }

    [[nodiscard]] TVariableSpecification* Variable(const std::string& name) const {
        if (Variable_.contains(name)) {
            return Variable_.at(name).get();
        }
        throw std::logic_error{"Compilation Error: Undefined symbol"};// TODO Compilation Errors
    }

    [[nodiscard]] TMethodSpecification* Method(const std::string& name) const {
        if (Methods_.contains(name)) {
            return Methods_.at(name).get();
        }
        throw std::logic_error{"Compilation Error: Undefined symbol"}; // TODO
    }

private:
    std::unordered_map<std::string, std::unique_ptr<TVariableSpecification>> Variable_;
    std::unordered_map<std::string, std::unique_ptr<TMethodSpecification>> Methods_;
};
