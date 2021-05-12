#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "types.hh"


template<class T>
class TScope {
public:
    explicit TScope(std::string debugName = "") : debugName(std::move(debugName)) {}

    template<class... Args>
    void AddVariable(const std::string& name, Args&&... args) {
        if (Variable_.contains(name)) {
            throw std::logic_error{"Compilation Error: Variable redefinition"};
        }
        Variable_.emplace(std::pair<const std::string, T>(name, T{std::forward<Args>(args)...}));
    }

    [[nodiscard]] bool HasVariable(const std::string& name) const {
        return Variable_.contains(name);
    }

    [[nodiscard]] const T& Variable(const std::string& name) const {
        return Variable_.at(name);
    }

public:
    std::string debugName;

private:
    std::unordered_map<std::string, T> Variable_;
};


template<class T>
class TScopeTreeNode : public TScope<T> {
public:
    TScopeTreeNode(const std::string& debugName, TScopeTreeNode* parent) : TScope<T>(debugName), Parent_(parent) {}

    TScopeTreeNode* Parent() {
        return Parent_;
    }

private:
    TScopeTreeNode* Parent_{nullptr};
};