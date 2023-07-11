#include "../inc/ParenthesesMatch.h"


bool parenthesesMatch(const char* str){
    Stack<char> charStack;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '(') {
            charStack.push('(');
        }
        if (str[i] == ')') {
            charStack.pop();
        }
        i++;
    }
    if (charStack.empty()) { return true; }
    else { return false; }

}
