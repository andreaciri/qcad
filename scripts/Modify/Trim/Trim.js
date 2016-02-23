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

include("../Modify.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class Trim
 * \brief Trims an entity to another entity or trims both entities
 * if \c this.trimBoth is true.
 * \ingroup ecma_modify
 */
function Trim(guiAction) {
    Modify.call(this, guiAction);

    this.limitingEntity = undefined;
    this.limitingClickPos = undefined;

    this.trimEntity = undefined;
    this.trimClickPos = undefined;

    this.trimBoth = false;
    this.chooseTrimEntityFirst = false;
}

Trim.prototype = new Modify();

Trim.includeBasePath = includeBasePath;

Trim.State = {
    ChoosingLimitingEntity : 0,
    ChoosingTrimEntity : 1
};

Trim.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    if (this.chooseTrimEntityFirst) {
        this.setState(Trim.State.ChoosingTrimEntity);
    }
    else {
        this.setState(Trim.State.ChoosingLimitingEntity);
    }
};

Trim.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Trim.State.ChoosingLimitingEntity:
        this.limitingEntity = undefined;
        this.limitingClickPos = undefined;
        if (!this.chooseTrimEntityFirst) {
            this.trimEntity = undefined;
            this.trimClickPos = undefined;
        }
        var trLimitingEntity = qsTr("Choose limiting entity");
        this.setCommandPrompt(trLimitingEntity);
        this.setLeftMouseTip(trLimitingEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Trim.State.ChoosingTrimEntity:
        this.trimEntity = undefined;
        this.trimClickPos = undefined;
        if (this.chooseTrimEntityFirst) {
            this.limitingEntity = undefined;
            this.limitingClickPos = undefined;
        }
        var trTrimEntity = qsTr("Choose entity to trim");
        this.setCommandPrompt(trTrimEntity);
        this.setLeftMouseTip(trTrimEntity);
        this.setRightMouseTip(EAction.trBack);
        break;
    }
};

Trim.prototype.escapeEvent = function() {
    switch (this.state) {
    case Trim.State.ChoosingLimitingEntity:
        if (this.chooseTrimEntityFirst) {
            this.setState(Trim.State.ChoosingTrimEntity);
        }
        else {
            Modify.prototype.escapeEvent.call(this);
        }
        break;

    case Trim.State.ChoosingTrimEntity:
        if (this.chooseTrimEntityFirst) {
            Modify.prototype.escapeEvent.call(this);
        }
        else {
            this.setState(Trim.State.ChoosingLimitingEntity);
        }
        break;
    }
};

Trim.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    switch (this.state) {
    case Trim.State.ChoosingLimitingEntity:
        if (isNull(entity) || (this.trimBoth && !EAction.assertEditable(entity, preview))) {
            this.limitingEntity = undefined;
            if (preview) {
                this.updatePreview();
            }
            break;
        }

        var shape = entity.getClosestSimpleShape(pos);

        // unsupported entity chosen:
        if (!this.isSupportedLimitingShape(shape)) {
            if (preview) {
                this.updatePreview();
            }
            else {
                this.warnUnsupportedEntity();
            }
            break;
        }

        this.limitingEntity = entity;
        this.limitingClickPos = pos;
        if (preview) {
            this.updatePreview();
        }
        else {
            if (this.chooseTrimEntityFirst) {
                var op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                }
                this.setState(Trim.State.ChoosingTrimEntity);
            }
            else {
                this.setState(Trim.State.ChoosingTrimEntity);
            }
        }
        break;

    case Trim.State.ChoosingTrimEntity:
        if (isNull(entity) || !EAction.assertEditable(entity, preview)) {
            this.trimEntity = undefined;
            if (preview) {
                this.updatePreview();
            }
            return;
        }

        // unsupported entity chosen:
        if (!this.isSupportedTrimEntity(entity)) {
            this.trimEntity = undefined;
            if (preview) {
                this.updatePreview();
            }
            else {
                this.warnUnsupportedEntity();
            }
            break;
        }

        this.trimEntity = entity;
        this.trimClickPos = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            if (this.chooseTrimEntityFirst) {
                this.setState(Trim.State.ChoosingLimitingEntity);
            }
            else {
                var op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                }
            }

            // trimming both? start asking for next limiting entity
            // otherwise, trim more entities to same limiting entity
            if (this.trimBoth) {
                this.setState(Trim.State.ChoosingLimitingEntity);
            }
        }
        break;
    }
};

Trim.prototype.isSupportedLimitingShape = function(shape) {
    return isLineBasedShape(shape) ||
           isArcShape(shape) ||
           isCircleShape(shape) ||
           isEllipseShape(shape) ||
           (RSpline.hasProxy() && isSplineShape(shape)) ||
           (RPolyline.hasProxy() && isPolylineShape(shape));
};

