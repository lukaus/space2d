#include "node.h"
#include "nodelist.h"

Node NodeList::operator[](int idx)
{
    Node * cur = head;
    for(int i = 0; i < idx; i++)
    {
        cur = cur->next;
    }   
    return *cur;
}

void NodeList::AddNode(long double mass)
{
    Node* newNode = new Node();
    newNode->particle->mass = mass;

    if(head == nullptr)
    {
        head = newNode;
        head->next = nullptr;
        head->last = nullptr;
    }
    else
    {
        Node * cur = head;
        while (cur->next != nullptr)
            cur = cur->next;
        cur->next = newNode;

        newNode->last = cur;
        newNode->next = nullptr;
    }
    count++;
}
