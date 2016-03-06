include("../SmartBuilding.js");

/**
 * \class CandidatePoint
 * \brief Point from position.
 * \ingroup ecma_draw_point
 */
function CandidatePoint(guiAction) {
    SmartBuilding.call(this, guiAction);

    this.point = undefined;
}

CandidatePoint.State = {
    SettingPosition : 0
};

CandidatePoint.prototype = new SmartBuilding();
CandidatePoint.includeBasePath = includeBasePath;

CandidatePoint.prototype.beginEvent = function() {
    SmartBuilding.prototype.beginEvent.call(this);

    this.setState(CandidatePoint.State.SettingPosition);
};

CandidatePoint.prototype.setState = function(state) {
    SmartBuilding.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var trPos = qsTr("Position");
    this.setCommandPrompt(trPos);
    this.setLeftMouseTip(trPos);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

CandidatePoint.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    this.point = event.getModelPosition();
    if (preview) {
        this.updatePreview();
    }
    else {
        di.setRelativeZero(this.point);
        this.applyOperation();
    }
};

CandidatePoint.prototype.getOperation = function(preview) {
    if (!isVector(this.point)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var e = new RPointEntity(
        this.getDocument(),
        new RPointData(this.point)
    );
    e.setCustomProperty("QCAD", "isCandidate", "1");
    op.addObject(e);
    return op;
};

CandidatePoint.init = function(basePath) {
    var action = new RGuiAction(qsTranslate("CandidatePoint", "Candidate &Point"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/CandidatePoint.js");
    action.setIcon(basePath + "/CandidatePoint.svg");
    action.setStatusTip(qsTranslate("CandidatePoint", "Place candidate points"));
    action.setDefaultShortcut(new QKeySequence("c,p"));
    action.setDefaultCommands(["candidate", "cp"]);
    action.setGroupSortOrder(80100);
    action.setSortOrder(200);
    action.setWidgetNames(["SmartBuildingMenu", "SmartBuildingToolBar", "SmartBuildingToolsPanel", "SmartBuildingMatrixPanel"]);
};