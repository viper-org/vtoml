// Copyright 2025 solar-mist

#ifndef VTOML_PARSER_H
#define VTOML_PARSER_H 1

#include "vtoml/lexer/Token.h"

#include "vtoml/Value.h"

#include <filesystem>
#include <vector>
#include <unordered_map>

namespace toml
{
    std::unordered_map<std::string, ValuePtr> ParseFile(const std::filesystem::path& filePath);

    class Parser
    {
    public:
        Parser(std::vector<lexer::Token> tokens);

        void parse();

        std::unordered_map<std::string, ValuePtr> getTable();

    private:
        std::vector<lexer::Token> mTokens;
        int mPosition;

        std::unordered_map<std::string, ValuePtr > mTable;

        lexer::Token current() const;
        lexer::Token consume();
        lexer::Token peek(int offset) const;

        void expectToken(lexer::TokenType tokenType);

        void parseKeyValue();

        ValuePtr parseValue();
        StringValuePtr parseStringValue();
        ArrayValuePtr parseArrayValue();
    };
}

#endif // VTOML_PARSER_H