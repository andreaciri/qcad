#include "Room.hpp"
#include <QDebug>

Room::Room (int id, QList<RVector> roomPoints) {
    roomId = id;
    numberOfPoints = roomPoints.length();
    polyX = RVector::getXList(roomPoints);
    polyY = RVector::getYList(roomPoints);

    for (int i = 0; i < numberOfPoints; i++) {
        qDebug("ROOM %d CONSTRUCTOR: (x= %lf, y= %lf)", roomId, polyX[i], polyY[i]);
    }
    this->precalc_values();
}

bool Room::isInside(int intX, int intY){
    double x = (double) intX;
    double y = (double) intY;
    int i;
    int j = polyCorners - 1;
    bool oddNodes = false;

    for (i = 0; i < numberOfPoints; i++) {
        if ((polyY[i] < y && polyY[j] >= y
             ||   polyY[j] < y && polyY[i] >= y)) {
            oddNodes ^= (y * multiple[i] + constant[i] < x); // ^ operator is the bit-wise XOR
        }
        j=i;
    }
    return oddNodes;
}

void Room::precalc_values() {

    int i;
    int j = numberOfPoints - 1 ;
    constant = polyX;
    multiple = polyX;

    for(i = 0; i < numberOfPoints; i++) {
        if(polyY[j] == polyY[i]) {
            constant[i] = polyX[i];
            multiple[i] = 0;
        }
        else {
            constant[i] = polyX[i] - (polyY[i] * polyX[j]) / (polyY[j] - polyY[i]) + (polyY[i] * polyX[i]) / (polyY[j] - polyY[i]);
            multiple[i] = (polyX[j] - polyX[i]) / (polyY[j] - polyY[i]);
        }
        j = i;
    }
}
