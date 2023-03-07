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
  // Get postfix notation with shunting yard algorithm basically copied from https://en.wikipedia.org/wiki/Shunting_yard_algorithm
  char postfixOut[100];
  memset(postfixOut, 0x0, 100);
  int poi = 0;
  cout << "Postfix notation: ";
  Stack<char> opStack;
  int inputLen = strlen(rawExpression);
  while (rawExpression[inputLen - 1] == ' ') inputLen--;
  for (int i = 0; i < inputLen; i += 2) {
    char c = rawExpression[i];
    if (isdigit(c)) postfixOut[poi++] = c;
    else if (Utils::isOperator(c)) {
      while (!opStack.empty() && opStack.top() != '(') {
        int o1p = Utils::getOperatorPrecedence(c);
        int o2p = Utils::getOperatorPrecedence(opStack.top());
        if (o2p > o1p || (o1p == o2p && c != '^')) { // Carat is right associative, o1 has to be left associative if o1p == o2p
	  postfixOut[poi++] = opStack.top();
          opStack.pop();
        }
        else break;
      }
      opStack.push(c);
    }
    else if (c == '(') opStack.push(c);
    else if (c == ')') {
      while (opStack.top() != '(') {
	postfixOut[poi++] = opStack.top();
        opStack.pop();
      }
      opStack.pop();
    }
  }
  while (!opStack.empty()) {
    postfixOut[poi++] = opStack.top();    
    opStack.pop();
  }
  for (int i = 0; i < poi; i++) {
    cout << postfixOut[i] << ' ';
  }
  cout << endl;
  // We have the postfix queue, time to construct the binary expression tree
  Stack<Node*> stk;
  for (int i = 0; i < poi; i++) {
    if (isdigit(postfixOut[i])) {
      stk.push(new Node(postfixOut[i]));
      continue;
    }
    // We are now dealing with an operator
    Node* t1 = stk.top();
    stk.pop();
    Node* t2 = stk.top();
    stk.pop();
    Node* epicNode = new Node(postfixOut[i]);
    epicNode->left = t2;
    epicNode->right = t1;
    stk.push(epicNode);
  }
  Node* treetop = stk.top(); // The very tippy top of the tree! 
  stk.pop();

  /*
  char* token = strtok(rawExpression, " ");
  while (token) {

    token = strtok(NULL, " ");
  }
  */
  return 0;
}
