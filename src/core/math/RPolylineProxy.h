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

#ifndef RPOLYLINEPROXY_H
#define RPOLYLINEPROXY_H

#include "../core_global.h"

#include <RS.h>

class RArc;
class RExporter;
class RLine;
class RPainterPath;
class RPolyline;
class RVector;


/**
 * Proxy for advanced polyline functionality. May be implemented
 * by a plugin.
 *
 * \ingroup math
 */
class QCADCORE_EXPORT RPolylineProxy {
public:
    virtual ~RPolylineProxy() {}
    virtual RS::Ending getTrimEnd(RPolyline& polyline, const RVector& trimPoint, const RVector& clickPoint) = 0;
    virtual void trimStartPoint(RPolyline& polyline, const RVector& trimPoint, const RVector& clickPoint) = 0;
    virtual void trimEndPoint(RPolyline& polyline, const RVector& trimPoint, const RVector& clickPoint) = 0;

    virtual QList<RPolyline> renderThickPolyline(const RPolyline& polyline) = 0;
    virtual QList<RVector> verifyTangency(const RPolyline& polyline, double toleranceMin = RS::AngleTolerance, double toleranceMax = M_PI_4) = 0;
};

#endif
