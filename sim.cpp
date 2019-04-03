#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "particle.h"

const float GRAV = 6.673E-11;

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

    void SetPos(double long x, double long y)
    {
        particle->x = x;
        particle->y = y;
        pix.setPosition(sf::Vector2f((float)x,(float)y));
    }
    void UpdatePos()
    {
        this->SetPos(this->particle->x + this->particle->x_vel, 
                     this->particle->y + this->particle->y_vel);
    }

    void Status()
    {
        cout << this << ", (" << this->particle->x << ", " << this->particle->y << "), [" 
            << this->particle->x_vel << ", " << this->particle->y_vel << "]\n";
    }

    Node* next = nullptr;
    Node* last = nullptr;
};

int nodeCount = 0;
Node* head;
Node* tail;

void AddNode(long double mass = 1.0)
{
    Node* newNode = new Node();
    newNode->particle = new Particle();
    newNode->particle->mass = mass;

    if(head == nullptr)
    {
        head = newNode;
        tail = newNode;
        head->next = nullptr;
        head->last = nullptr;
    }
    else
    {
        tail->next = newNode;

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
    window.setFramerateLimit(6);

    AddNode(1.989E30); // mass of sun
    AddNode(5.972E24); // mass of earth
    
    head->pix.setFillColor(sf::Color::Green);
    head->pix.setFillColor(sf::Color::Red);

    head->SetColor(255,255,0);
    head->next->SetColor(128,128,255);

    head->SetPos(250,250);
    head->next->SetPos(110,110);
    //head->next->SetPos(399,250);

    head->next->particle->y_vel = 0.7; // Earth orbits at 30 km/s

    cerr << "Gravitational Constant= " + to_string(GRAV) + "\n"; 
    cerr << "Beginning simulation. Particles: " + to_string(nodeCount) + "\n"; 
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

        //window.clear();
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
long double dist(Node* a, Node* b)
{
    return sqrt( pow(b->particle->x - a->particle->x, 2) + pow(b->particle->y - a->particle->y, 2));
}

// Angle relative x-axis between two points(in rads)
long double angle(Node* a, Node* b)
{
    return atan2(b->particle->y - a->particle->y, b->particle->x - a->particle->x );
}

long double x_part(long double angle, long double magnitude) // Get x part of magnitude with angle
{
    return magnitude * cos(angle);
}

long double y_part(long double angle, long double magnitude) // Get y part of magnitude with angle
{
    return magnitude * sin(angle);
}

void Simulate()
{
    Node* cur = head;
    for(int i = 0; i < nodeCount; i++)
    {
        // For each other node

        Node* chk = head;
        for(int i = 0; i < nodeCount; i++)
        {
            // Skip self
            if(chk == cur)
            {
                chk = chk->next;
                continue;
            }
            // Get distance
            long double d = dist(cur, chk) * 10E8; // convert meters to  million km
        
            // Calculate acceleration
            long double a = (GRAV * chk->particle->mass) / (pow(d, 2));
            cout << "\n" << cur << ":\nd= " + to_string(d) + "\na= " + to_string(a) << endl;  
            
            long double theta = angle(cur,chk); 
            
            long double dvx = x_part(theta, a);
            long double dvy = y_part(theta, a);

            cout << "Δvx= " + to_string(dvx) + "\n";
            cout << "Δvy= " + to_string(dvy) + "\n";

            // Apply accel to v
            cur->particle->x_vel += dvx;
            cur->particle->y_vel += dvy;
        
            chk = chk->next;
        }
        cur = cur->next;
    }
    // Now update positions all at once
    cur = head;
    for(int i = 0; i < nodeCount; i++)
    {
        cur->UpdatePos();
        cur->Status();
        cur = cur->next;
    }
}
