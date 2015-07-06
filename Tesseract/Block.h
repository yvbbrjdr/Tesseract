#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include "Coordinate.h"

class Block {
public:
    QString Name;
    Coordinate Color;
    QString TextureName;
    bool SoundCanGetThrough;
};

#endif // BLOCK_H
