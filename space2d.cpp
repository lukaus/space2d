#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/particle.h"
#include "src/node.h"
#include "src/simulation.h"

using namespace std;

int main(int argc, char* argv[])
{
    Simulation sim;
    if(argc > 3)
    {
        cerr << "Syntax is 'space2d [settings file] [particles file]'"
            << "\n\t [settings file] and [particles file] are optional and default to settings.cfg and particles.dat respectively.\n";
        return 0;
    }
    string settingsFilename = "settings.cfg";
    string particleFilename = "particles.dat";
    if(argc > 1)
        settingsFilename = (argv[1]);
    else if(argc > 2)
        particleFilename = (argv[2]);

    sim.LoadSettings(settingsFilename);
    sim.LoadParticles(particleFilename);

    sf::RenderWindow window(sf::VideoMode(sim.winX, sim.winY), "Space2d v0.8");
    window.setFramerateLimit(sim.ticksPerSecond);

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
