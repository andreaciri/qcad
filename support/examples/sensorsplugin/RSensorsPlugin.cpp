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
#include "moves.hpp"


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
    pData->technique = this->technique;

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

    if(this->technique == 1){
        estimateMin = estimateMin * 3;
        estimateMax = estimateMax * 3;
    }


    if(this->wantCandidates && estimateMin > this->candidates.length()){
        return QString("ERROR: INSUFFICIENT CANDIDATE SITES FOR THE AIMED COVERAGE.");
    }


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

    if(this->sensorRange.length() > 1){
        int startCard = i;
        int increment, tempCoverage;
        increment = (int) (startCard - estimateMax)/3;
        solution tempSol = vnsheuristic(*pData);
        while(i < estimateMax){
            if(increment < 1)
                increment = 1;
            i += increment;
            pData->card[1] = i;
            tempSol = vnsheuristic(*pData);
            tempCoverage = ((float) tempSol.sparseMR.size() / (float) (pData->nr));
            if(tempCoverage >= aimedCoverage && totalPrice(tempSol, this->sensorCost) < totalPrice(currentSol, this->sensorCost)){
                currentCoverage = tempCoverage;
            }
        }
    }

    QString resultJSON = generateJSONResult(pData, currentSol.sparseMC, currentCoverage);
    return resultJSON;

//DestroyProblemData(&pData);
//    pData->card[1] = estimateMin;
//    solution lowerSol = vnsheuristic(*pData);
//    pData->card[1] = estimateMax;
//    solution upperSol = vnsheuristic(*pData);
//    solution currentSol = binarySearch(estimateMin, lowerSol, estimateMax, upperSol, aimedCoverage, this->sensorCost);
//    currentCoverage = ((float) currentSol.sparseMR.size() / (float) (currentSol.ins.nr));
//    qDebug("TOTAL PRICE= %d", totalPrice(currentSol, this->sensorCost));

//    QString resultJSON = generateJSONResult(pData, currentSol.sparseMC, currentCoverage);
//    //DestroyProblemData(&pData);
//    return resultJSON;
}

solution binarySearch(int low, solution lower, int up, solution upper, float aimedCoverage, QVector<int> sensorCost){

    int lowerCoverage = ((float) lower.sparseMR.size() / (float) (lower.ins.nr));
    int upperCoverage = ((float) upper.sparseMR.size() / (float) (upper.ins.nr));
    int medium = (low + up)/2;
    if(medium - low < 1){
        if(lowerCoverage < aimedCoverage && upperCoverage >= aimedCoverage)
            return upper;
        if(lowerCoverage >= aimedCoverage && upperCoverage < aimedCoverage)
            return lower;
        return (totalPrice(lower, sensorCost) < totalPrice(upper, sensorCost)) ? lower : upper;
    }

    lower.ins.card[1] = medium;
    solution currentSol = vnsheuristic(lower.ins);
    //int currentCoverage = ((float) currentSol.sparseMR.size() / (float) );
    if(lowerCoverage < aimedCoverage && upperCoverage >= aimedCoverage)
        return binarySearch(medium, currentSol, up, upper, aimedCoverage, sensorCost);
    if(lowerCoverage >= aimedCoverage && upperCoverage < aimedCoverage)
        return binarySearch(low, lower, medium, currentSol, aimedCoverage, sensorCost);
    //if(lowerCoverage < aimedCoverage && upperCoverage < aimedCoverage && currentCoverage < aimedCoverage)
    return (lowerCoverage > upperCoverage) ? binarySearch(low, lower, medium, currentSol, aimedCoverage, sensorCost) : binarySearch(medium, currentSol, up, upper, aimedCoverage, sensorCost);

}

int totalPrice(solution sol, QVector<int> sensorCost){
    int price = 0;
    for(const auto& node: sol.sparseMC){
        price = price + sensorCost[(typeFromColumn(sol, node) - 1)];
    }
    return price;
}

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
    else if(context->argumentCount()==9 && context->argument(3).isArray()) {
        CoveragePlugin* cppResult = new CoveragePlugin();
        QList<RVector> fP;
        QList<RVector> cand;
        QList<RVector> box;
        QList<int> rs;
        QVector<int> range;
        QVector<int> cost;
        float aimedCoverage;
        int technique;
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
        technique = context->argument(8).toInteger();
        cppResult->technique = technique;
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
