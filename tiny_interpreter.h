#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

enum Type {
    uninitialsed,
    digit,
    variable,
    operation, // An operand
    bracket,
    EoF // End of line
};

struct Token {
    Type type;
    char value;
};

// A tree node representing a parsed mathematical expression.
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

        bool is_assignment();
        float evaluate(std::unordered_map<char,float>& variables, Expression * node);
};

class Lexer {
    public:
        Lexer(const std::string &input);

        Token next(); // Pops from the tokens vector
        Token peek() const; // Used to check the next token

    private:  
        std::vector<Token> tokens; // Stripped user input
        std::vector<Token> tokeniser(const std::string &input) const; // Strips user input
};

//
class Parser
{
    public:
        Parser() { }

        Expression* parse_expression(Lexer& lexer, float binding_power);

    private:
        float binding_power_of(char op) const;
};