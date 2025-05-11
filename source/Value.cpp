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

    
    ArrayValue::ArrayValue(std::vector<ValuePtr> values)
        : mValues(std::move(values))
    {
    }

    std::vector<Value*> ArrayValue::toArray() const
    {
        std::vector<Value*> values;
        for (auto& valuePtr : mValues)
        {
            values.push_back(valuePtr.get());
        }
        return values;
    }
}