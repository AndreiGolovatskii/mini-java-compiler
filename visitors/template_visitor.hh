#pragma once

#include "ast_components.hh"
#include "partial_visitor.hh"

template<class ReturnType>
class TTemplateVisitor : public TPartialVisitor {
public:
    ReturnType Accept(INode* node) {
        node->Accept(this);
        return std::move(ReturnValue_.value());
    }

    template<typename T>
    void Return(T&& value) {
        ReturnValue_.emplace(std::forward<T>(value));
    }

private:
    std::optional<ReturnType> ReturnValue_;
};