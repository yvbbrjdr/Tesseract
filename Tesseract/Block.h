#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include "Coordinate.h"
#include <bass.h>
#include <QList>
#include "Sound.h"
#include "Player.h"
#include <cstring>


class World;
class Bnode;
class TesseractWidget;

class Block {
public:
    QString Name;
    Coordinate Color;
    QString TextureName;
    bool SoundCanGoOut;
};

class Bnode {
public:
    int Type,Belong;
    Coordinate Position,HalfSize;
    void *Data;
    Bnode(int _Type,int _Belong,Coordinate _Position,Coordinate _HalfSize);
};

#include "tesseractwidget.h"

#endif // BLOCK_H
