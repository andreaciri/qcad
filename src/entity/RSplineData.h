/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#ifndef RSPLINEDATA_H
#define RSPLINEDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RSpline.h"
#include "RVector.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a spline entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RSplineData: public REntityData, protected RSpline {

    friend class RSplineEntity;

protected:
    RSplineData(RDocument* document, const RSplineData& data);

public:
    RSplineData();
    RSplineData(const RSpline& spline);

    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    void setShape(const RSpline& s) {
        copySpline(s);
    }

    void appendControlPoint(const RVector& point) {
        RSpline::appendControlPoint(point);
    }

    void setPeriodic(bool on) {
        RSpline::setPeriodic(on);
    }

    bool isValid() const {
        return RSpline::isValid();
    }

    int getDegree() const {
        return RSpline::getDegree();
    }

    double getDirection1() const {
        return RSpline::getDirection1();
    }

    double getDirection2() const {
        return RSpline::getDirection2();
    }

    RVector getStartPoint() const {
        return RSpline::getStartPoint();
    }

    RVector getEndPoint() const {
        return RSpline::getEndPoint();
    }

    void setStartPoint(const RVector& sp) {
        RSpline::setStartPoint(sp);
    }

    void setEndPoint(const RVector& ep) {
        RSpline::setEndPoint(ep);
    }

    bool reverse() {
        return RSpline::reverse();
    }

    RS::Ending getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
        return RSpline::getTrimEnd(trimPoint, clickPoint);
    }
    void trimStartPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid) {
        return RSpline::trimStartPoint(trimPoint, clickPoint);
    }
    void trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid) {
        return RSpline::trimEndPoint(trimPoint, clickPoint);
    }

    bool isClosed() const  {
        return RSpline::isClosed();
    }

    bool isPeriodic() const  {
        return RSpline::isPeriodic();
    }

    RVector getTangentAtStart() const {
        return RSpline::getTangentAtStart();
    }

    RVector getTangentAtEnd() const {
        return RSpline::getTangentAtEnd();
    }

    //void updateTangentsPeriodic() {
    //    RSpline::updateTangentsPeriodic();
    //}

    QList<RVector> getControlPoints() const {
        return RSpline::getControlPoints();
    }

    QList<RVector> getControlPointsWrapped() const {
        return RSpline::getControlPointsWrapped();
    }

    QList<RVector> getFitPoints() const {
        return RSpline::getFitPoints();
    }

    QList<double> getKnotVector() const {
        return RSpline::getKnotVector();
    }

    QList<double> getActualKnotVector() const {
        return RSpline::getActualKnotVector();
    }

    QList<double> getWeights() const {
        return RSpline::getWeights();
    }

    double getLength() const {
        return RSpline::getLength();
    }
    RVector getPointAt(double t) const {
        return RSpline::getPointAt(t);
    }
    RVector getPointAtDistance(double distance) const {
        return RSpline::getPointAtDistance(distance);
    }
    double getAngleAt(double distance, RS::From from = RS::FromStart) const {
        return RSpline::getAngleAt(distance, from);
    }

    RPolyline toPolyline(int segments) const {
        return RSpline::toPolyline(segments);
    }

    void simplify(double tolerance) {
        RSpline s = RSpline::simplify(tolerance);
        setShape(s);
    }

    //RSpline getSubSpline(double d1, double d2) const {
    //    return RSpline::getSubSpline(d1, d2);
    //}

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false) const {
        Q_UNUSED(queryBox)
        Q_UNUSED(ignoreComplex)

        // make sure we copy only splines with updated cache:
        //getExploded();

        return QList<QSharedPointer<RShape> >() <<
                QSharedPointer<RShape>(new RSpline(*this));
    }

    virtual void update() const {
        //RSpline::update();
    }
};

Q_DECLARE_METATYPE(RSplineData)
Q_DECLARE_METATYPE(RSplineData*)
Q_DECLARE_METATYPE(const RSplineData*)
Q_DECLARE_METATYPE(QSharedPointer<RSplineData>)

#endif
