#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "particle.h"
#include "node.h"
#include "simulation.h"

using std::cout, std::cerr, std::endl;

// Wraps particle and SFML circle


Node::Node()
{
    trailCount = 0;
    trailHead = nullptr;
    next =nullptr;
    last = nullptr;
    particle = new Particle();
    pix = new sf::CircleShape();
    pix->setRadius(1);
}

void Node::SetTrailColor(int r, int g, int b, int a)
{
    trailColor = sf::Color(r,g,b,a);
}

void Node::SetColor(sf::Color col)
{
    pix->setFillColor(col);
}
void Node::SetColor(int r, int g, int b, int a)
{
    pix->setFillColor(sf::Color(r,g,b,a));
}

void Node::SetPos(double long x, double long y)
{
    if(particle != nullptr)
    {
        particle->x = x;
        particle->y = y;
    }
    pix->setPosition(sf::Vector2f((float)x - particle->radius,(float)y - particle->radius));
}
void Node::Update(Simulation* sim)
{
    this->UpdateTrail(sim);
    this->UpdatePos(sim);
}
void Node::UpdatePos(Simulation* sim)
{
    this->SetPos(this->particle->x + this->particle->x_vel, 
                 this->particle->y + this->particle->y_vel);
}

void Node::UpdateTrail(Simulation* sim)
{
    if( sim->tick % sim->trailFreq == 0)
    {
        if(this->trailHead == nullptr)
        {
            if(sim->trailMaxLen > 0)
            {
                this->trailHead = new Node();

                this->trailHead->pix->setRadius(this->particle->radius * sim->trailRadiusMultiplier);

                this->trailHead->SetColor(this->trailColor);
                this->trailHead->SetPos((this->particle->x) + (this->particle->radius * sim->trailRadiusMultiplier), (this->particle->y + (this->particle->radius * sim->trailRadiusMultiplier)));
                this->trailHead->next = nullptr;
                this->trailHead->last = nullptr;
                this->trailCount++;
            }
        }
        else
        {
            Node * n = new Node();
            n->pix->setRadius(sim->trailRadiusMultiplier * this->particle->radius);

            // Get last node
            Node * cur = trailHead;
            while (cur->next != nullptr)
                cur = cur->next;
            
            cur->next = n;
            n->last = cur;

            n->SetPos((this->particle->x) + (this->particle->radius * sim->trailRadiusMultiplier), (this->particle->y + (this->particle->radius * sim->trailRadiusMultiplier)));
            n->SetColor(this->trailColor);

            this->trailCount++;


            if(this->trailCount > sim->trailMaxLen)
            {
              //  cerr << "\n\nAnd finally, cull list.\n\n";
                Node* temp = this->trailHead;
                this->trailHead = trailHead->next;
                this->trailHead->last = nullptr;

                this->trailCount--;
            }
        }
    }
}

void Node::Status()
{
    cout << this->particle->name << " " << "{" << this->particle->mass << "},\t("
        << this->particle->x << ", " << this->particle->y << "),\t[" 
        << this->particle->x_vel << ", " << this->particle->y_vel << "]\n";
}

