#ifndef PLAYER_H
#define PLAYER_H

#include "Coordinate.h"
#include <QString>

#ifndef ZERO
#define ZERO (0.0000001f)
#endif

#ifndef PI
#define PI (3.14159265358979323846264338f)
#endif

#define INTERVAL 4

class Player {
public:
    QString name;
    Coordinate pos,face,at,up,size;
    double theta,phi;
    Player();
    Player(Coordinate);
    void go(double,double,double);
    void turn(double,double);
};

#endif // PLAYER_H
