#include "tiny_interpreter.h"
#include <stdexcept>

// Recursive evaluation operation
float Interpreter::evaluate(std::unordered_map<char,float>& variables, Expression* node) {

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