#pragma once

#include <string>

class IType {
public:
    virtual size_t Size() = 0;
    virtual ~IType()      = default;
};