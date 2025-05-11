// Copyright 2025 solar-mist

#ifndef VTOML_VALUE_H
#define VTOML_VALUE_H 1

#include <stdexcept>
#include <memory>
#include <string>
#include <vector>

namespace toml
{
    class Value
    {
    public:
        virtual ~Value() = default;

        virtual std::string toString() const
        {
            throw std::runtime_error("Value is not a string");
        }

        virtual std::vector<Value*> toArray() const
        {
            throw std::runtime_error("Value is not an array");
        }

        virtual bool isString() const { return false; }
        virtual bool isArray() const { return false; }
    };
    using ValuePtr = std::unique_ptr<Value>;

    class StringValue : public Value
    {
    public:
        StringValue(std::string value);

        std::string toString() const override;

        bool isString() const override { return true; }

    private:
        std::string mValue;
    };
    using StringValuePtr = std::unique_ptr<StringValue>;

    class ArrayValue : public Value
    {
    public:
        ArrayValue(std::vector<ValuePtr> values);

        std::vector<Value*> toArray() const override;

        bool isArray() const override { return true; }

    private:
        std::vector<ValuePtr> mValues;
    };
    using ArrayValuePtr = std::unique_ptr<ArrayValue>;
}

#endif // VTOML_VALUE_H