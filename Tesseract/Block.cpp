#include "Block.h"

Block::Block() {}

Block::Block(QString _Name,Coordinate _Color,QString _TextureName,bool _SoundCanGoOut) {
    Name=_Name;
    Color=_Color;
    TextureName=_TextureName;
    SoundCanGoOut=_SoundCanGoOut;
}

Bnode::Bnode(QString _Type,int _Belong,Coordinate _Position,Coordinate _HalfSize) {
    Type=_Type;
    Belong=_Belong;
    Position=_Position;
    HalfSize=_HalfSize;
    Data=NULL;
}
