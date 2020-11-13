#ifndef PARTICLE_H
#define PARTICLE_H
#include <string>
//
// Basic particle class


class Particle
{
    private:
    public:
        std::string name;
        double long x = 0;
        double long y = 0;
        long double mass = 0.0;
        long double x_vel = 0.0;
        long double y_vel = 0.0;
        double radius = 0.0;

        Particle();

    protected:
};
#endif
