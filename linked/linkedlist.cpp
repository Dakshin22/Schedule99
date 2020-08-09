#include "linkedlist.h"
#include <exception>
#include <iostream>
using namespace std;

Node* LinkedList::getNode(int n)
{ 
  Node* ret = head;
  for (int i = 0; i < n && ret; i++)
    ret = ret->next();
  return ret;
}

const Node* LinkedList::getNode(int n) const
{
  const Node* ret = head;
  for (int i = 0; i < n && ret; i++)
    ret = ret->next();
  return ret;
}

//Add a node with value x at position pos
//pos may be between 0 and size, inclusive
void LinkedList::insert(int x, int pos)
{
  if (pos < 0 || pos > size)
    return;

  Node* insert = new Node(x);
  if (head == nullptr)
  {
    head = tail = insert;
  }
  else if (pos == 0)
  {
    head->setPrev(insert);
    insert->setNext(head);
    head = insert;
  }
  else if (pos == size)
  {
    tail->setNext(insert);
    insert->setPrev(tail);
    tail = insert;
  }
  else
  {
    Node* before = getNode(pos - 1);
    Node* after = before->next();
    before->setNext(insert);
    insert->setPrev(before);
    insert->setNext(after);
    after->setPrev(insert);
  }
  size++;
}

//Remove the node at position pos
//pos may be between 0 and size - 1
void LinkedList::remove(int pos)
{
  if (pos < 0 || pos >= size)
    return;
  
  Node* victim = getNode(pos);

  if (size == 1)
  {
    delete head;
    head = tail = nullptr;
  }
  else if (head == victim)
  {
    head = victim->next();
    delete victim;
    head->setPrev(nullptr);
  }
  else if (victim == tail)
  {
    tail = victim->prev();
    delete victim;
    tail->setNext(nullptr);
  }
  else
  {
    Node* before = victim->prev();
    Node* after = victim->next();
    before->setNext(after);
    after->setPrev(before);
    delete victim;
  }
  size--;
  
}

//Destroys the linked list
LinkedList::~LinkedList()
{
  Node* temp;
  while (head != nullptr)
  {
    temp = head;
    head = head->next();
    cout << "Deleting " << temp->value() << endl;
    delete temp;
  }
}

//Constructs a copy of the argument
LinkedList::LinkedList(const LinkedList& copy)
{
  head = tail = nullptr;
  size = copy.size;

  const Node* temp;
  Node* node;
  temp = copy.head;
  while (temp != nullptr)
  {
    node = new Node(temp->value());
    if (head == nullptr)
      head = node;
    else
    {
      tail->setNext(node);
      node->setPrev(tail);
    }
    tail = node;
    temp = temp->next();
  }
}

//Makes this list into a copy of the RHS
const LinkedList& LinkedList::operator=(const LinkedList& copy)
{
  //Copy assignment:  delete existing, then make a copy
  //Could be made more efficient by changing values and either
  // extending or shortening existing list, but much harder to implement!

  if (&copy == this)
    return copy;
  
  Node* node;
  const Node* temp;
  while (head != nullptr)
  {
    node = head;
    head = head->next();
    delete node;
  }
  head = tail = nullptr;
  size = copy.size;

  temp = copy.head;
  while (temp != nullptr)
  {
    node = new Node(temp->value());
    if (head == nullptr)
      head = node;
    else
    {
      tail->setNext(node);
      node->setPrev(tail);
    }
    tail = node;
    temp = temp->next();
  }
  return copy;
}