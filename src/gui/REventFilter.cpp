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
#include <QCoreApplication>
#include <QWheelEvent>

#include "REventFilter.h"

/**
 * Event filter. If type is QEvent::None, all events are filtered.
 */
REventFilter::REventFilter(QEvent::Type type, bool forward) : type(type), forward(forward) {
}

bool REventFilter::eventFilter(QObject* obj, QEvent* event) {
    if (type==QEvent::None || event->type() == type) {
        if (forward) {
            QObject* parent = obj->parent();
            if (parent!=NULL) {
                QCoreApplication::sendEvent(parent, event);
            }
        }
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
