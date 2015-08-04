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
    QString Name;
    Coordinate Position,EyeVector,LookAt,HeadVector;
    double Theta,Phi;
    Player();
    Player(Coordinate);
    void Go(double,double,double);
    void Turn(double,double);
};

#endif // PLAYER_H