Trim.prototype.isSupportedTrimEntity = function(entity) {
    return isLineBasedEntity(entity) ||
           isArcEntity(entity) ||
           isCircleEntity(entity) ||
           isEllipseEntity(entity) ||
           (RSpline.hasProxy() && isSplineEntity(entity)) ||
           (RPolyline.hasProxy() && isPolylineEntity(entity));
};

Trim.prototype.warnUnsupportedEntity = function() {
    if (RSpline.hasProxy() && RPolyline.hasProxy()) {
        EAction.warnNotLineArcCircleEllipseSplinePolyline();
    }
    else {
        EAction.warnNotLineArcCircleEllipse();
    }
};

Trim.prototype.getOperation = function(preview) {
    if (!isEntity(this.trimEntity)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var success = Trim.trim(op, this.limitingEntity, this.limitingClickPos, this.trimEntity, this.trimClickPos, this.trimBoth, preview);

    if (!preview) {
        this.trimEntity = undefined;
    }

    if (!success && !preview) {
        EAction.handleUserWarning(qsTr("The two entities don't intersect, or are currently not supported for trimming."));
    }

    return op;
};

Trim.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.limitingEntity)) {
        ret.push(this.limitingEntity.getId());
    }
    if (isEntity(this.trimEntity)) {
        ret.push(this.trimEntity.getId());
    }
    return ret;
};

/**
 * Trims or extends the given trimEntity to the intersection point of the
 * trimEntity and the limitingShape.
 *
 * \param limitingEntity Entity to which the trim entity will be trimmed.
 * \param limitingClickPos Coordinate which defines the intersection to which the
 *    trim entity will be trimmed.
 * \param trimEntity Entity which will be trimmed.
 * \param trimClickPos Coordinate which defines which endpoint of the
 *   trim entity to trim.
 * \param trimBoth true: Trim both entities. false: trim trimEntity only.
 */
Trim.trim = function(op, limitingEntity, limitingClickPos, trimEntity, trimClickPos, trimBoth, preview) {
    if (!isEntity(limitingEntity) || !isValidVector(limitingClickPos) ||
        !isEntity(trimEntity) || !isValidVector(trimClickPos) ||
        !isBoolean(trimBoth)) {
        return false;
    }

    var trimShape = trimEntity.castToShape();
    if (isNull(trimShape)) {
        return false;
    }

    var limitingShape = limitingEntity.castToShape();
    if (isNull(limitingShape)) {
        limitingShape = limitingEntity.getClosestSimpleShape(limitingClickPos);
        if (!isNull(limitingShape)) {
            limitingShape = limitingShape.data();
        }
    }
    if (isNull(limitingShape)) {
        return false;
    }

    var samePolyline = (limitingEntity.getId()===trimEntity.getId() && isPolylineEntity(limitingEntity));
    if (samePolyline) {
        if (!trimBoth) {
            // TODO: fix trimming one segment within same polyline:
            return false;
        }
    }

    var newShapes = Trim.trimShapes(limitingShape, limitingClickPos, trimShape, trimClickPos, trimBoth, samePolyline);
    if (newShapes.length===0) {
        return false;
    }

    if (!modifyEntity(op, trimEntity.clone(), newShapes[0])) {
        if (!preview) {
            if (trimBoth) {
                EAction.handleUserWarning(qsTr("First entity cannot be trimmed."));
            }
            else {
                EAction.handleUserWarning(qsTr("Entity cannot be trimmed."));
            }
        }
    }

    if (newShapes.length===1) {
        // trimming was within same polyline:
        return true;
    }

    if (trimBoth) {
        if (!modifyEntity(op, limitingEntity.clone(), newShapes[1])) {
            if (!preview) {
                EAction.handleUserWarning(qsTr("Second entity cannot be trimmed."));
            }
        }
    }

    return true;
};

/**
 * Trimming on shape level.
 *
 * \param limitingShape Entity to which the trim entity will be trimmed.
 * \param limitingClickPos Coordinate which defines the intersection to which the
 *    trim entity will be trimmed.
 * \param trimShape Shape which will be trimmed.
 * \param trimClickPos Coordinate which defines which endpoint of the
 *   trim entity to trim.
 * \param trimBoth true: Trim both entities. false: trim trimEntity only.
 */
