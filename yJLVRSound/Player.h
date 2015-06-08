#ifndef PLAYER_H
#define PLAYER_H

#include "World.h"
#include "Coordinate.h"

#ifndef ZERO
#define ZERO (0.0000001f)
#endif

#ifndef PI
#define PI (3.14159265358979323846264338f)
#endif

class Player {
public:
    Coordinate pos,face,at,up;
    double theta,phi;
    World *w;
    Player(World *world) {
        w=world;
        pos=Coordinate(0,1,0);
        theta=0;
        phi=PI/2;
        turn(0,0);
    }
    void go(double front,double left) {
        pos.z+=cos(theta)*front;
        pos.x+=sin(theta)*front;
        pos.z-=sin(theta)*left;
        pos.x+=cos(theta)*left;
        at=pos+face;
    }
    void turn(double raise,double left) {
        if (phi-raise<0)
            phi=0;
        else if (phi-raise>PI)
            phi=PI;
        else
            phi-=raise;
        theta+=left;
        while (theta<0)
            theta+=2*PI;
        while (theta>=2*PI)
            theta-=2*PI;
        face.z=cos(theta)*sin(phi);
        face.x=sin(theta)*sin(phi);
        face.y=cos(phi);
        at=pos+face;
        up.z=-cos(theta)*cos(phi);
        up.x=-sin(theta)*cos(phi);
        up.y=sin(phi);
    }
};

#endif // PLAYER_H
