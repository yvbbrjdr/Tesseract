#ifndef PLAYER_H
#define PLAYER_H

#include "World.h"
#include "Coordinate.h"

#ifndef ZERO
#define ZERO (0.00000001f)
#endif

#ifndef PI
#define PI (3.14159265358979323846264338f)
#endif

class Player {
public:
    Coordinate pos,face,at;
    double theta,phi;
    World *w;
    Player(World *world) {
        w=world;
        pos=Coordinate(0,0,0);
        theta=0;
        phi=PI/2;
        turn(0,0);
    }
    void go(double front,double left) {
        pos.x+=cos(theta)*front;
        pos.y+=sin(theta)*front;
        pos.x-=sin(theta)*left;
        pos.y+=cos(theta)*left;
    }
    void turn(double up,double left) {
        if (phi-up>=0&&phi-up<=PI)
            phi-=up;
        theta+=left;
        while (theta<0)
            theta+=2*PI;
        while (theta>=2*PI)
            theta-=2*PI;
        face.x=cos(theta)*sin(phi);
        face.y=sin(theta)*sin(phi);
        face.z=cos(phi);
        at=pos+face;
    }
};

#endif // PLAYER_H
