#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/particle.h"
#include "src/node.h"
#include "src/simulation.h"
#include <sys/stat.h>

using namespace std;

bool fileExists(const string& fn)
{
    struct stat b;
    return(stat(fn.c_str(), &b) == 0);
}

int main(int argc, char* argv[])
{

    // initialization
    Simulation sim;
    Node * target = nullptr;
    bool dragging = false;
    bool updateScreen = true;

    // parse arguments
    if(argc > 3)
    {
        cerr << "Syntax is 'space2d [particles file] [settings file]'"
            << "\n\t [particles file] and [settings file] are optional and default to settings.cfg and particles.dat respectively.\n";
        return 0;
    }
    string settingsFilename = "cfg/settings.cfg";
    string particleFilename = "dat/particles.dat";

    // Load settings and data
    if (argc == 1)
    {
        // Search for saved .cfg and .dat, otherwise load defaults
        if(fileExists("cfg/saved_settings.cfg"))
            settingsFilename = "cfg/saved_settings.cfg";

        if(fileExists("dat/saved_particles.dat"))
            particleFilename = "dat/saved_particles.dat";
    }

    else 
    {
        if(argc > 1)
        {
            // Make sure files exist
            particleFilename = (argv[1]);
            if(fileExists(particleFilename) == false)
                particleFilename = "dat/"+particleFilename;
            if(fileExists(particleFilename) == false)
            {
                cerr << "Cannot access data file \"" << (argv[1]) << "\" either in ./ or ./dat!";
                return -1;
            }
        }
        if(argc > 2)
        {
            settingsFilename = (argv[2]);
            if(fileExists(settingsFilename) == false)
                settingsFilename = "cfg/"+settingsFilename;
            if(fileExists(settingsFilename) == false)
            {
                cerr << "Cannot access configuration file \"" << (argv[2]) << "\" either in ./ or ./cfg!";
                return -1;
            }
        }
    }
    sim.LoadSettings(settingsFilename);
    sim.LoadParticles(particleFilename);


    // Create graphical stuff
    sf::RenderWindow window(sf::VideoMode(sim.winX, sim.winY), "Space2d v0.99");
    window.setFramerateLimit(sim.ticksPerSecond);

    cerr << "Window is (" << sim.winX << ", " << sim.winY << ")\n";
    cerr << "Trails are " << sim.trailMaxLen << " pixels long updated every " << sim.trailFreq << " ticks.\n";
    cerr << "Gravitational Constant= " << sim.gravityConstant << "\n"; 
    cerr << "Distance per pixel is " << sim.distanceScale <<  "\n"; 
    cerr << "Beginning simulation at " << sim.ticksPerSecond << " ticks/s. \nParticle count: " << sim.list.count << "\n"; 

    sf::Vector2f mPos = window.getView().getCenter();
    while (window.isOpen())
    {
        if(!sim.paused)
            sim.Simulate();
        sf::Event event;
        sf::View view = window.getView();

        while (window.pollEvent(event))
        {
            bool recenter = false;
            if (event.type == sf::Event::Closed)
            {
                cerr << "Closing Space2d..." << endl;
                // Save settings and particles

                sim.SaveSettings();
                sim.SaveParticles();

                window.close();
            }
            if(event.type ==sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            view = window.getView();
            if(updateScreen && event.type == sf::Event::MouseWheelMoved)
            {
                if(event.mouseWheel.delta < 0)
                {
                    view.zoom(10.0f / 9.0f);
                }
                else if(event.mouseWheel.delta > 0)
                {
                    view.zoom(9.0f / 10.0f);
                }
                window.setView(view);
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Equal) // Increase TPS
                {
                    int addTps = 1;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                        addTps *= 10;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        addTps *= 100;
                    sim.ticksPerSecond += addTps;
                    window.setFramerateLimit(sim.ticksPerSecond);
                    cout << sim.tick << ", [" << sim.date << "]: TicksPerSecond: " << sim.ticksPerSecond << endl;
                }
                if(event.key.code == sf::Keyboard::Hyphen) // Increase TPS
                {
                    int addTps = -1;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                        addTps *= 10;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        addTps *= 100;
                    sim.ticksPerSecond += addTps;
                    if (sim.ticksPerSecond < 0)
                        sim.ticksPerSecond = 0;
                    window.setFramerateLimit(sim.ticksPerSecond);
                    cout << sim.tick << ", [" << sim.date << "]: TicksPerSecond: " << sim.ticksPerSecond << endl;
                }
                if(event.key.code == sf::Keyboard::Space)
                {
                    sim.paused = !sim.paused;
                    cout << sim.tick << ", [" << sim.date << "]: Pause: " << sim.paused << endl;
                }
                if(event.key.code == sf::Keyboard::T) // Toggle show ticks
                {
                    sim.showTicks = !sim.showTicks;
                    cout << sim.tick << ", [" << sim.date << "]: Show time: " << sim.showTicks << endl;

                }
                if(event.key.code == sf::Keyboard::P) // Toggle screen refresh
                {
                    updateScreen = !updateScreen;
                    cout << sim.tick <<", [" << sim.date << "]: Update screen: " << updateScreen << endl;
                }
                if(event.key.code == sf::Keyboard::L) // Toggle muting console logging
                {
                    sim.muteConsole = !sim.muteConsole;
                    cout << sim.tick << ", [" << sim.date << "]: Mute console: " << sim.muteConsole << endl;
                }
                if(event.key.code == sf::Keyboard::V) // Toggle muting console logging
                {
                    sim.verbose = !sim.verbose;
                    cout << sim.tick << ", [" << sim.date << "]: Verbose: " << sim.verbose << endl;
                }
                if(event.key.code == sf::Keyboard::Period && sim.paused)
                    sim.Simulate();
                if(event.key.code == sf::Keyboard::Tab && updateScreen) // Target next particle
                {
                    Node * nextTarget = nullptr;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {
                        // Go to last/tail instead of next/head
                        if (target == nullptr)
                           nextTarget = sim.list.tail; 
                        else
                        {
                            nextTarget = target->last;
                        }
                    }
                    else
                    {
                        if (target == nullptr)
                        {
                            nextTarget = sim.list.head;
                        }
                        else
                            nextTarget = target->next;
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    {
                        nextTarget = nullptr;
                    }
                    else if (nextTarget == nullptr)
                    {
                        recenter = true;
                        target = nullptr;
                    }
                    target = nextTarget;

                    if (target == nullptr)
                        cout << "No target.\n";
                    else
                        cout << "Targetting " << target->particle->name << "." << endl;
                }
            }
            if(updateScreen && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                mPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                dragging = true;
                target=nullptr;
            }
            else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                dragging = false;
            }
            else if(updateScreen && event.type == sf::Event::MouseMoved && dragging)
            {
                sf::Vector2f curPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                float xMove = mPos.x - curPos.x;
                float yMove = mPos.y - curPos.y;
                view.move(xMove, yMove);
            }

            // Adjust view to target
            if(recenter)
            {
                float xRatio = window.getSize().x; 
                float yRatio = window.getSize().y;

                sf::FloatRect visibleArea(0.f, 0.f, window.getSize().x, window.getSize().y);
                view = sf::View(visibleArea);
            }
        }
        if(target != nullptr) // Center on target
            view.setCenter(target->particle->x, target->particle->y);



        if (updateScreen)
        {
            window.setView(view);
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
    }

    return 0;
}
