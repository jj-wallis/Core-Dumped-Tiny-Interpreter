#include <vector>
#include <string>
#include <memory>

enum Type {
    uninitialsed,
    atom, // A variable or an interger
    operation, // An operand
    bracket,
    EoF // End of line
};

struct Token {
    Type type;
    char value;
};

// A tree representing a parsed mathematical expression.
class Expression {
    public:
        Expression() { } 

        ~Expression() {
            delete lhs;
            delete rhs;
        }

        char value = '\0';
        Type type = uninitialsed;

        Expression* lhs = nullptr; // Sub expressions
        Expression* rhs = nullptr;
};

class Lexer {
    public:
        Lexer(const std::string &input); // Takes raw input from stdin, constructor calls the tokensier

        ~Lexer() {
            delete root;
        } 

        Expression* root; // This will be an operation with the lowest binding power
  
        Token next(); // Pops from the tokens vector
        Token peek() const; // Used to check the next token
        Expression* parse_expression(float binding_power); // Main logic

    private:
        std::vector<Token> tokens; // Stripped user input
 
        std::vector<Token> tokeniser(const std::string &input) const; // Strips user input
        float binding_power_of(char op) const; //  Dertermines operator precedence for operation grouping
};