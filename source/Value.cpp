// Copyright 2025 solar-mist

#include "vtoml/Value.h"

namespace toml
{
    StringValue::StringValue(std::string value)
        : mValue(std::move(value))
    {
    }

    std::string StringValue::toString() const
    {
        return mValue;
    }
}