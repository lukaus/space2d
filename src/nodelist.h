#ifndef NODELIST_H
#define NODELIST_H

#include "node.h"

class Node;
class NodeList
{
  public:
      Node* head = nullptr;
      int count = 0;

      Node operator[](int idx);
      void AddNode(long double mass = 1.0);

  private:

};
#endif
