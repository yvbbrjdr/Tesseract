#ifndef WORLD_H
#define WORLD_H

#include "Coordinate.h"

class World {
public:
    Coordinate size;
    World(Coordinate s) {size=s;}
};

#endif // WORLD_H
