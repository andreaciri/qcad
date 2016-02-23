// SmartBuilding.js
// All actions are derived from class Draw, so we need to 
// include this class definition here:
include("../Draw/Draw.js");
// Constructor calls base class constructor:
function SmartBuilding(guiAction) {
    Draw.call(this, guiAction);
}
// Derive class SmartBuilding from class Draw:
SmartBuilding.prototype = new Draw();
SmartBuilding.includeBasePath = includeBasePath;

SmartBuilding.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="SmartBuildingToolsPanelAction") {
        EAction.showCadToolBarPanel("SmartBuildingToolsPanel");
        this.terminate();
    }
};

SmartBuilding.prototype.createLineEntity = function(doc, p1, p2) {
    return new RLineEntity(doc, new RLineData(p1, p2));
};

// This static function returns a new or existing QMenu object.
SmartBuilding.getMenu = function() {
    // Draw.getMenu is a helper function that returns an existing 
    // or new QMenu object with the given title and object name.
    // The object name (here "SmartBuildingMenu") must be unique. 
    return EAction.getMenu(SmartBuilding.getTitle(), "SmartBuildingMenu");
};
// This static function returns a new or existing QToolBar object.
SmartBuilding.getToolBar = function() {
    // Draw.getToolBar is a helper function that returns an existing 
    // or new QToolBar object with the given title and object name.
    // The object name (here "SmartBuildingToolBar") must be unique. 
    var tb = EAction.getToolBar(SmartBuilding.getTitle(), "SmartBuildingToolBar");
    tb.visible = false;
    return tb;
};

SmartBuilding.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(SmartBuilding.getTitle(), "SmartBuildingMatrixPanel", 3500);
};

SmartBuilding.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "SmartBuildingToolsPanelAction";
    if (!isNull(mtb) && isNull(mtb.findChild(actionName))) {
        var action = new RGuiAction(qsTr("SmartBuilding Tools"), mtb);
        action.setScriptFile(SmartBuilding.includeBasePath + "/SmartBuilding.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(SmartBuilding.includeBasePath + "/SmartBuilding.svg");
        action.setStatusTip(qsTr("Smart Building tools"));
        action.setDefaultShortcut(new QKeySequence("s,b"));
        action.setNoState();
        action.setDefaultCommands(["smartmenu"]);
        action.setGroupSortOrder(55);
        action.setSortOrder(101);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(SmartBuilding.getTitle(), "SmartBuildingToolsPanel", true);
    return tb;
};

// This static function defines and returns the title of the menu 
// and toolbar.
// The qsTr function marks the title as a translatable string.
SmartBuilding.getTitle = function() {
    return qsTr("Smart Building");
};
// Init creates the menu and toolbar on start.
SmartBuilding.init = function() {
    SmartBuilding.getMenu();
    SmartBuilding.getToolBar();
    SmartBuilding.getCadToolBarPanel();
    SmartBuilding.getToolMatrixPanel();
};