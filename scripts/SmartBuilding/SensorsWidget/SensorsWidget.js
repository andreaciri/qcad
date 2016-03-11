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

//! [main]
//! [include]
include("scripts/WidgetFactory.js");
//! [include]
include("../SmartBuilding.js");

function SensorsWidget(guiAction) {
    SmartBuilding.call(this, guiAction);
}

SensorsWidget.prototype = new SmartBuilding();
SensorsWidget.includeBasePath = includeBasePath;

//! [beginEvent]
SensorsWidget.prototype.beginEvent = function() {
    SmartBuilding.prototype.beginEvent.call(this);

    // Create the dialog from the .ui file using the helper
    // function WidgetFactory.createWidget().
    var dialog = WidgetFactory.createWidget(
            SensorsWidget.includeBasePath,
            "SensorsWidget.ui");

    // Restore the previous user data or display default values as
    // set in Qt Designer:
    WidgetFactory.restoreState(dialog);

    // Display and execute the dialog:
    if (!dialog.exec()) {
        dialog.destroy();
        EAction.activateMainWindow();
        // User hit cancel:
        this.terminate();
        return;
    }

    // User hit OK. Store the new user input:
    WidgetFactory.saveState(dialog);
    var widgets = getWidgets(dialog);
    var sensorRange = widgets["SensorRange"].text;
    var aimedCoverage = widgets["AimedCoverage"].value;
    var wantCandidates = widgets["Candidates"].checked;

    // Print the user input to the QCAD console:
    var appWin = EAction.getMainWindow();
    appWin.handleUserMessage("Sensor Range: " + sensorRange);

    var allEntities = this.getDocument().queryAllEntities(false, false, RS.EntityAll);
    var ent;
    var typeKey;
    var floorPoints = [];
    var candidates = [];

    for(i=0; i<allEntities.length; i++){

        ent = this.getDocument().queryEntity(allEntities[i]);
        typeKey = ent.getCustomPropertyKeys("QCAD");

        if(typeKey[0] == "isFloorplan"){
            floorPoints.push(ent.getStartPoint());
        }
        else if(typeKey[0] == "isCandidate") {
            candidates.push(ent.getPosition());
        }
            else{
                appWin.handleUserMessage("this is not a smartbuilding entity: " + allEntities[i]);
                appWin.handleUserMessage("typeKey content: " + typeKey[0]);
        }

    }

    var boundingBox = this.getDocument().getBoundingBox().getCorners2d();
    appWin.handleUserMessage("Floorplan points: " + floorPoints);
    appWin.handleUserMessage("Candidate points: " + candidates);
    appWin.handleUserMessage("Bounding box corners: " + boundingBox);
    appWin.handleUserMessage("Aimed percentage of coverage: " + aimedCoverage +"%");
    appWin.handleUserMessage("Using candidate points: " + (wantCandidates? "Yes" : "No"));

    var coveragePlugin = new CoveragePlugin(sensorRange, floorPoints, candidates, boundingBox, wantCandidates, aimedCoverage);
    var resultJSON = coveragePlugin.start();
    var resultObj = eval('(' + resultJSON + ')');
    appWin.handleUserMessage("resultJSON: " + resultJSON);
    appWin.handleUserMessage("COVERAGE RATE: " + (resultObj.coverage*100)+"%");
    //appWin.handleUserMessage("PROVA COO: " + resultObj.coordinates);
    appWin.handleUserMessage("FIRST COO: " + resultObj.coordinates[0].x);

    dialog.destroy();
    EAction.activateMainWindow();
    this.terminate();
};
//! [beginEvent]

SensorsWidget.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Sensors Coverage"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SensorsWidget.js");
    action.setGroupSortOrder(80100);
    action.setSortOrder(200);
    action.setWidgetNames(["SmartBuildingMenu"]);
};
//! [main]
