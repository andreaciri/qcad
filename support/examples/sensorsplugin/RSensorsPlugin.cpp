#include <QMenuBar>

#include "REcmaHelper.h"
#include "RSensorsPlugin.h"
#include "RSettings.h"
#include "RPluginInfo.h"
#include "RVersion.h"
#include "RMainWindowQt.h"
#include "solution.hpp"
#include "greedy.hpp"
#include "util.hpp"
#include "vnsheuristic.hpp"


bool RSensorsPlugin::init() {
    qDebug() << "RSensorsPlugin::init";
    return true;
}

void RSensorsPlugin::postInit(InitStatus status) {
    if (status!=RPluginInterface::AllDone) {
        return;
    }
    RMainWindowQt* appWin = RMainWindowQt::getMainWindow();
    RGuiAction* guiAction = new RGuiAction("My CPP Action", appWin);
    guiAction->setRequiresDocument(true);
    //guiAction->setScriptFile(basePath + "/Line2P.js");
    //guiAction->setIcon(basePath + "/Line2P.svg");
    //guiAction->setStatusTip(qsTranslate("Line2P", "Draw single line or sequence of lines"));
    //guiAction->setDefaultShortcut(new QKeySequence("l,i"));
    guiAction->setGroupSortOrder(100000);
    guiAction->setSortOrder(100);

    QMenuBar* menuBar = appWin->menuBar();
    QMenu* menu = menuBar->findChild<QMenu*>("MiscMenu");
    //menu->addAction(guiAction);
    guiAction->addToMenu(menu);

    guiAction->setFactory(MyAction::factory);
    //MyAction* action = new MyAction(guiAction);


}

void RSensorsPlugin::initScriptExtensions(QScriptEngine& engine) {
    qDebug() << "RSensorsPlugin::initScriptExtensions";

    QScriptValue* proto = new QScriptValue(engine.newVariant(qVariantFromValue((CoveragePlugin*)0)));

    // base class:
    QScriptValue dpt = engine.defaultPrototype(qMetaTypeId<QObject*>());
    proto->setPrototype(dpt);

    REcmaHelper::registerFunction(&engine, proto, RSensorsPlugin::CoveragePluginToString, "toString");

    engine.setDefaultPrototype(qMetaTypeId<CoveragePlugin*>(), *proto);
                        
    //qScriptRegisterMetaType<CoveragePlugin*>(&engine, toScriptValue, fromScriptValue, *proto);

    QScriptValue ctor = engine.newFunction(RSensorsPlugin::createCoveragePlugin, *proto, 0);

    engine.globalObject().setProperty("CoveragePlugin", ctor, QScriptValue::SkipInEnumeration);
}

RPluginInfo RSensorsPlugin::getPluginInfo() {
    RPluginInfo ret;
    ret.set("Version", R_QCAD_VERSION_STRING);
    ret.set("ID", "Sensors");
    ret.set("Name", "Sensors Plugin");
    ret.set("License", "GPLv3");
    ret.set("URL", "http://qcad.org");
    return ret;
}


void CoveragePlugin::start(){
    if(this->wantCandidates){
        qDebug("Aimed Coverage: %f:", this->aimedCoverage);
    }
    int BoundingCoo[4][2];
    int i;
    for(i = 0; i < this->boundingBox.length(); i++){
        BoundingCoo[i][0] = (int) this->boundingBox[i].getX();
        BoundingCoo[i][1] = (int) this->boundingBox[i].getY();
    }

    ProblemData& pData=(*LoadData(BoundingCoo, this->sensorRange));
    solution currentSol = vnsheuristic(pData);

    i=0;
    qDebug("VNS Heuristic:");
    for(const auto& antenna: currentSol.sparseMC){
        i++;
        qDebug("Antenna %d: (x= %d, y= %d)", i, pData.columns[antenna.column][0], pData.columns[antenna.column][1]);
    }

}

/**
 * Constructor for CoveragePlugin:
 */
QScriptValue RSensorsPlugin::createCoveragePlugin(QScriptContext* context, QScriptEngine* engine) {
    if (context->thisObject().strictlyEquals(engine->globalObject())) {
        return REcmaHelper::throwError(QString::fromLatin1("CoveragePlugin(): Did you forget to construct with 'new'?"), context);
    }
    
    // constructor without arguments:
    if(context->argumentCount() == 0) {
        CoveragePlugin* cppResult = new CoveragePlugin();
        return engine->newQObject(context->thisObject(), cppResult);
    }
    else if(context->argumentCount()==6 && context->argument(3).isArray()) {
        CoveragePlugin* cppResult = new CoveragePlugin();
        QList<RVector> fP;
        QList<RVector> cand;
        QList<RVector> box;
        int range;
        float aimedCoverage;
        bool wantCandidates;

        // convert ECMAScript array to QList<RVector>:
        range = context->argument(0).toInt32();
        cppResult->sensorRange = range;
        REcmaHelper::fromScriptValue(engine, context->argument(1), fP);
        cppResult->floorPoints = fP;
        REcmaHelper::fromScriptValue(engine, context->argument(2), cand);
        cppResult->candidates = cand;
        REcmaHelper::fromScriptValue(engine, context->argument(3), box);
        cppResult->boundingBox = box;
        wantCandidates = context->argument(4).toBool();
        cppResult->wantCandidates = wantCandidates;
        aimedCoverage = context->argument(5).toNumber();
        cppResult->aimedCoverage = aimedCoverage;
        return engine->newQObject(context->thisObject(), cppResult);
    }
    else {
        return REcmaHelper::throwError(QString::fromLatin1("CoveragePlugin(): no matching constructor found."), context);
    }
}

/**
 * CoveragePlugin::toString
 */
QScriptValue RSensorsPlugin::CoveragePluginToString(QScriptContext *context, QScriptEngine *engine) {
    Q_UNUSED(engine)

    CoveragePlugin* self = getSelfCoveragePlugin("toString", context);
    return QScriptValue(QString("CoveragePlugin(0x%1)").arg((unsigned long int)self, 0, 16));
}

CoveragePlugin* RSensorsPlugin::getSelfCoveragePlugin(const QString& fName, QScriptContext* context) {
    CoveragePlugin* self = REcmaHelper::scriptValueTo<CoveragePlugin >(context->thisObject());
    if (self == NULL){
        if (fName!="toString") {
            REcmaHelper::throwError(QString("CoveragePlugin.%1(): This object is not a CoveragePlugin").arg(fName), context);
        }
        return NULL;
    }
    
    return self;
}


#if QT_VERSION < 0x050000
QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(Sensors, RSensorsPlugin)
QT_END_NAMESPACE
#endif
