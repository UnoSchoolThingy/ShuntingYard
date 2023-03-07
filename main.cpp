/* Uno Pasadhika 
 * Shunting Yard - equation parse and output program thingy 
 * 3/2/2023 
*/

#include <iostream>
#include "Node.h"
#include "Utils.h"

using namespace std;

int main() {
  char rawExpression[100];
  cout << "Enter expression: ";
  cin.getline(rawExpression, 100);
  // Print postfix notation with shunting yard algorithm basically copied from https://en.wikipedia.org/wiki/Shunting_yard_algorithm 
  cout << "Postfix notation: ";
  Stack<char> opStack;
  int inputLen = strlen(rawExpression);
  while (rawExpression[inputLen - 1] == ' ') inputLen--;
  for (int i = 0; i < inputLen; i += 2) {
    char c = rawExpression[i];
    if (isdigit(c)) cout << c << ' ';
    else if (Utils::isOperator(c)) {
      while (!opStack.empty() && opStack.top() != '(') {
	int o1p = Utils::getOperatorPrecedence(c);
	int o2p = Utils::getOperatorPrecedence(opStack.top());
	if (o2p > o1p || (o1p == o2p && c != '^')) { // Carat is right associative, o1 has to be left associative if o1p == o2p 
	  cout << opStack.top() << ' ';
	  opStack.pop();
	}
	else break;
      }
      opStack.push(c);
    }
    else if (c == '(') opStack.push(c);
    else if (c == ')') {
      while (opStack.top() != '(') {
	cout << opStack.top() << ' ';
	opStack.pop();
      }
      opStack.pop();
    }
  }
  while (!opStack.empty()) {
    cout << opStack.top() << ' ';
    opStack.pop();
  }
  cout << endl;
  // We've printed the postfix notation, now we can construct the expression tree 
  /*
  char* token = strtok(rawExpression, " ");
  while (token) {
    
    token = strtok(NULL, " ");
  }
  */
  return 0;
}
