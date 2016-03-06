// Floorplan.js
// Include base class definition:
include("../SmartBuilding.js");
 
// Constructor calls base class constructor:
function Floorplan(guiAction) {
    SmartBuilding.call(this, guiAction);
    // list of points drawn:
    this.pointList = [];
    // index of point that was drawn last, used for tool undo / redo:
    this.pointListIndex = -1;
    // list of entities drawn:
    this.entityIdList = [];

    this.point1 = undefined;
    this.point2 = undefined;

    this.setUiOptions(["Floorplan.ui"]);
}
// Derive class Floorplan from class SmartBuilding:
Floorplan.prototype = new SmartBuilding();

// Indicates whether the tool is going to create the first point or not
Floorplan.State = {
    SettingFirstPoint : 0,
    SettingNextPoint : 1
};

Floorplan.includeBasePath = includeBasePath;
// This function is called immediately after the constructor when the user 
// starts this action. For actions that don't require any user input (for
// example auto zoom), beginEvent does everything and then terminates the
// action.
Floorplan.prototype.beginEvent = function() {
    // call base class implementation of beginEvent:
    SmartBuilding.prototype.beginEvent.call(this);
    
    this.setState(Floorplan.State.SettingFirstPoint);
    this.updateButtonStates();


    // terminate this action immediately:
    //this.terminate();
};

Floorplan.prototype.setState = function(state) {
    SmartBuilding.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

        var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Floorplan.State.SettingFirstPoint:
        var trFirstPoint = qsTr("First point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        this.pointList = [];
        this.pointListIndex = -1;
        this.entityIdList = [];
        break;

    case Floorplan.State.SettingNextPoint:
        var trNextPoint = qsTr("Next point");
        this.setCommandPrompt(trNextPoint);
        this.setLeftMouseTip(trNextPoint);
        this.setRightMouseTip(qsTr("Done"));
        break;
    }

    EAction.showSnapTools();
};

Floorplan.prototype.showUiOptions = function(resume, restoreFromSettings) {
    Draw.prototype.showUiOptions.call(this, resume, restoreFromSettings);

    var optionsToolBar = EAction.getOptionsToolBar();
    this.updateButtonStates();
};

// If there are no setted points, the escape close the tool
// else, delete current line
Floorplan.prototype.escapeEvent = function() {
    
    switch (this.state) {
    case Floorplan.State.SettingFirstPoint:
        EAction.prototype.escapeEvent.call(this);
        return;

    case Floorplan.State.SettingNextPoint:
        this.setState(Floorplan.State.SettingFirstPoint);
        this.updateButtonStates();
        break;
    }
};

Floorplan.prototype.keyPressEvent = function(event) {
    var di = this.getDocumentInterface();

    if ((event.key() === Qt.Key_Enter.valueOf()) || (event.key() === Qt.Key_Return.valueOf())) {
        if (this.state === Floorplan.State.SettingFirstPoint) {
            this.point1 = di.getLastPosition();
            di.setRelativeZero(this.point1);
            this.setState(Floorplan.State.SettingNextPoint);
            di.clearPreview();
            di.previewOperation(this.getOperation(true));
        } else {
            EAction.prototype.keyPressEvent(event);
        }
    } else {
        EAction.prototype.keyPressEvent(event);
    }
};

Floorplan.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Floorplan.State.SettingFirstPoint:
        if (!preview) {
            this.point1 = event.getModelPosition();
            this.pointList.splice(0, 0, this.point1);
            this.pointListIndex = 0;
            di.setRelativeZero(this.point1);
            this.setState(Floorplan.State.SettingNextPoint);
        }
        break;

    case Floorplan.State.SettingNextPoint:
        this.point2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(preview);
            if (!isNull(op)) {
                
                this.pointListIndex++;

                var doc = this.getDocument();
                var trans = di.applyOperation(op);
                var id = this.getLineEntityId(trans);

                this.pointList.splice(this.pointListIndex, 0, this.point2);
                this.entityIdList.splice(this.pointListIndex-1, 0, id);
                di.setRelativeZero(this.point2);
                this.point1 = this.point2;
            }
        }
        break;
    }

    if (!preview) {
        this.updateButtonStates();
    }
};

Floorplan.prototype.getOperation = function(preview) {
    if (!isVector(this.point1) || !isVector(this.point2)) {
        return undefined;
    }
    var e = this.createLineEntity(this.getDocument(), this.point1, this.point2);
    e.setCustomProperty("QCAD", "isFloorplan", "1");
    return new RAddObjectOperation(e, this.getToolTitle());
};

Floorplan.prototype.slotClose = function() {
    if (this.pointList.length >= 3) {
        this.point2 = this.pointList[0];
        this.getDocumentInterface().applyOperation(this.getOperation(false));
        this.pointList.push(this.point2);
        var di = this.getDocumentInterface();
        di.setRelativeZero(this.point2);
        this.setState(Floorplan.State.SettingFirstPoint);
    }
    
    this.updateButtonStates();
};

