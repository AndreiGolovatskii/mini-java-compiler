#pragma once

#include <deque>
#include <string>

#include "ast_components.hh"
#include "i_type.hh"
#include "scope.hh"

class TScopeTable {
public:
    void BeginScope(const std::string& name = "") {
        ScopeStack_.emplace_back(name);
    }

    void EndScope() {
        ScopeStack_.pop_back();
    }

    void AddVariable(const std::string& name, std::unique_ptr<IType>&& type) {
        ScopeStack_.back().AddVariable(name, std::move(type));
    }

    [[nodiscard]] TVariableSpecification* Variable(const std::string& name) const {
        for (auto it = ScopeStack_.rbegin(); it != ScopeStack_.rend(); ++it) {
            auto* variable = it->Variable(name);
            if (variable) {
                return variable;
            }
        }
        throw std::logic_error{"Compilation Error: Undeclared identifier " + name};// TODO Compilation Error
    }

private:
    std::deque<TScope> ScopeStack_;
};
