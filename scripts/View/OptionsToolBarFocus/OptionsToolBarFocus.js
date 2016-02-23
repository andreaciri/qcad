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

include("scripts/View/View.js");
include("scripts/Widgets/OptionsToolBar/OptionsToolBar.js");

function OptionsToolBarFocus(guiAction) {
    View.call(this, guiAction);
}

OptionsToolBarFocus.prototype = new View();

OptionsToolBarFocus.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);

    var w = OptionsToolBar.getFirstInputWidget();
    if (!isNull(w)) {
        w.setFocus(Qt.OtherFocusReason);
    }

    this.terminate();
};

