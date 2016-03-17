#include "Room.hpp"
#include <QDebug>

Room::Room (int id, QList<RVector> roomPoints) {
    int i, x, y;
    double minX, minY, maxX, maxY;
    roomId = id;
    numberOfPoints = roomPoints.length();
    polyX = RVector::getXList(roomPoints);
    polyY = RVector::getYList(roomPoints);

    for (i = 0; i < numberOfPoints; i++) {
        qDebug("ROOM %d CONSTRUCTOR: (x= %lf, y= %lf)", roomId, polyX[i], polyY[i]);
    }

    this->precalc_values();

//    minX = polyX[0];
//    minY = polyY[0];
//    maxX = polyX[0];
//    maxY = polyY[0];
//    for (i = 0; i < numberOfPoints; i++){
//        if(polyX[i] < minX){
//            minX = polyX[i];
//        }
//        else if(polyX[i] > maxX){
//            maxX = polyX[i];
//        }
//        if(polyY[i] < minY){
//            minY = polyY[i];
//        }
//        else if(polyY[i] > maxY){
//            maxY = polyY[i];
//        }
//    }
//    RVector *r = new RVector(1, 1, 0, true);
//    QList<int > temp;
//    temp.append(1);
//    temp.append(2);
//    insidePoints.insert(temp);


}

bool Room::isInside(int intX, int intY){
    double x = (double) intX;
    double y = (double) intY;
    int i;
    int j = numberOfPoints - 1;
    bool oddNodes = false;

    for (i = 0; i < numberOfPoints; i++) {
        if ((polyY[i] < y && polyY[j] >= y)
             ||   (polyY[j] < y && polyY[i] >= y)) {
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
