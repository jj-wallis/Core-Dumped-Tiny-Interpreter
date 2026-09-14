#include "tiny_interpreter.h"

// Called on the root node of a tree
bool Expression::is_assign() {
    if (type == operation && value == '=') {
        // Only accept left hand side assingment
        if (lhs->type == variable) {
            return true;
        }
    }
    return false;
}