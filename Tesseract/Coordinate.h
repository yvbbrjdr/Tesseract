#ifndef COORDINATE_H
#define COORDINATE_H

#include <cmath>
#ifndef ZERO
#define ZERO (0.0000001f)
#endif

class Coordinate {
public:
    double x,y,z;
    Coordinate();
    Coordinate(double,double,double);
    Coordinate operator + (Coordinate);
    Coordinate operator - (Coordinate);
    Coordinate operator * (double);
    Coordinate operator / (double);
    double* ToArray(double*);
    double Length();
    Coordinate ToDirection();
    Coordinate Abs();
};

#endif // COORDINATE_H
