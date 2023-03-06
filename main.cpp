/* Uno Pasadhika 
 * Shunting Yard - equation parse and output program thingy 
 * 3/2/2023 
*/

#include <iostream>
#include "Node.h"

using namespace std;

int main() {
  Queue s;
  for (char i = '0'; i <= '9'; i++) {
    Node n(i);
    cout << "Pushing " << i << "!\n";
    s.push(n);
  }
  cout << "Hi!\n";
  while (!s.empty()) {
    cout << "Popping " << s.peek().data << "!\n";
    s.pop();
  }
  return 0;
}
