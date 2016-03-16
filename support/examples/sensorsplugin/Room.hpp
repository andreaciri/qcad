#ifndef ROOM_HPP
#define ROOM_HPP
#include <QObject>
#include <RActionAdapter.h>


class Room{

public:
    // Room constructor
    Room(int id, QList<RVector> roomPoints);

    bool isInside(int x, int y);
    int roomId;
    int numberOfPoints;
};

#endif
