#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

class Node
{
private:
  int data;
  Node* nextPtr;
  Node* prevPtr;
public:
  Node(int x) { data = x; prevPtr = nextPtr = nullptr; }
  int& value() { return data; }
  int value() const { return data; }
  Node* next() { return nextPtr; }
  const Node* next() const { return nextPtr; }
  Node* prev() { return prevPtr; }
  const Node* prev() const { return prevPtr; }
  void setNext(Node* n) { nextPtr = n; }
  void setPrev(Node* p) { prevPtr = p; }
  bool hasPrev() const { return prevPtr != nullptr; }
  bool hasNext() const { return nextPtr != nullptr; }
};

class LinkedList
{
private:
  Node* head;
  Node* tail;
  int size;
public:
  LinkedList() { head = tail = nullptr; size = 0; }
  bool empty() const { return size == 0; }
  int getSize() const { return size; }
  Node* getHead() { return head; }
  const Node* getHead() const { return head; }
  Node* getTail() { return tail; }
  const Node* getTail() const { return tail; }
  Node* getNode(int pos);
  const Node* getNode(int pos) const;
  void insert(int data, int pos);
  void remove(int pos);
  ~LinkedList();
  LinkedList(const LinkedList&);
  const LinkedList& operator=(const LinkedList&);
};

#endif //__LINKEDLIST_H