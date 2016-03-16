#include "Room.hpp"
#include <QDebug>

Room::Room (int id, QList<RVector> roomPoints) {
    roomId = id;
    numberOfPoints = roomPoints.length();
    QList<double> polyX = RVector::getXList(roomPoints);
    QList<double> polyY = RVector::getYList(roomPoints);

    for (int i = 0; i < numberOfPoints; i++) {
        qDebug("ROOM %d CONSTRUCTOR: (x= %lf, y= %lf)", roomId, polyX[i], polyY[i]);
    }
}

