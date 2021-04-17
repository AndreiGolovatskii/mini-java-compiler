#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "types.hh"


class TScope {
public:
    explicit TScope(std::string debugName = "") : debugName(std::move(debugName)) {}

    void AddVariable(const std::string& name, std::unique_ptr<IType>&& type) {
        if (Variable_.contains(name)) {
            throw std::logic_error{"Compilation Error: Variable redefinition"};
        }
        Variable_[name] = std::make_unique<TVariableSpecification>(std::move(type), false);
    }

    [[nodiscard]] TVariableSpecification* TryVariable(const std::string& name) const {
        if (Variable_.contains(name)) {
            return Variable_.at(name).get();
        }
        return nullptr;
    }

    [[nodiscard]] TVariableSpecification* Variable(const std::string& name) const {
        auto* res = TryVariable(name);
        if (res) {
            return res;
        }
        throw std::logic_error{"Compilation Error: Variable used without declaration"};
    }

public:
    const std::string debugName;

private:
    std::unordered_map<std::string, std::unique_ptr<TVariableSpecification>> Variable_;
};


class TScopeTreeNode : public TScope {
public:
    TScopeTreeNode(std::string debugName, TScopeTreeNode* parent) : TScope(std::move(debugName)), Parent_(parent) {}

    TScopeTreeNode* Parent() {
        return Parent_;
    }

private:
    TScopeTreeNode* Parent_{nullptr};
};