#ifndef ROOM_HPP
#define ROOM_HPP
#include <QObject>
#include <RActionAdapter.h>
#include <QSet>


class Room{

public:
    // Room constructor
    Room(int id, QList<RVector> roomPoints);

    bool isInside(int x, int y);
    int roomId;
    int numberOfPoints;
    QList<double> polyX;
    QList<double> polyY;
    QSet<QList<int> > insidePoints;
private:
    QList<double> constant; // Storage for precalculated constants (same size as polyX)
    QList<double> multiple; // Storage for precalculated multipliers (same size as polyX)
    void precalc_values(); // Pre-calcuation of inside-check for efficiency improvement
};

#endif
