#include "tiny_interpreter.h"
#include <stdexcept>

// Called on the root node of a tree
bool Expression::is_assignment() {
    if (type == operation && value == '=') {
        // Only accept left hand side assingment
        if (lhs->type == variable) {
            return true;
        }
    }
    return false;
}

// Recursive evaluation operation
float Expression::evaluate(std::unordered_map<char,float>& variables, Expression* node) {

    if (node->type == digit) {
        return node->value - '0';
    }

    else if (node->type == variable) {
        return variables[node->value];
    }

    else if (node->type == operation){
        switch(node->value) 
            {
                case '+': 
                    return evaluate(variables, node->lhs) + evaluate(variables, node->rhs);
                case '-':
                    return evaluate(variables, node->lhs) - evaluate(variables, node->rhs);
                case '*':
                    return evaluate(variables, node->lhs) * evaluate(variables, node->rhs);
                case '/':
                    return evaluate(variables, node->lhs) / evaluate(variables, node->rhs);
                default:
                    throw std::runtime_error("Error during evaluation");
            }
    }

    return 0;
}