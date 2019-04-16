#include "node.h"
#include "nodelist.h"
#include <vector>

Node NodeList::operator[](int idx)
{
    Node * cur = head;
    for(int i = 0; i < idx; i++)
    {
        cur = cur->next;
    }   
    return *cur;
}
bool NodeList::AddNode(std::vector<std::string> part)
{
    Node* newNode = new Node();
    if(part.size() > 3)
    {
        newNode->particle->name = part[0];
        newNode->SetPos(stof(part[1]), stof(part[2]));
        newNode->particle->mass = stof(part[3]);

        if(part.size() > 4)
        {
            // x_vel
            newNode->particle->x_vel =stof(part[4]);
        }

        if(part.size() > 5)
        {
            // y_vel
            newNode->particle->y_vel =stof(part[5]);
        }

        if(part.size() > 6)
        {
            // particle radius
            newNode->pix->setRadius(stof(part[6]));
        }

        if(part.size() > 9)
        {
            // particle color (6, 7, 8)
            newNode->SetColor(stoi(part[7]), stoi(part[8]), stoi(part[9]));
        }

        if(part.size() > 10)
        {
            // trail radius
            newNode->trailRadius = stof(part[10]);
        }

        if(part.size() == 14)
        {
            // trail color 
            newNode->SetTrailColor(stoi(part[11]), stoi(part[12]), stoi(part[13]));
        }
        return AddNode(newNode);
    }
    else
        return false;
}

bool NodeList::AddNode(long double mass)
{
    Node* newNode = new Node();
    newNode->particle->mass = mass;
    return AddNode(newNode);
}

bool NodeList::AddNode(Node* newNode)
{
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
    return true;
}
