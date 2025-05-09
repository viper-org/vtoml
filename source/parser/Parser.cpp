// Copyright 2025 solar-mist

#include "vtoml/parser/Parser.h"

#include "vtoml/lexer/Lexer.h"

#include <fstream>
#include <sstream>

namespace toml
{
    std::unordered_map<std::string, ValuePtr> ParseFile(const std::filesystem::path& filePath)
    {
        std::ifstream file(filePath);

        std::stringstream buf;
        buf << file.rdbuf();
        std::string text = std::move(buf).str();

        lexer::Lexer lexer(text, filePath.string());
        auto tokens = lexer.lex();

        Parser parser(std::move(tokens));
        parser.parse();

        return parser.getTable();
    }

    
    Parser::Parser(std::vector<lexer::Token> tokens)
        : mTokens(std::move(tokens)), mPosition(0)
    {
    }

    void Parser::parse()
    {
        while (mPosition < mTokens.size())
        {
            if (current().getTokenType() == lexer::TokenType::EndOfFile)
            {
                break;
            }
            parseKeyValue();
        }
    }

    std::unordered_map<std::string, ValuePtr> Parser::getTable()
    {
        return std::move(mTable);
    }


    lexer::Token Parser::current() const
    {
        return mTokens[mPosition];
    }

    lexer::Token Parser::consume()
    {
        return mTokens[mPosition++];
    }

    lexer::Token Parser::peek(int offset) const
    {
        return mTokens[mPosition + offset];
    }

    void Parser::expectToken(lexer::TokenType tokenType)
    {
        if (current().getTokenType() != tokenType)
        {
            // TODO: Proper errors
            throw std::runtime_error("Unexpected token");
        }
    }


    void Parser::parseKeyValue()
    {
        expectToken(lexer::TokenType::Identifier);
        std::string key(consume().getText());

        expectToken(lexer::TokenType::Equal);
        consume();

        auto value = parseValue();

        mTable[key] = std::move(value);
    }

    ValuePtr Parser::parseValue()
    {
        switch (current().getTokenType())
        {
            case lexer::TokenType::StringLiteral:
                return parseStringValue();
            
            // TODO: Other value types

            default:
                expectToken(lexer::TokenType::StringLiteral);
        }
        return nullptr; // Unreachable
    }

    StringValuePtr Parser::parseStringValue()
    {
        std::string value(consume().getText());

        return std::make_unique<StringValue>(std::move(value));
    }
}