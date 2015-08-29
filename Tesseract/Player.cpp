#include "Player.h"

Player::Player() {}

Player::Player(Coordinate s) {
    size=s;
    pos=Coordinate(0,1,0);
    theta=0;
    phi=PI/2;
    turn(0,0);
}

void Player::go(double front,double left,double raise) {
    pos.z+=cos(theta)*front;
    pos.x+=sin(theta)*front;
    pos.z-=sin(theta)*left;
    pos.x+=cos(theta)*left;
    pos.y+=raise;
    if (pos.z<-size.z/2)
        pos.z=-size.z/2;
    if (pos.z>size.z/2)
        pos.z=size.z/2;
    if (pos.x<-size.x/2)
        pos.x=-size.x/2;
    if (pos.x>size.x/2)
        pos.x=size.x/2;
    if (pos.y<1)
        pos.y=1;
    if (pos.y>size.y)
        pos.y=size.y;
    at=pos+face;
}

void Player::turn(double raise,double left) {
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
    face.z=cos(theta)*sin(phi)*INTERVAL;
    face.x=sin(theta)*sin(phi)*INTERVAL;
    face.y=cos(phi)*INTERVAL;
    at=pos+face;
    up.z=-cos(theta)*cos(phi);
    up.x=-sin(theta)*cos(phi);
    up.y=sin(phi);
}
