#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include "node.h"
#include "nodelist.h"
#include "simulation.h"
#include "date.h"

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
    date.addSeconds(timeScale);
    if(!muteConsole)
        cout << "\n===============================\nt= " << tick << ", time=[" << date << "]" << endl; 
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
            if(verbose && !muteConsole)
                cur->Status();
            long double d = dist(cur, chk) * distanceScale; // convert meters to  million km

            // Calculate acceleration
            long double F = gravityConstant * ((chk->particle->mass * cur->particle->mass) / (pow(d, 2)));
            long double a = F / cur->particle->mass; // F = ma, so a = F/m

            long double theta = angle(cur,chk); 


            // acceleration by dimension
            long double dvx = x_part(theta, a);
            long double dvy = y_part(theta, a);

            long double xvBefore = cur->particle->x_vel;
            long double yvBefore = cur->particle->x_vel;


            // Apply accel to v

            cur->particle->x_vel += dvx;
            cur->particle->y_vel += dvy;

            if(verbose && !muteConsole)
            {
                cout << "d: " << d << endl;
                cout << "a: " << a << endl;
                cout << "θ: " << theta << endl;
                cout << "Δvx: " << dvx << endl;
                cout << "Δvy: " << dvy << endl;
                cout << "vx " << xvBefore << " -> ";
                cout << cur->particle->x_vel << endl;

                cout << "vy " << yvBefore << " -> ";
                cout << cur->particle->y_vel << endl;
            }
        
            chk = chk->next;
        }
        cur = cur->next;
    }
    if(!muteConsole)
        cout << endl;
    // Now update positions all at once
    cur = list.head;
    for(int i = 0; i < list.count; i++)
    {
        cur->Update(this);
        if(verbose && !muteConsole)
            cerr << cur << ": " << dist(cur, list.head) << endl;
        if(!muteConsole)
            cur->Status();
        cur = cur->next;
    }
}

bool startsWith(string a, string b) // does a start with b
{
    if(a.length() < b.length())
        return false;

    for(int i = 0; i < b.length(); i++)
        if(a[i] != b[i])
            return false;

    return true;
}

void Simulation::LoadSettings(string filename)
{
    cerr << "Loading settings from " << filename << "...\t";
    ifstream in;
    in.open(filename);
    
    string line;
    getline(in, line);
    while(in)
    {
        if(startsWith(line, "GRAV=") && line.length() > 5)
            gravityConstant = stof(line.substr(5, line.length() - 5));

        else if(line == "PAUSED")
            paused = true;

        else if(line == "VERBOSE")
            verbose = true;

        else if(startsWith(line, "X=") && line.length() > 2)
            winX = stoi(line.substr(2, line.length() - 2));

        else if(startsWith(line, "Y=") && line.length() > 2)
            winY = stoi(line.substr(2, line.length() - 2));

        else if(startsWith(line, "TPS=") && line.length() > 4)
            ticksPerSecond = stoi(line.substr(4, line.length() - 4));

        else if(startsWith(line, "TRMX=") && line.length() > 5)
            trailMaxLen = stoi(line.substr(5, line.length() - 5));

        else if(startsWith(line, "TRFQ=") && line.length() > 5)
            trailFreq = stoi(line.substr(5, line.length() - 5));

        else if(startsWith(line, "TRRA=") && line.length() > 5)
            trailRadius = stof(line.substr(5, line.length() - 5));

        else if(startsWith(line, "DSCL=") && line.length() > 5)
            distanceScale = stof(line.substr(5, line.length() - 5));

        else if(startsWith(line, "TSCL=") && line.length() > 5)
            timeScale = stof(line.substr(5, line.length() - 5));

        else if(startsWith(line, "#") == false && line != "")
            cerr << "Failed to parse parameter \"" << line << "\"" << endl;

        getline(in, line);
    }

    in.close();

}


void Simulation::LoadParticles(string filename)
{
    cerr << "Loading particles from " << filename << "...\t";

    int year = 2000;
    int day = 1;
    int month, minute, second, hour = 0;

    ifstream in;
    in.open(filename);
    
    string line;
    getline(in, line);
    while(in)
    {
        if(line.length() > 0 && line[0] != '#')
        {
            if(startsWith(line, "YEAR=") && line.length() > 5)
                date.setYears(stoi(line.substr(5, line.length() - 5)));
            else if(startsWith(line, "MONTH=") && line.length() > 6)
                date.setMonths(stoi(line.substr(6, line.length() - 6))-1);
            else if(startsWith(line, "DAY=") && line.length() > 4)
                date.setDays(stoi(line.substr(4, line.length() - 4)));
            else if(startsWith(line, "HOUR=") && line.length() > 5)
                date.setHours(stoi(line.substr(5, line.length() - 5)));
            else if(startsWith(line, "MINUTE=") && line.length() > 7)
                date.setMinutes(stoi(line.substr(7, line.length() - 7)));
            else if(startsWith(line, "SECOND=") && line.length() > 7)
                date.setSeconds(stoi(line.substr(7, line.length() - 7)));
            else
            {    
                istringstream iss(line);
                vector<string> results(istream_iterator<string>{iss},
                                         istream_iterator<string>());
                if(list.AddNode(results))
                    cerr << ".";
                else
                    cerr << "\nFailed to load particle! : \n" << line << endl;
            }
        }        
        getline(in, line);
    }
    in.close();
    cerr << "done." << endl;
}
