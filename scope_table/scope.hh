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
        Variable_[name] = std::make_unique<TVariableSpecification>(std::move(type), false);
    }

    [[nodiscard]] TVariableSpecification* Variable(const std::string& name) const {
        if (Variable_.contains(name)) {
            return Variable_.at(name).get();
        }
        return nullptr;
    }

public:
    const std::string debugName;

private:
    std::unordered_map<std::string, std::unique_ptr<TVariableSpecification>> Variable_;
};