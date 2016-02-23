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
#include "RTextBasedEntity.h"
#include "RExporter.h"

RPropertyTypeId RTextBasedEntity::PropertyCustom;
RPropertyTypeId RTextBasedEntity::PropertyHandle;
RPropertyTypeId RTextBasedEntity::PropertyType;
RPropertyTypeId RTextBasedEntity::PropertyBlock;
RPropertyTypeId RTextBasedEntity::PropertyLayer;
RPropertyTypeId RTextBasedEntity::PropertyLinetype;
RPropertyTypeId RTextBasedEntity::PropertyLinetypeScale;
RPropertyTypeId RTextBasedEntity::PropertyLineweight;
RPropertyTypeId RTextBasedEntity::PropertyColor;
RPropertyTypeId RTextBasedEntity::PropertyDisplayedColor;
RPropertyTypeId RTextBasedEntity::PropertyDrawOrder;

RPropertyTypeId RTextBasedEntity::PropertySimple;
RPropertyTypeId RTextBasedEntity::PropertyPositionX;
RPropertyTypeId RTextBasedEntity::PropertyPositionY;
RPropertyTypeId RTextBasedEntity::PropertyPositionZ;
RPropertyTypeId RTextBasedEntity::PropertyText;
RPropertyTypeId RTextBasedEntity::PropertyPlainText;
RPropertyTypeId RTextBasedEntity::PropertyFontName;
RPropertyTypeId RTextBasedEntity::PropertyHeight;
RPropertyTypeId RTextBasedEntity::PropertyAngle;
RPropertyTypeId RTextBasedEntity::PropertyXScale;
RPropertyTypeId RTextBasedEntity::PropertyBold;
RPropertyTypeId RTextBasedEntity::PropertyItalic;
RPropertyTypeId RTextBasedEntity::PropertyLineSpacingFactor;
RPropertyTypeId RTextBasedEntity::PropertyHAlign;
RPropertyTypeId RTextBasedEntity::PropertyVAlign;


RTextBasedEntity::RTextBasedEntity(RDocument* document, RObject::Id objectId) :
    REntity(document, objectId) {
}

RTextBasedEntity::~RTextBasedEntity() {
}

void RTextBasedEntity::init() {
    RTextBasedEntity::PropertyCustom.generateId(typeid(RTextBasedEntity), RObject::PropertyCustom);
    RTextBasedEntity::PropertyHandle.generateId(typeid(RTextBasedEntity), RObject::PropertyHandle);
    RTextBasedEntity::PropertyType.generateId(typeid(RTextBasedEntity), REntity::PropertyType);
    RTextBasedEntity::PropertyBlock.generateId(typeid(RTextBasedEntity), REntity::PropertyBlock);
    RTextBasedEntity::PropertyLayer.generateId(typeid(RTextBasedEntity), REntity::PropertyLayer);
    RTextBasedEntity::PropertyLinetype.generateId(typeid(RTextBasedEntity), REntity::PropertyLinetype);
    RTextBasedEntity::PropertyLinetypeScale.generateId(typeid(RTextBasedEntity), REntity::PropertyLinetypeScale);
    RTextBasedEntity::PropertyLineweight.generateId(typeid(RTextBasedEntity), REntity::PropertyLineweight);
    RTextBasedEntity::PropertyColor.generateId(typeid(RTextBasedEntity), REntity::PropertyColor);
    RTextBasedEntity::PropertyDisplayedColor.generateId(typeid(RTextBasedEntity), REntity::PropertyDisplayedColor);
    RTextBasedEntity::PropertyDrawOrder.generateId(typeid(RTextBasedEntity), REntity::PropertyDrawOrder);

    RTextBasedEntity::PropertySimple.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Simple"));
    RTextBasedEntity::PropertyPositionX.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "X"));
    RTextBasedEntity::PropertyPositionY.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RTextBasedEntity::PropertyPositionZ.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RTextBasedEntity::PropertyText.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Text"));
    RTextBasedEntity::PropertyPlainText.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Plain Text"));
    RTextBasedEntity::PropertyFontName.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Font Name"));
    RTextBasedEntity::PropertyHeight.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Text Height"));
    RTextBasedEntity::PropertyAngle.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Text Angle"));
    RTextBasedEntity::PropertyXScale.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "X Scale"));
    RTextBasedEntity::PropertyBold.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Bold"));
    RTextBasedEntity::PropertyItalic.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Italic"));
    RTextBasedEntity::PropertyLineSpacingFactor.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Line Spacing"));
    RTextBasedEntity::PropertyHAlign.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Horizontal"));
    RTextBasedEntity::PropertyVAlign.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Vertical"));
}

