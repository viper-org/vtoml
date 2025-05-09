// Copyright 2025 solar-mist

#ifndef VTOML_VALUE_H
#define VTOML_VALUE_H 1

#include <memory>
#include <string>

namespace toml
{
    class Value
    {
    public:
        virtual ~Value() = default;

        virtual std::string toString() const = 0;
    };
    using ValuePtr = std::unique_ptr<Value>;

    class StringValue : public Value
    {
    public:
        StringValue(std::string value);

        std::string toString() const override;

    private:
        std::string mValue;
    };
    using StringValuePtr = std::unique_ptr<StringValue>;
}

#endif // VTOML_VALUE_H