#include "Player.h"

Coordinate Player::CanGo;

Player::Player() {
    Position=Coordinate(0,1,0);
    Theta=0;
    Phi=PI/2;
    Turn(0,0);
}

void Player::Go(double Front,double Left,double Up) {
    Position.z+=cos(Theta)*Front;
    Position.x+=sin(Theta)*Front;
    Position.z-=sin(Theta)*Left;
    Position.x+=cos(Theta)*Left;
    Position.y+=Up;
    if (Position.z<-CanGo.z/2)
        Position.z=-CanGo.z/2;
    if (Position.z>CanGo.z/2)
        Position.z=CanGo.z/2;
    if (Position.x<-CanGo.x/2)
        Position.x=-CanGo.x/2;
    if (Position.x>CanGo.x/2)
        Position.x=CanGo.x/2;
    if (Position.y<1)
        Position.y=1;
    if (Position.y>CanGo.y)
        Position.y=CanGo.y;
    LookAt=Position+EyeVector;
}

void Player::Turn(double Raise,double Left) {
    if (Phi-Raise<0)
        Phi=0;
    else if (Phi-Raise>PI)
        Phi=PI;
    else
        Phi-=Raise;
    Theta+=Left;
    while (Theta<0)
        Theta+=2*PI;
    while (Theta>=2*PI)
        Theta-=2*PI;
    EyeVector.z=cos(Theta)*sin(Phi)*INTERVAL;
    EyeVector.x=sin(Theta)*sin(Phi)*INTERVAL;
    EyeVector.y=cos(Phi)*INTERVAL;
    LookAt=Position+EyeVector;
    HeadVector.z=-cos(Theta)*cos(Phi);
    HeadVector.x=-sin(Theta)*cos(Phi);
    HeadVector.y=sin(Phi);
}