bool RTextBasedEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(getData().simple, value, PropertySimple == propertyTypeId);
    ret = ret || RObject::setMember(getData().alignmentPoint.x, value, PropertyPositionX == propertyTypeId);
    ret = ret || RObject::setMember(getData().alignmentPoint.y, value, PropertyPositionY == propertyTypeId);
    ret = ret || RObject::setMember(getData().alignmentPoint.z, value, PropertyPositionZ == propertyTypeId);
    ret = ret || RObject::setMember(getData().text, value, PropertyText == propertyTypeId);
    ret = ret || RObject::setMember(getData().fontName, value, PropertyFontName == propertyTypeId);
    ret = ret || RObject::setMember(getData().textHeight, value, PropertyHeight == propertyTypeId);
    ret = ret || RObject::setMember(getData().angle, value, PropertyAngle == propertyTypeId);
    ret = ret || RObject::setMember(getData().xScale, value, PropertyXScale == propertyTypeId);
    ret = ret || RObject::setMember(getData().bold, value, PropertyBold == propertyTypeId);
    ret = ret || RObject::setMember(getData().italic, value, PropertyItalic == propertyTypeId);
    ret = ret || RObject::setMember((int&)getData().horizontalAlignment, value.value<int>(), PropertyHAlign == propertyTypeId);
    ret = ret || RObject::setMember((int&)getData().verticalAlignment, value.value<int>(), PropertyVAlign == propertyTypeId);

    if (PropertyLineSpacingFactor == propertyTypeId) {
        if (value.toDouble()>=0.0) {
            ret = ret || RObject::setMember(getData().lineSpacingFactor, value, true);
        }
    }

    if (ret) {
        getData().update();
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> RTextBasedEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes) {
    if (propertyTypeId == PropertySimple) {
        return qMakePair(QVariant(getData().simple), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionX) {
        return qMakePair(QVariant(getData().alignmentPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionY) {
        return qMakePair(QVariant(getData().alignmentPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionZ) {
        return qMakePair(QVariant(getData().alignmentPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyText) {
        return qMakePair(QVariant(getData().text),
            RPropertyAttributes(RPropertyAttributes::RichText|RPropertyAttributes::Label));
    } else if (propertyTypeId == PropertyPlainText) {
        return qMakePair(QVariant(getData().getPlainText()),
                         RPropertyAttributes(RPropertyAttributes::Label|RPropertyAttributes::ReadOnly));
    } else if (propertyTypeId == PropertyFontName) {
        return qMakePair(QVariant(getData().fontName),
            RPropertyAttributes(RPropertyAttributes::Style));
    } else if (propertyTypeId == PropertyHeight) {
        return qMakePair(QVariant(getData().textHeight), RPropertyAttributes());
    } else if (propertyTypeId == PropertyAngle) {
        return qMakePair(QVariant(getData().angle), RPropertyAttributes(
            RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyXScale) {
        return qMakePair(QVariant(getData().xScale), RPropertyAttributes());
    } else if (propertyTypeId == PropertyBold) {
        return qMakePair(QVariant(getData().bold), RPropertyAttributes());
    } else if (propertyTypeId == PropertyItalic) {
        return qMakePair(QVariant(getData().italic), RPropertyAttributes());
    } else if (propertyTypeId == PropertyLineSpacingFactor) {
        return qMakePair(QVariant(getData().lineSpacingFactor), RPropertyAttributes());
    } else if (propertyTypeId == PropertyHAlign) {
//        return qMakePair(QVariant(getData().horizontalAlignment), RPropertyAttributes(RPropertyAttributes::AffectsOtherProperties));
        return qMakePair(QVariant(getData().horizontalAlignment), RPropertyAttributes());
    } else if (propertyTypeId == PropertyVAlign) {
//        return qMakePair(QVariant(getData().verticalAlignment), RPropertyAttributes(RPropertyAttributes::AffectsOtherProperties));
        return qMakePair(QVariant(getData().verticalAlignment), RPropertyAttributes());
    }
    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RTextBasedEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);

    if (RSettings::isTextRenderedAsText()) {
        QList<RPainterPath> paths = e.exportText(getData(), forceSelected);
        e.exportPainterPaths(paths);
    }
    else {
        e.exportPainterPathSource(getData());
    }
}

void RTextBasedEntity::print(QDebug dbg) const {
    dbg.nospace() << "RTextBasedEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", alignmentPoint: " << getAlignmentPoint()
                  << ", position: " << getPosition()
                  << ", text: " << getPlainText()
                  << ", textHeight: " << getTextHeight()
                  << ", textWidth: " << getTextWidth()
                  << ", drawingDirection: " << getDrawingDirection()
                  << ")";
}
