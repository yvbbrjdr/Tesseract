#include "Block.h"

Block::Block() {}

Block::Block(const QString &_Name, const Coordinate &_Color, const QString &_TextureName, const bool &_SoundCanGoOut) {
    Name=_Name;
    Color=_Color;
    TextureName=_TextureName;
    SoundCanGoOut=_SoundCanGoOut;
}

Bnode::Bnode(const QString &_Type, const int &_Belong, const Coordinate &_Position, const Coordinate &_HalfSize) {
    Type=_Type;
    Belong=_Belong;
    Position=_Position;
    HalfSize=_HalfSize;
    Data=NULL;
}
