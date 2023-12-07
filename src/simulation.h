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
    float distanceScale = 1E9;
    float timeScale = 1E0;
    int winX = 500;
    int winY = 500;
    int ticksPerSecond = 0;
    int trailMaxLen = 200;
    int trailFreq = 500000;
    float trailRadiusMultiplier = 0.3;
    NodeList list;

    bool verbose = false;
    bool paused = false;
    bool muteConsole = false;
    bool showTicks = true;

    void Simulate();
    void LoadSettings(std::string filename);
    void LoadParticles(std::string filename);

    void SaveSettings();
    void SaveParticles();
};
#endif
