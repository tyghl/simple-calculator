#include <iostream>
#include "token.hpp"

class Token_stream {
public:
    Token get() {
        if (full) {
            full = false;
            return buffer;
        }
        char ch;
        std::cin >> ch;
        switch (ch) {
        case ';':
        case 'q':
        case '(':case ')':case '+':case '-':case '*':case '/':
            return Token{ch};
        case '.':
        case '0':case '1':case '2':case '3':case '4':
        case '5':case '6':case '7':case '8':case '9':
        {
            std::cin.putback(ch);
            double val;
            std::cin >> val;
            return Token{'8', val};
        }
        default:
            throw std::runtime_error("Bad token");
        }
    }

    void putback(Token t) {
        if (full) throw std::runtime_error("putback into a full buffer");
        buffer = t;
        full = true;
    }
private:
    bool full{false};
    Token buffer;
};