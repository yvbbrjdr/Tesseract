#include "Block.h"

Bnode::Bnode(int _Type,int _Belong,Coordinate _Position,Coordinate _HalfSize) {
    Type=_Type;
    Belong=_Belong;
    Position=_Position;
    HalfSize=_HalfSize;
    Data=NULL;
}
