#ifndef SIMULATION_H
#define SIMULATION_H

#include "node.h"
#include <string>
#include "nodelist.h"
#include "date.h"

class Node;

class Simulation
{
private:
long double dist(Node * a, Node * b);
long double angle(Node * a, Node * b);
long double x_part(long double angle, long double magnitude);
    long double y_part(long double angle, long double magnitude);
  public:
    Simulation();
    int tick = 0;
    Date date;
    float gravityConstant = 6.673E-20;
    float distanceScale = 10E5;
    float timeScale = 1E3;
    int winX = 500;
    int winY = 500;
    int ticksPerSecond = 60;
    int trailMaxLen = 100;
    int trailFreq = 1;
    float trailRadius = 0.5;
    NodeList list;

    bool verbose = false;
    bool paused = false;
    bool muteConsole = false;

    void Simulate();
    void LoadSettings(std::string filename);
    void LoadParticles(std::string filename);
};
#endif
