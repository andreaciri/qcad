#include <QMenuBar>
#include <math.h>

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
#include "Room.hpp"


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


QString CoveragePlugin::start(){
    int BoundingCoo[4][2];
    int i, j, estimateMin, estimateMax, maxRange, minRange;
    float currentCoverage;
    int numberOfRooms = this->roomSides.length();
    QList<Room> rooms;

    j = 0;
    for(i = 0; i < numberOfRooms; i++){
        Room *r = new Room(i, this->floorPoints.mid(j, this->roomSides[i]));
        rooms.append(*r);
        j += this->roomSides[i];
    }
    //return QString("temp ERROR");

    for(i = 0; i < this->boundingBox.length(); i++){
        BoundingCoo[i][0] = (int) this->boundingBox[i].getX();
        BoundingCoo[i][1] = (int) this->boundingBox[i].getY();
    }

    ProblemData* pData = LoadData(BoundingCoo, this->sensorRange, this->sensorCost, this->wantCandidates, this->candidates, rooms);

    maxRange = 0;
    minRange = 0;
    for (i=1; i<this->sensorRange.size();i++){
        if(this->sensorRange[i] > this->sensorRange[maxRange])
            maxRange = i;
        else if(this->sensorRange[i] < this->sensorRange[minRange])
            minRange = i;
    }

    estimateMin = (int) floor((pData->nr * this->aimedCoverage) / ((this->sensorRange[maxRange]) * (this->sensorRange[maxRange]) * 3.14));
    estimateMax = (int) floor((pData->nr * this->aimedCoverage) / ((this->sensorRange[minRange]) * (this->sensorRange[minRange]) * 3.14));
    if(estimateMin == 0)
        estimateMin = 1;
    if(estimateMax == 0)
        estimateMax = 1;
    if(this->wantCandidates && estimateMin > this->candidates.length()){
        return QString("ERROR: INSUFFICIENT CANDIDATE SITES FOR THE AIMED COVERAGE.");
    }


    if(this->sensorRange.length() <= 1){
        pData->card[1] = estimateMin;
        solution currentSol = vnsheuristic(*pData);
        currentCoverage = ((float) currentSol.sparseMR.size() / (float) (pData->nr));
        for(i = estimateMin + 1; currentCoverage < aimedCoverage; i++){
                if(this->wantCandidates && i > this->candidates.length()){
                    return QString("ERROR: INSUFFICIENT CANDIDATE SITES FOR THE AIMED COVERAGE.");
                }

                pData->card[1] = i;

                currentSol = vnsheuristic(*pData);
                currentCoverage = ((float) currentSol.sparseMR.size() / (float) (pData->nr));
            }

            QString resultJSON = generateJSONResult(pData, currentSol.sparseMC, currentCoverage);
            //DestroyProblemData(&pData);
            return resultJSON;
    }

    pData->card[1] = estimateMin;
    solution lowerSol = vnsheuristic(*pData);
    pData->card[1] = estimateMax;
    solution upperSol = vnsheuristic(*pData);
    solution currentSol = binarySearch(estimateMin, lowerSol, estimateMax, upperSol, aimedCoverage);
    currentCoverage = ((float) currentSol.sparseMR.size() / (float) (currentSol.ins.nr));


    QString resultJSON = generateJSONResult(pData, currentSol.sparseMC, currentCoverage);
    //DestroyProblemData(&pData);
    return resultJSON;
}

solution binarySearch(int low, solution lower, int up, solution upper, float aimedCoverage){

    int lowerCoverage = ((float) lower.sparseMR.size() / (float) low);
    int upperCoverage = ((float) upper.sparseMR.size() / (float) up);
    int medium = (low + up)/2;
    if(medium - low < 2){
        if(lowerCoverage < aimedCoverage && upperCoverage >= aimedCoverage)
            return upper;
        if(lowerCoverage >= aimedCoverage && upperCoverage < aimedCoverage)
            return lower;
        return (lower.cost > upper.cost) ? lower : upper;
    }

    lower.ins.card[1] = medium;
    solution currentSol = vnsheuristic(lower.ins);
    if(lowerCoverage < aimedCoverage && upperCoverage >= aimedCoverage)
        return binarySearch(medium, currentSol, up, upper, aimedCoverage);
    if(lowerCoverage >= aimedCoverage && upperCoverage < aimedCoverage)
        return binarySearch(low, lower, medium, currentSol, aimedCoverage);
    return (lower.cost > upper.cost) ? binarySearch(low, lower, medium, currentSol, aimedCoverage) : binarySearch(medium, currentSol, up, upper, aimedCoverage);;

}

//TODO: funzione totalPrice per soluzione

QString generateJSONResult(ProblemData* pData, SMC sparseMC, float coverageRate){
    int i, x, y, m, c;
    i = 0;
    QString cooString = "[";
    qDebug("VNS Heuristic:");
    for(const auto& antenna: sparseMC){
        i++;
        c = antenna.column;
        x = pData->columns[c][0];
        y = pData->columns[c][1];
        m = (((c-1) - ((c-1) % pData->truenc)) / pData->truenc)+1;
        qDebug("Antenna %d: (x= %d, y= %d)", i, x, y);
        if(i>1){
            QTextStream(&cooString) << ", ";
        }
        QTextStream(&cooString) << "{x:" << x << ", y:" << y << ", m:" << m << "}";
    }
    QTextStream(&cooString) << "]";
    qDebug("Current coverage: %f", coverageRate);


    QString resultJSON;
    QTextStream(&resultJSON) << "{fornitureQuantity:" << i << ", coverage:" << coverageRate << ", coordinates:" << cooString << "}";
    return resultJSON;
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
    else if(context->argumentCount()==8 && context->argument(3).isArray()) {
        CoveragePlugin* cppResult = new CoveragePlugin();
        QList<RVector> fP;
        QList<RVector> cand;
        QList<RVector> box;
        QList<int> rs;
        QVector<int> range;
        QVector<int> cost;
        float aimedCoverage;
        bool wantCandidates;

        // convert ECMAScript parameters to C++ variables:
        REcmaHelper::fromScriptValue(engine, context->argument(0), range);
        cppResult->sensorRange = range;
        REcmaHelper::fromScriptValue(engine, context->argument(1), fP);
        cppResult->floorPoints = fP;
        REcmaHelper::fromScriptValue(engine, context->argument(2), cand);
        cppResult->candidates = cand;
        REcmaHelper::fromScriptValue(engine, context->argument(3), box);
        cppResult->boundingBox = box;
        wantCandidates = context->argument(4).toBool();
        cppResult->wantCandidates = wantCandidates;
        aimedCoverage = context->argument(5).toNumber() / 100.00;
        cppResult->aimedCoverage = aimedCoverage;
        REcmaHelper::fromScriptValue(engine, context->argument(6), rs);
        cppResult->roomSides = rs;
        REcmaHelper::fromScriptValue(engine, context->argument(7), cost);
        cppResult->sensorCost = cost;
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
