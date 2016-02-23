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

include("../IsometricGridTop/IsometricGridTop.js");

/**
 * \class IsometricGridRight
 * \brief Switches isometric grid to right side view.
 * \ingroup ecma_view
 */
function IsometricGridRight(guiAction) {
    IsometricGridTop.call(this, guiAction);
    this.proj = RS.IsoRight;
}

IsometricGridRight.prototype = new IsometricGridTop();

IsometricGridRight.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Right Projection"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/IsometricGridRight.js");
    action.setRequiresDocument(true);
    action.setIcon(basePath + "/IsometricGridRight.svg");
    action.setDefaultShortcut(new QKeySequence("j,r"));
    action.setDefaultCommands(["isometricgridright", "jr"]);
    action.setGroup("isometricProjection");
    action.setNoState(true);
    action.setGroupSortOrder(3500);
    action.setSortOrder(300);
    action.setWidgetNames(["ViewMenu", "IsometricViewToolBar", "ViewToolsPanel", "ViewMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    var fl = new ProjectionFocusListener(action, RS.IsoRight);
    appWin.addViewFocusListener(fl);
};
