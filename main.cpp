/* Uno Pasadhika
 * Shunting Yard - equation parse and output program thingy
 * 3/8/2023
*/

#include <iostream>
#include "Node.h"
#include "Utils.h"

using namespace std;

// Printing funcs are basically the same as the ones from https://en.wikipedia.org/wiki/Binary_expression_tree

// Print tree in infix 
void printInfix(Node* tree) {
  if (tree == nullptr) return;
  if (Utils::isOperator(tree->data)) cout << "( ";
  printInfix(tree->left);
  cout << tree->data << ' ';
  printInfix(tree->right);
  if (Utils::isOperator(tree->data)) cout << ") ";
}

// Print tree for postfix
void printPostfix(Node* tree) {
  if (tree == nullptr) return;
  printPostfix(tree->left);
  printPostfix(tree->right);
  cout << tree->data << ' ';
}

// Print tree in prefix 
void printPrefix(Node* tree) {
  if (tree == nullptr) return;
  cout << tree->data << ' ';
  printPrefix(tree->left);
  printPrefix(tree->right);
}

int main() {
  char rawExpression[100];
  cout << "Enter expression: ";
  cin.getline(rawExpression, 100);
  // Get postfix notation with shunting yard algorithm basically copied from https://en.wikipedia.org/wiki/Shunting_yard_algorithm
  char postfixOut[100];
  memset(postfixOut, 0x0, 100);
  int poi = 0;
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
  /* Print postfix 
  cout << "Postfix notation: ";
  for (int i = 0; i < poi; i++) {
    cout << postfixOut[i] << ' ';
  }
  cout << endl;
  */
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
 insaneLabel:
  cout << "Tree thingy done, enter print format (in, pre, post): ";
  char in[50];
  cin >> in;
  if (strcmp(in, "in") == 0) { // Infix
    printInfix(treetop);
  }
  else if (strcmp(in, "pre") == 0) { // Prefix
    // Actually traverse the tree for this one
    printPrefix(treetop);
  }
  else if (strcmp(in, "post") == 0) { // Postfix
    printPostfix(treetop);
  }
  else {
    cout << "Invalid input!\n";
    goto insaneLabel;
  }
  cout << endl;
  /*
  char* token = strtok(rawExpression, " ");
  while (token) {

    token = strtok(NULL, " ");
  }
  */
  return 0;
}
