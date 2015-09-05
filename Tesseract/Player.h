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
    Coordinate Position,EyeVector,LookAt,HeadVector,CanGo;
    double Theta,Phi;
    Player();
    Player(Coordinate);
    void Go(double Front,double Left,double Up);
    void Turn(double Raise, double Left);
};

#endif // PLAYER_H
