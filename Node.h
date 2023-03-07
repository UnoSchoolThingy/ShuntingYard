#include <cstring>

// Kind of bad implementation but it works 

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

template <typename T>
struct ListElement { 
  T n;
  ListElement<T>* prev;
  ListElement<T>* next;

  ListElement() {
    memset(this, 0x0, sizeof(ListElement<T>));
  }

  ListElement(T n) {
    this->n = n;
    prev = nullptr;
    next = nullptr;
  }
};

template <typename T>
struct Stack {
  ListElement<T>* topField;

  Stack() {
    memset(this, 0x0, sizeof(Stack));
  }

  bool empty() {
    return topField == nullptr;
  }

  void push(T nodeToAdd) {
    ListElement<T>* add = new ListElement(nodeToAdd);
    ListElement<T>* old = topField;
    topField = add;
    if (old == nullptr) return;
    topField->next = old;
  }

  void pop() {
    ListElement<T>* next = topField->next;
    delete topField;
    topField = next;
  };

  // Peek function but renamed 
  T top() {
    return topField->n;
  }
};

template <typename T>
struct Queue {
  ListElement<T>* start;
  ListElement<T>* end;

  Queue() {
    memset(this, 0x0, sizeof(Queue));
  }

  bool empty() {
    return start == nullptr;
  }

  // Enqueue 
  void push(T nodeToAdd) {
    ListElement<T>* add = new ListElement(nodeToAdd);
    ListElement<T>* old = start;
    start = add;
    add->next = old;
    if (old == nullptr) end = start;
    else old->prev = add;
  }

  // Dequeue 
  void pop() {
    if (end == nullptr) return;
    ListElement<T>* old = end;
    if (end->prev != nullptr) end = end->prev;
    else memset(this, 0x0, sizeof(Queue));
    delete old;
  };

  T front() {
    return end->n;
  }
};

/* bad queue thingy with linear insert because brain no worky 
struct Queue {
  ListElement* start;

  Queue() {
    memset(this, 0x0, sizeof(Queue));
  }

  bool empty() {
    return start == nullptr;
  }

  void push(Node nodeToAdd) {
    ListElement* add = new ListElement(nodeToAdd);
    if (start == nullptr) {
      start = add;
      return;
    }
    ListElement* prev = start;
    ListElement* curr = start->next;
    while (curr != nullptr) {
      prev = curr;
      curr = curr->next;
    }
    prev->next = add;
  }

  void pop() {
    ListElement* next = start->next;
    delete start;
    start = next;
  };

  Node peek() {
    return start->n;
  }
};
*/
