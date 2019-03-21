#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "particle.h"

using namespace std;

class Node
{
    public:
    Particle* particle;
    sf::RectangleShape pix;
    
    Node()
    {
        pix.setSize(sf::Vector2f(1,1));
    }

    void SetColor(int r, int g, int b, int a=255)
    {
        pix.setFillColor(sf::Color(r,g,b,a));
    }

    void SetPos(int x, int y)
    {
        particle->x = x;
        particle->y = y;
        pix.setPosition(sf::Vector2f((float)x,(float)y));
    }

    Node* next = nullptr;
    Node* last = nullptr;
};

int nodeCount = 0;
Node* head;
Node* tail;

void AddNode()
{
    Node* newNode = new Node();
    newNode->particle = new Particle();

    if(head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->last = tail;
        newNode->next = nullptr;

        tail = newNode;
    }
    nodeCount++;
}
void Simulate();

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Space2d v0.0");
    window.setFramerateLimit(60);
    AddNode();
    head->particle = new Particle();
    head->pix.setFillColor(sf::Color::Green);
    head->SetColor(255,255,255);
    head->SetPos(499,499);

    while (window.isOpen())
    {
        Simulate();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type ==sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        window.clear();
        Node* cur = head;
        for(int i = 0; i < nodeCount; i++)
        {   
            window.draw(cur->pix);
            cur = cur->next;
        }      

        window.display();
    }

    return 0;
}

// Distance between two points
float dist(Node* a, Node* b)
{
    return sqrt( pow(b->particle->x - a->particle->x, 2) + pow(b->particle->y - a->particle->y, 2));
}

// Angle relative x-axis between two points(in rads)
float angle(Node* a, Node* b)
{
    return atan2(b->particle->y - a->particle->y, b->particle->x - a->particle->x );
}


void Simulate()
{
    Node* cur = head;
    for(int i = 0; i < nodeCount; i++)
    {
        // Start with gravity components



        cur = cur->next;
    }
}
