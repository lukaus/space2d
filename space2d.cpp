#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/particle.h"
#include "src/node.h"
#include "src/simulation.h"

using namespace std;

int main()
{
    Simulation sim;

    sf::RenderWindow window(sf::VideoMode(sim.winX, sim.winY), "Space2d v0.1");
    window.setFramerateLimit(sim.ticksPerSecond);

    sim.list.AddNode(1.989E30); // mass of sun
    sim.list.AddNode(1.989E30); // mass of sun
    sim.list.AddNode(1.989E30); // mass of sun
    //AddNode(5.972E24); // mass of earth


    sim.list[0].SetColor(255,255,0);
    sim.list[0].next->SetColor(128,128,255);

    sim.list.head->SetPos(250,250);
    sim.list.head->next->SetPos(397,250);

    sim.list.head->next->next->SetColor(255,128,128);
    sim.list.head->next->next->SetPos(597,250);
    //head->next->SetPos(399,250);

    sim.list.head->particle->y_vel = -0.3; // Earth orbits at 30 km/s
    sim.list.head->next->particle->y_vel = 0.3; // Earth orbits at 30 km/s
    sim.list.head->next->next->particle->x_vel = -0.3; // Earth orbits at 30 km/s

    sim.list.head->SetTrailColor(245, 245, 220);
    sim.list.head->next->SetTrailColor(245, 245, 220);
    sim.list.head->next->next->SetTrailColor(245, 245, 220);

    cerr << "Window is (" << sim.winX << ", " << sim.winY << ")\n";
    cerr << "Trails are " << sim.trailMaxLen << " pixels long updated every " << sim.trailFreq << " ticks.\n";
    cerr << "Gravitational Constant= " << sim.gravityConstant << "\n"; 
    cerr << "Distance per pixel is " << sim.distanceScale <<  "\n"; 
    cerr << "Beginning simulation at " << sim.ticksPerSecond << " ticks/s. \nParticle count: " << sim.list.count << "\n"; 

    while (window.isOpen())
    {
        sim.Simulate();
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
        Node* cur = sim.list.head;
        for(int i = 0; i < sim.list.count; i++)
        {   
            // Draw node's trail
            Node * trailCur = cur->trailHead;
            if(trailCur != nullptr)
            {
                for( int j = 0; j < cur->trailCount; j++)
                {
                    window.draw(*trailCur->pix);
                    trailCur = trailCur->next;
                }
            }
            // Then draw node itself
            window.draw(*cur->pix);

            cur = cur->next;
        }      

        window.display();
    }

    return 0;
}
