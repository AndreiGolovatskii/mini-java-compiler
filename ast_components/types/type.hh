#ifndef COMPILER_TYPE_HH
#define COMPILER_TYPE_HH

#include <memory>

class TType {
public:
    void MakeArray() {
        IsArray_ = true;
    }

    virtual ~TType() = default;

private:
    bool IsArray_ = false;
};


using TTypePtr = std::unique_ptr<TType>;


class TVoidType : public TType {};


using TVoidTypePtr = std::unique_ptr<TVoidType>;


class TIntType : public TType {};


using TIntTypePtr = std::unique_ptr<TIntType>;


class TBooleanType : public TType {};


using TBooleanTypePtr = std::unique_ptr<TBooleanType>;


class TIdentifierType : public TType {
public:
    explicit TIdentifierType(std::string&& identifier) : Identifier_(std::move(identifier)) {}

private:
    std::string Identifier_;
};


using TIdentifierTypePtr = std::unique_ptr<TIdentifierType>;

#endif//COMPILER_TYPE_HH
