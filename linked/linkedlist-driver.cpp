#include <iostream>
using namespace std;

#include "linkedlist.h"

//Testing function for LinkedList
//Checks that all forwards and backwards links point to each other
//Checks head->prev and tail->next are null
//Checks that tail and size are correct
void test_ll(LinkedList* ll)
{
  Node* n = ll->getHead();
  if (n != nullptr && n->prev() != nullptr)
    cout << "Bad head->prev pointer" << endl;
  for (int i = 0; i < ll->getSize() - 1; i++)
  {
    if (n == nullptr || n->next() == nullptr)
      cout << "Null forward link";
    if (n->next()->prev() != n)
      cout << "Forwards and backwards links " << i << " don't match" << endl;
    n = n->next();
  }
  if (n != nullptr && n->next() != nullptr)
    cout << "Bad terminal pointer" << endl;
  if (ll->getTail() != n)
    cout << "Bad tail pointer" << endl;
  cout << "Link test complete" << endl;
}

//Insertion operator overload for LinkedList
//Outputs all ints as space-separated list, with size
ostream& operator<<(ostream& out, const LinkedList* ll)
{
  if (ll->empty())
    return out << "empty";

  const Node* n = ll->getHead();
  while (n != nullptr)
  {
    out << n->value() << ' ';
    n = n->next();
  }
  return out << "(size " << ll->getSize() << ')';
}

int main()
{
  LinkedList* ll;
  LinkedList* copy = nullptr;

  //Test insert
  ll = new LinkedList();
  cout << "Initially:  " << (ll->empty()? "empty":"not empty") << endl;

  cout << "Inserting 1-5:  ";
  for (int i = 0; i < 5; i++)
    ll->insert(i+1, i);
  cout << ll << endl;
  test_ll(ll);

  cout << "Inserting alternating zeros:  ";
  for (int i = 0; i <= 5; i++)
    ll->insert(0, 5-i);
  cout << ll << endl;
  test_ll(ll);

  //* Test remove
  cout << "Remove last element: ";
  ll->remove(ll->getSize()-1);
  cout << ll << endl;
  test_ll(ll);

  cout << "Remove first element: ";
  ll->remove(0);
  cout << ll << endl;
  test_ll(ll);

  cout << "Remove third element: ";
  ll->remove(2);
  cout << ll << endl;
  test_ll(ll);

  //* Test removing all elements
  cout << "Before removing last element:  ";
  while (ll->getSize() > 1)
    ll->remove(0);
  cout << ll << endl;
  test_ll(ll);

  cout << "After removing last element:  ";
  ll->remove(0);
  cout << ll << endl;
  test_ll(ll);

  cout << "After adding new element:  ";
  ll->insert(1000, 0);
  cout << ll << endl;
  test_ll(ll);

  //* Test copy constructor
  copy = new LinkedList(*ll);
  cout << "Made a copy:  " << copy << endl;
  test_ll(copy);

  for (int i = 1001; i < 1006; i++)
    ll->insert(i, ll->getSize());
  copy->insert(-1, 1);
  cout << "Adding 1001..1005 to original and -1 to copy:  " 
       << ll << " vs. " << copy << endl;
  
  //* Test copy assignment
  *copy = *ll;
  cout << "Assigning copy = original:  " << ll << " vs. " << copy << endl;
  test_ll(copy);
  for (int i = 1; i < 4; i++)
    ll->insert(i, ll->getSize());
  copy->insert(-1, copy->getSize());
  cout << "Adding 1..3 to original and -1 to copy:  " << ll << " vs. " << copy << endl;
  //*/

  delete ll;
  delete copy;
  return 0;
}