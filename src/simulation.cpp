#include <cmath>
#include <iostream>
#include "node.h"
#include "nodelist.h"
#include "simulation.h"

using namespace std;

        Simulation::Simulation()
{

}

// Distance between two points
long double Simulation::dist(Node* a, Node* b)
{
    return sqrt( pow(b->particle->x - a->particle->x, 2) + pow(b->particle->y - a->particle->y, 2));
}

// Angle relative x-axis between two points(in rads)
long double Simulation::angle(Node* a, Node* b)
{
    return atan2(b->particle->y - a->particle->y, b->particle->x - a->particle->x );
}

long double Simulation::x_part(long double angle, long double magnitude) // Get x part of magnitude with angle
{
    return magnitude * cos(angle);
}

long double Simulation::y_part(long double angle, long double magnitude) // Get y part of magnitude with angle
{
    return magnitude * sin(angle);
}

void Simulation::Simulate()
{
    tick++;
    cout << "\n===============================\nt= " << tick << endl; 
    Node* cur = list.head;
    for(int i = 0; i < list.count; i++)
    {
        // For each other node

        Node* chk = list.head;
        for(int i = 0; i < list.count; i++)
        {
            // Skip self
            if(chk == cur)
            {
                chk = chk->next;
                continue;
            }
            // Get distance
            long double d = dist(cur, chk) * distanceScale; // convert meters to  million km
        
            // Calculate acceleration
            long double a = (gravityConstant * chk->particle->mass) / (pow(d, 2));
            long double theta = angle(cur,chk); 
            
            // acceleration by dimension
            long double dvx = x_part(theta, a);
            long double dvy = y_part(theta, a);

            // Apply accel to v
            cur->particle->x_vel += dvx;
            cur->particle->y_vel += dvy;
        
            chk = chk->next;
        }
        cur = cur->next;
    }
    cout << endl;
    // Now update positions all at once
    cur = list.head;
    for(int i = 0; i < list.count; i++)
    {
        cur->Update(this);
        cur->Status();
        cur = cur->next;
    }
}

