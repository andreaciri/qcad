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
#include "RPainterPathExporter.h"

void RPainterPathExporter::exportLineSegment(const RLine& line, double angle) {
    if (line.getLength()<RS::PointTolerance) {
        if (exportZeroLinesAsPoints) {
            path.addPoint(line.getStartPoint());
        }
        else {
            // Qt won't export a zero length line as point:
            // e.g. dot in a dash/dot line:
            RVector startPoint = line.startPoint - RVector::createPolar(0.01, angle);
            RVector endPoint = line.endPoint + RVector::createPolar(0.01, angle);
            path.moveTo(startPoint);
            path.lineTo(endPoint);
//            path.moveTo(line.getStartPoint()-RVector(0.01,0));
//            path.lineTo(line.getEndPoint()+RVector(0.01, 0));
//            path.moveTo(line.getStartPoint()-RVector(0,0.01));
//            path.lineTo(line.getEndPoint()+RVector(0, 0.01));
        }
    }
    else {
        path.moveTo(line.getStartPoint());
        path.lineTo(line.getEndPoint());
    }
}

void RPainterPathExporter::exportPainterPaths(const QList<RPainterPath>& paths) {
    for (int i=0; i<paths.length(); i++) {
        path.addPath(paths[i]);
    }
}

RPainterPath RPainterPathExporter::getPainterPath() {
    RPainterPath ret = path;
    path = RPainterPath();
    return ret;
}
