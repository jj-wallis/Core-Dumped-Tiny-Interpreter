#include <iostream>
#include <string>
#include <climits>
#include <unordered_map>
#include "tiny_interpreter.h"

/*
    Pratt Parser

    BIDMAS

    Known Limitations:
        -> Handles only infix operations
        -> Prefixes and suffixes are out of scope

        -> Does not handle double digit numbers
*/


// Main Runtime Loop
void runtime_loop() {

    Parser parser;
    std::unordered_map<char,float> variables;

    while (1) {
        // Wait for text input
        std::string input;
        
        // Get entire line of input
        if (!std::getline(std::cin, input)) {
            break; // Exit if EOF
        }

        // Exit
        if (input == "exit") {
            break;
        }

        // Create a new lexer on the stack
        Lexer lexer(input);
        Expression* root = parser.parse_expression(lexer, INT_MIN); 

        // Check if the expression was an assignment
        if (root->is_assignment()) {
            variables[root->lhs->value] = root->rhs->evaluate(variables, root->rhs);
        } 

        else {
            std::cout << root->evaluate(variables, root) << "\n";
        }
    }
}

int main () {
    std::cout << "Type 'exit' to quit\n";
    runtime_loop();
    return 0;
}