Floorplan.prototype.slotUndo = function() {
    if (this.pointListIndex > 0) {
        var di = this.getDocumentInterface();
        var doc = this.getDocument();

        this.pointListIndex--;
        this.point1 = this.pointList[this.pointListIndex];
        di.setRelativeZero(this.point1);

        // Delete last line with its entity id
        var id = this.entityIdList[this.pointListIndex];
        var entity = doc.queryEntityDirect(id);
        di.applyOperation(new RDeleteObjectOperation(entity));

        di.clearPreview();
        di.previewOperation(this.getOperation(true));
    }

    this.updateButtonStates();
};

Floorplan.prototype.slotRedo = function() {
    if (this.pointListIndex < this.pointList.length-1) {
        var di = this.getDocumentInterface();
        var doc = this.getDocument();

        this.pointListIndex++;
        this.point1 = this.pointList[this.pointListIndex];
        di.setRelativeZero(this.point1);

        // Create line entity and add it to the document with its id
        var e = this.createLineEntity(doc, this.pointList[this.pointListIndex-1], this.pointList[this.pointListIndex]);
        var trans = di.applyOperation(new RAddObjectOperation(e));
        var id = this.getLineEntityId(trans);
        this.entityIdList[this.pointListIndex-1] = id;

        di.clearPreview();
        di.previewOperation(this.getOperation(true));
    }

    this.updateButtonStates();
};

Floorplan.prototype.updateButtonStates = function() {
    var optionsToolBar = EAction.getOptionsToolBar();

    var w = optionsToolBar.findChild("Undo");
    if (!isNull(w)) {
        if (this.pointListIndex > 0) {
            w.enabled = true;
        } else {
            w.enabled = false;
        }
    }

    w = optionsToolBar.findChild("Redo");
    if (!isNull(w)) {
        //qDebug("this.pointList: ", this.pointList);
        //qDebug("this.pointListIndex: ", this.pointListIndex);
        //qDebug("this.entityIdList.length: ", this.entityIdList.length);
        if (this.pointListIndex >= 0 &&
            this.pointListIndex < this.entityIdList.length) {

            w.enabled = true;
        } else {
            w.enabled = false;
        }
    }
    
    w = optionsToolBar.findChild("Close");
    if (!isNull(w)) {
        if (this.pointList.length > 2) {
            w.enabled = true;
        } else {
            w.enabled = false;
        }
    }
};

Floorplan.prototype.getLineEntityId = function(trans) {
    var objIds = trans.getAffectedObjects();
    for (var i=0; i<objIds.length; i++) {
        var objId = objIds[i];
        var obj = this.getDocument().queryObjectDirect(objId);
        if (isLineEntity(obj)) {
            return obj.getId();
        }
    }
};

/**
 * Allows commands to be entered in command line
 *
 * "Using the 'startsWith' function allows the user to enter only as many characters
 * as needed to distinguish between commands
 * In this case only the first character is needed. (But entering 'c', 'cl', 'clo', 'clos'
 * or 'close' would all invoke the close command. Similarly with undo and redo)"
 *
 */
Floorplan.prototype.commandEvent = function(event) {
    var str;

    var cmd = event.getCommand();
    cmd = cmd.toLowerCase();

    str = "close";
    if (str.startsWith(cmd)) {
        this.slotClose();
        event.accept();
        return;
    }
    str = "undo";
    if (str.startsWith(cmd)) {
        this.slotUndo();
        event.accept();
        return;
    }
    str = "redo";
    if (str.startsWith(cmd)) {
        this.slotRedo();
        event.accept();
        return;
    }
};

Floorplan.getToolBar = function() {
    var tb = EAction.getToolBar(Floorplan.getTitle(), "Floorplan");
    tb.visible = false;
    return tb;
};

Floorplan.getCadToolBarPanel = function() {
    return Floorplan.getCadToolBarPanel();
};

// Floorplan.init() is called by QCAD to initialize the action and create
// the menu / toolbar for it.
Floorplan.init = function(basePath) {
    // Create a new RGuiAction (extended QAction):
    var action = new RGuiAction("&Floorplan", RMainWindowQt.getMainWindow());
    // This action requires a document to be open. If no document is
    // open, the menu and tool button are grayed out:
    action.setRequiresDocument(true);
    // Define the script file that is executed when this action is
    // launched:
    action.setScriptFile(basePath + "/Floorplan.js");
    // Set the icon that is shown in the toolbar and on some platforms
    // also in the menu:
    action.setIcon(basePath + "/Floorplan.svg");
    action.setStatusTip(qsTranslate("Floorplan", "Draw floorplan rooms as closed polygons"));
    // Set the command(s) that can be used on the command line to 
    // launch this action:
    action.setDefaultCommands(["floorplan"]);
    // Define the sort order of this action. Menus and tool buttons are
    // ordered by these values:
    action.setGroupSortOrder(80100);
    action.setSortOrder(100);
    // Set list of widgets this action is added to
    // (menus, tool bars, CAD tool bar panels):
    action.setWidgetNames(["SmartBuildingMenu", "SmartBuildingToolBar", "SmartBuildingToolsPanel", "SmartBuildingMatrixPanel"]);
};