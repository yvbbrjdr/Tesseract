#include "Coordinate.h"

Coordinate::Coordinate() {
    x=y=z=0;
}

Coordinate::Coordinate(double a,double b,double c) {
    x=a;
    y=b;
    z=c;
}

Coordinate Coordinate::operator + (Coordinate b) {
    Coordinate a=*this;
    return Coordinate(a.x+b.x,a.y+b.y,a.z+b.z);
}

Coordinate Coordinate::operator - (Coordinate b) {
    Coordinate a=*this;
    return Coordinate(a.x-b.x,a.y-b.y,a.z-b.z);
}

Coordinate Coordinate::operator * (double d) {
    Coordinate a=*this;
    return Coordinate(a.x*d,a.y*d,a.z*d);
}

Coordinate Coordinate::operator / (double d) {
    Coordinate a=*this;
    return Coordinate(a.x/d,a.y/d,a.z/d);
}

double* Coordinate::ToArray(double res[3]) {
    res[0]=this->x;
    res[1]=this->y;
    res[2]=this->z;
    return res;
}

double Coordinate::Length() {
    return sqrt(x*x+y*y+z*z);
}

Coordinate Coordinate::ToDirection() {
    double l=Length();
    Coordinate res=*this;
    if (fabs(l)>ZERO) {
        res.x/=l;
        res.y/=l;
        res.z/=l;
    }
    return res;
}

Coordinate Coordinate::Abs() {
    Coordinate res=*this;
    res.x=fabs(x);
    res.y=fabs(y);
    res.z=fabs(z);
    return res;
}
