#ifndef PLAYER_H
#define PLAYER_H

#include "World.h"
#include "Coordinate.h"

class Player {
public:
    Coordinate pos,face;
    World *w;
    Player(World *world) {
        w=world;
        pos=Coordinate(0,0,1);
        face=Coordinate(1,0,0);
    }
    void go(double front,double left) {
        pos.x+=face.x*front;
        pos.y+=face.y*front;
        pos.x-=face.y*left;
        pos.y+=face.x*left;
    }
};

#endif // PLAYER_H
