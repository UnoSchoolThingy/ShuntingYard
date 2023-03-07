#pragma once

#include <cstring>
#include <math.h>

// Utilities and stuff
struct Utils {
  static bool isOperator(char c) {
    return (c == '*' || c == '/' || c == '+' || c == '-' || c == '^'); 
  }

  static int getOperatorPrecedence(char c) {
    if (c == '^') return 4;
    if (c == '*' || c == '/') return 3;
    return 2;
  }
};
