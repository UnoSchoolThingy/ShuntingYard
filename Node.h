#include <cstring>

// This entire system totally sucks because it's copying the node a bunch of times but performance shouldn't really matter that much for this program so it's probably fine 

struct Node {
  char data;
  Node* left;
  Node* right;

  Node() {
    memset(this, 0x0, sizeof(Node));
  }
  
  Node(char c) {
    data = c;
    left = nullptr;
    right = nullptr;
  }
};

struct NodeListElement { 
  Node n;
  NodeListElement* prev;
  NodeListElement* next;

  NodeListElement() {
    memset(this, 0x0, sizeof(NodeListElement));
  }

  NodeListElement(Node n) {
    this->n = n;
    prev = nullptr;
    next = nullptr;
  }
};

struct Stack {
  NodeListElement* top;

  Stack() {
    memset(this, 0x0, sizeof(Stack));
  }

  bool empty() {
    return top == nullptr;
  }

  void push(Node nodeToAdd) {
    NodeListElement* add = new NodeListElement(nodeToAdd);
    NodeListElement* old = top;
    top = add;
    if (old == nullptr) return;
    top->next = old;
  }

  void pop() {
    NodeListElement* next = top->next;
    delete top;
    top = next;
  };

  Node peek() {
    return top->n;
  }
};

struct Queue {
  NodeListElement* start;
  NodeListElement* end;

  Queue() {
    memset(this, 0x0, sizeof(Queue));
  }

  bool empty() {
    return start == nullptr;
  }

  void push(Node nodeToAdd) {
    NodeListElement* add = new NodeListElement(nodeToAdd);
    NodeListElement* old = start;
    start = add;
    add->next = old;
    if (old == nullptr) end = start;
    else old->prev = add;
  }

  void pop() {
    if (end == nullptr) return;
    NodeListElement* old = end;
    if (end->prev != nullptr) end = end->prev;
    else memset(this, 0x0, sizeof(Queue));
    delete old;
  };

  Node peek() {
    return end->n;
  }
};

/* bad queue thingy with linear insert because brain no worky 
struct Queue {
  NodeListElement* start;

  Queue() {
    memset(this, 0x0, sizeof(Queue));
  }

  bool empty() {
    return start == nullptr;
  }

  void push(Node nodeToAdd) {
    NodeListElement* add = new NodeListElement(nodeToAdd);
    if (start == nullptr) {
      start = add;
      return;
    }
    NodeListElement* prev = start;
    NodeListElement* curr = start->next;
    while (curr != nullptr) {
      prev = curr;
      curr = curr->next;
    }
    prev->next = add;
  }

  void pop() {
    NodeListElement* next = start->next;
    delete start;
    start = next;
  };

  Node peek() {
    return start->n;
  }
};
*/