Trim.trimShapes = function(limitingShape, limitingClickPos, trimShape, trimClickPos, trimBoth, samePolyline) {
    var i1, i2, segment;

    var trimShapeSimple = trimShape;
    if (isPolylineShape(trimShape)) {
        i1 = trimShape.getClosestSegment(trimClickPos);
        if (i1<0) {
            return [];
        }
        segment = trimShape.getSegmentAt(i1);
        if (isNull(segment)) {
            return [];
        }
        trimShapeSimple = segment.data();
    }

    var limitingShapeSimple = limitingShape;
    if (isPolylineShape(limitingShape)) {
        i2 = limitingShape.getClosestSegment(limitingClickPos);
        if (i2<0) {
            return [];
        }
        segment = limitingShape.getSegmentAt(i2);
        if (isNull(segment)) {
            return [];
        }
        limitingShapeSimple = segment.data();
    }

    // possible trim points:
    var sol = trimShapeSimple.getIntersectionPoints(limitingShapeSimple, false);
    if (sol.length===0) {
        return [];
    }

    var trimmedShape1;
    var trimmedShape2;
    var c, r, am, a1, a2;
    var mp;

    if (isCircleShape(trimShape)) {
        // convert circle to trimmable arc:
        c = trimShape.getCenter();
        r = trimShape.getRadius();
        am = c.getAngleTo(trimClickPos);
        a1 = RMath.getNormalizedAngle(am-Math.PI/2);
        a2 = RMath.getNormalizedAngle(am+Math.PI/2);
        trimmedShape1 = new RArc(c,r,a1,a2,false);
    }
    else if (isFullEllipseShape(trimShape)) {
        c = trimShape.getCenter();
        mp = trimShape.getMajorPoint();
        r = trimShape.getRatio();
        am = trimShape.getParamTo(trimClickPos);
        a1 = RMath.getNormalizedAngle(am-Math.PI/2);
        a2 = RMath.getNormalizedAngle(am+Math.PI/2);
        trimmedShape1 = new REllipse(c,mp,r,a1,a2,false);
    }
    else {
        if (samePolyline) {
            trimmedShape1 = trimShapeSimple.clone();
        }
        else {
            trimmedShape1 = trimShape.clone();
        }
    }

    if (trimBoth) {
        if (isCircleShape(limitingShape)) {
            // convert circle to trimmable arc:
            c = limitingShape.getCenter();
            r = limitingShape.getRadius();
            am = c.getAngleTo(trimClickPos);
            a1 = RMath.getNormalizedAngle(am-Math.PI/2);
            a2 = RMath.getNormalizedAngle(am+Math.PI/2);
            trimmedShape2 = new RArc(c,r,a1,a2,false);
        }
        else {
            if (samePolyline) {
                trimmedShape2 = limitingShapeSimple.clone();
            }
            else {
                trimmedShape2 = limitingShape.clone();
            }
        }
    }

    // find trim (intersection) point:
    var isIdx;
    if (trimBoth || isEllipseShape(trimShape)) {
        isIdx = trimClickPos.getClosestIndex(sol);
    }
    else {
        isIdx = limitingClickPos.getClosestIndex(sol);
    }
    var is = sol[isIdx];

    var is2;
    if (sol.length===1 || isIdx!==0) {
        is2 = sol[0];
    }
    else {
        is2 = sol[1];
    }

    // trim trim entity:
    var ending1, ending2;

    ending1 = trimmedShape1.getTrimEnd(is, trimClickPos);

    switch (ending1) {
    case RS.EndingStart:
        trimmedShape1.trimStartPoint(is, trimClickPos);
        if (isCircleShape(trimShape) || isFullEllipseShape(trimShape)) {
            trimmedShape1.trimEndPoint(is2, trimClickPos);
        }
        break;
    case RS.EndingEnd:
        trimmedShape1.trimEndPoint(is, trimClickPos);
        if (isCircleShape(trimShape) || isFullEllipseShape(trimShape)) {
            trimmedShape1.trimStartPoint(is2, trimClickPos);
        }
        break;
    default:
        break;
    }

    if (isXLineShape(trimmedShape1)) {
        trimmedShape1 = xLineToRay(trimmedShape1);
    }
    else if (isRayShape(trimShape) && ending1===RS.EndingEnd) {
        trimmedShape1 = rayToLine(trimmedShape1);
    }

    // trim limiting shape if possible (not possible for splines):
    if (trimBoth && isFunction(trimmedShape2.getTrimEnd)) {
        ending2 = trimmedShape2.getTrimEnd(is, limitingClickPos);

        switch (ending2) {
        case RS.EndingStart:
            trimmedShape2.trimStartPoint(is, limitingClickPos);
            if (isCircleShape(limitingShape) || isFullEllipseShape(limitingShape)) {
                trimmedShape2.trimEndPoint(is2, limitingClickPos);
            }
            break;
        case RS.EndingEnd:
            trimmedShape2.trimEndPoint(is, limitingClickPos);
            if (isCircleShape(limitingShape) || isFullEllipseShape(limitingShape)) {
                trimmedShape2.trimStartPoint(is2, limitingClickPos);
            }
            break;
        default:
            break;
        }

        if (isXLineShape(trimmedShape2)) {
            trimmedShape2 = xLineToRay(trimmedShape2);
        }
        else if (isRayShape(trimmedShape2) && ending2===RS.EndingEnd) {
            trimmedShape2 = rayToLine(trimmedShape2);
        }
    }

    if (samePolyline) {
        var pl = ShapeAlgorithms.modifyPolylineCorner(trimShape, trimmedShape1, ending1, i1, limitingShape, trimmedShape2, ending2, i2, undefined);
        return [ pl ];
    }

    return [ trimmedShape1, trimmedShape2 ];
};
