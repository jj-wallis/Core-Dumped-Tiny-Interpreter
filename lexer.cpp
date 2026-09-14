#include "tiny_interpreter.h"
#include <climits>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>

// Constructor
Lexer::Lexer(const std::string &input) {
    this->tokens = tokeniser(input);
};

// Take a line of standard in and store it as a vector of tokens
std::vector<Token> Lexer::tokeniser(const std::string &input) const {
    std::vector<Token> tokens;
    tokens.reserve(input.size()); // Preallocate size
    int bracket_depth = 0;

    for (char c : input) {

        // Filter for whitespace
        if (std::isspace(c)) {
            continue;
        }

        Token token;
        token.value = c;

        // Check for variables and numbers
        if (std::isalpha(c)) {
            token.type = variable;
        }

        if (std::isdigit(c)) {
            token.type = integer;
        }

        // Check for specifics
        else {
            switch (c) {
                 case '=': case '+': case '-': case '*': case '/':
                    token.type = operation;
                    break; 
                case '(': case ')':
                    token.type = bracket;
                    break;
                default:
                    throw std::runtime_error(std::string("Lexer error: Invalid character encountered: '") + c + "'");
            }
        }
        tokens.push_back(token);
    }

    std::reverse(tokens.begin(), tokens.end()); // Reverse the vector so we can pop elements

    return tokens;
}

// Returns the next token in the equation
Token Lexer::next() {
    Token t = tokens.back();
    tokens.pop_back();
    return t;
}

// Checks the next token in the equation
Token Lexer::peek() const {
    if (tokens.empty()) { 
        return Token{EoF, '\0'};
    }
    
    return tokens.back();
}