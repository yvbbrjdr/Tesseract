#ifndef COORDINATE_H
#define COORDINATE_H

#include <cmath>
#ifndef ZERO
#define ZERO 0.00000001f
#endif

class Coordinate {
public:
    double x,y,z;
    Coordinate() {x=y=z=0;}
    Coordinate(double a,double b,double c) {
        x=a;
        y=b;
        z=c;
    }
    Coordinate operator + (Coordinate b) {
        Coordinate a=*this;
        return Coordinate(a.x+b.x,a.y+b.y,a.z+b.z);
    }
    Coordinate operator - (Coordinate b) {
        Coordinate a=*this;
        return Coordinate(a.x-b.x,a.y-b.y,a.z-b.z);
    }
    Coordinate operator * (double d) {
        Coordinate a=*this;
        return Coordinate(a.x*d,a.y*d,a.z*d);
    }
    Coordinate operator / (double d) {
        Coordinate a=*this;
        return Coordinate(a.x/d,a.y/d,a.z/d);
    }
    double* ToArray() {
        double *res=new double[3];
        res[0]=this->x;
        res[1]=this->y;
        res[2]=this->z;
        return res;
    }
    double Length() {return sqrt(x*x+y*y+z*z);}
    Coordinate ToDirection() {
        double l=Length();
        Coordinate res;
        if (fabs(l)>ZERO) {
            res.x/=l;
            res.y/=l;
            res.z/=l;
        }
        return res;
    }
};

#endif // COORDINATE_H
