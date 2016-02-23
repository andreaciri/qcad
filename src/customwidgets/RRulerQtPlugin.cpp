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
#include <QtPlugin>

#include "RRulerQt.h"
#include "RRulerQtPlugin.h"

RRulerQtPlugin::RRulerQtPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RRulerQtPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RRulerQtPlugin::isInitialized() const {
    return initialized;
}

QWidget *RRulerQtPlugin::createWidget(QWidget *parent) {
    return new RRulerQt(parent);
}

QString RRulerQtPlugin::name() const {
    return "RRulerQt";
}

QString RRulerQtPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RRulerQtPlugin::icon() const {
    return QIcon();
}

QString RRulerQtPlugin::toolTip() const {
    return "";
}

QString RRulerQtPlugin::whatsThis() const {
    return "";
}

bool RRulerQtPlugin::isContainer() const {
    return false;
}

QString RRulerQtPlugin::domXml() const {
    return "<ui language=\"c++\">\n"
        " <widget class=\"RRulerQt\" name=\"ruler\">\n"
        " </widget>\n"
        "</ui>\n";
}

QString RRulerQtPlugin::includeFile() const {
    return "RRulerQt.h";
}
