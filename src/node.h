#ifndef NODE_H
#define NODE_H
#include "simulation.h"
#include "particle.h"
#include <SFML/Graphics.hpp>

class Simulation;

class Node
{
  public:
      Node* next = nullptr;
      Node* last = nullptr;

      Particle* particle = nullptr;
      sf::CircleShape* pix = nullptr;
      sf::Color trailColor;
      float trailRadius = 0.5;

      int trailCount = 0;
      Node* trailHead = nullptr;
      Node();

      void SetTrailColor(int r,int g, int b, int a=255);
      void SetColor(int r,int g, int b, int a=255);
      void SetColor(sf::Color col);
      void SetPos(double long x, double long y);
      void Update(Simulation* sim);
      void UpdatePos();
      void UpdateTrail(Simulation* sim);
      void Status();

  private:
};
#endif
