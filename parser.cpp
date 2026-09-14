#include "tiny_interpreter.h"
#include <climits>
#include <stdexcept>

// Checks binding power of an operator
float Parser::binding_power_of(char op) const {

    float binding_power = 0.0;

    // One operator has slighty higher bindng power for derterminism
    switch(op) 
    {
        case '=':
            binding_power = 0.1; break;
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

    // ^ and sqrt operators to exist with 3.? binding power

    return binding_power;
}

// Orders tokens into a tree structure for operator grouping
// Currently works under the assumption that tokens alternate between atoms and operations
Expression* Parser::parse_expression(Lexer& lexer, float current_binding_power) {

    Token next = lexer.next(); // Get the next token
    Expression* lhs = nullptr; // Declare on stack

    // If the first expression is a bracket, immediately recurse
    if (next.value == '(') {
        lhs = parse_expression(lexer, INT_MIN);
    } 

    else {
        // The first expression is expected an atom
        lhs = new Expression();   
        lhs->type = next.type;
        lhs->value = next.value;
    }

// !!!  // We need some check for invalid expression ordering

    // Check if there are more tokens to parse
    next = lexer.peek(); // As the last token was an atom, we expect the next token to be an operator (or bracket)
    while (next.type != EoF) {

        if (next.value == ')') { 
            lexer.next(); // Call lexer next to remove the closing bracket
            break;
        }

        // A new operator with a higher binding power starts a new op node, moving the current tree to the left and recurisng on the right
        if (binding_power_of(next.value) > current_binding_power)
        {
            Expression* op = new Expression();
            next = lexer.next();
            op->type = next.type;
            op->value = next.value;

            // The current working expression becomes the lhs
            op->lhs = lhs;
            op->rhs = parse_expression(lexer, binding_power_of(op->value));

            next = lexer.peek(); // Update the value of next

            lhs = op;
        }

        else {
            // Lower binding power breaks the recursion, returning this sub tree
            break;
        }
    }

    return lhs;
}