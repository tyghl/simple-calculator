#include <iostream>
#include <stdexcept>
#include "token_stream.hpp"

Token_stream ts;

double expression();

double primary() {
  Token t = ts.get();
  switch (t.kind) {
  case '8':
    return t.val;
  case '(': {
    double eval = expression();
    t = ts.get();
    if (t.kind == ')') return eval;
    else throw std::runtime_error("parathesis unmatch");
  }
  default:
    throw std::runtime_error("primary");
  }
}

double term() {
  double left = primary();
  Token t = ts.get();
  while (true) {
    switch (t.kind) {
    case '*':
      left *= primary();
      break;
    case '/': {
      double d = primary();
      if (d == 0) throw std::runtime_error("devided by zero!");
      left /= d;
      break;
    }
    default:
      ts.putback(t);
      return left;
    }
    t = ts.get();
  }
}

double expression() {
  double left = term();
  Token t = ts.get();
  while (true) {
    switch (t.kind) {
    case '+':
      left += term();
      break;
    case '-':
      left -= term();
      break;
    default:
      ts.putback(t);
      return left;
    }
    t = ts.get();
  }
}

int main() {
  std::cout << "Welcome to our simple calculator." << std::endl;
  std::cout << "Please enter expression: (available: + - * /; ';' to show answer; 'q' to exit) " << std::endl;
  try {
    double ans = 0;
    while (std::cin) {
      Token t = ts.get();
      if (t.kind == 'q') break;  
      if (t.kind == ';') {
        std::cout << "=" << ans << std::endl;
        continue;
      } else
        ts.putback(t);
      ans = expression();
    }
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "exception\n";
    return 2;
  }
  return 0;
}