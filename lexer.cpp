#include "tiny_interpreter.h"
#include <climits>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <memory> // !!! Need to add unique pointers

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
        if (std::isalpha(c) || std::isdigit(c)) {
            token.type = atom;
            tokens.push_back(token);
        }

        // Check for specifics
        else {
            switch (c) {
                case '+': case '-': case '*': case '/':
                    token.type = operation;
                    break; 
                case '(': case ')':
                    token.type = bracket;
                    break;
                default:
                    throw std::runtime_error(std::string("Lexer error: Invalid character encountered: '") + c + "'");
            }
            tokens.push_back(token);
        }
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

// Checks binding power of an operator
float Lexer::binding_power_of(char op) const {

    float binding_power = 0.0;

    // One operator has slighty higher bindng power for derterminism
    switch(op) 
    {
        case '+': 
            binding_power = 1.0; break;
        case '-':
            binding_power = 1.1; break;
        case '*':
            binding_power = 2.0; break;
        case '/':
            binding_power = 2.1; break;
        default:
            throw std::runtime_error(std::string("No binding power defined for: '") + op + "'");
    }

    return binding_power;
}

// Orders tokens into a tree structure for operator grouping
// Currently works under the assumption that tokens alternate between atoms and operations
Expression* Lexer::parse_expression(float current_binding_power) {

    Token next = Lexer::next(); // Get the next token
    Expression* lhs = nullptr; // Declare on stack

    // If the first expression is a bracket, immediately recurse
    if (next.value == '(') {
        lhs = parse_expression(INT_MIN);
    } 

    else {
        // The first expression is expected an atom
        lhs = new Expression();   
        lhs->type = next.type;
        lhs->value = next.value;
    }

// !!!  // We need some check for invalid expression ordering

    // Check if there are more tokens to parse
    next = Lexer::peek(); // As the last token was an atom, we expect the next token to be an operator (or bracket)
    while (next.type != EoF) {

        if (next.value == ')') { 
            Lexer::next(); // Call lexer next to remove the closing bracket
            break;
        }

        // A new operator with a higher binding power starts a new op node, moving the current tree to the left and recurisng on the right
        if (binding_power_of(next.value) > current_binding_power)
        {
            Expression* op = new Expression();
            next = Lexer::next();
            op->type = next.type;
            op->value = next.value;

            // The current working expression becomes the lhs
            op->lhs = lhs;
            op->rhs = parse_expression(binding_power_of(op->value));

            next = Lexer::peek(); // Update the value of next

            lhs = op;
        }

        else {
            // Lower binding power breaks the recursion, returning this sub tree
            break;
        }
    }

    return lhs;
}