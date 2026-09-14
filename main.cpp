#include <iostream>
#include <string>
#include <climits>
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

    while (1) {
        // Wait for text input
        std::string input;
        
        // Get entire line of input
        if (!std::getline(std::cin, input)) {
            break; // Exit if EOF
        }

        // Create a new lexer on the stack
        Lexer lexer(input);
        lexer.root = lexer.parse_expression(INT_MIN); // Start with a binding power lower than any defined
        
        std::cout << "Test" << "\n";

        break;
    }
}

int main () {
    runtime_loop();
    return 0;
}