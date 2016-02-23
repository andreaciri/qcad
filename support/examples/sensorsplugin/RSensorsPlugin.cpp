#include <QMenuBar>

#include "REcmaHelper.h"
#include "RSensorsPlugin.h"
#include "RSettings.h"
#include "RPluginInfo.h"
#include "RVersion.h"
#include "RMainWindowQt.h"


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

    QScriptValue* proto = new QScriptValue(engine.newVariant(qVariantFromValue((MySensorsClass*)0)));

    // base class:
    QScriptValue dpt = engine.defaultPrototype(qMetaTypeId<QObject*>());
    proto->setPrototype(dpt);

    REcmaHelper::registerFunction(&engine, proto, RSensorsPlugin::MySensorsClassToString, "toString");

    engine.setDefaultPrototype(qMetaTypeId<MySensorsClass*>(), *proto);
                        
    //qScriptRegisterMetaType<MySensorsClass*>(&engine, toScriptValue, fromScriptValue, *proto);

    QScriptValue ctor = engine.newFunction(RSensorsPlugin::createMySensorsClass, *proto, 0);

    engine.globalObject().setProperty("MySensorsClass", ctor, QScriptValue::SkipInEnumeration);
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


void MySensorsClass::test(){
    qDebug() << "MySensorClass::test - " << this->floorPoints;
    int BoundingCoo[4][2];
    for(int i = 0; i < this->boundingBox.length(); i++){
        BoundingCoo[i][0] = (int) this->boundingBox[i].getX();
        BoundingCoo[i][1] = (int) this->boundingBox[i].getY();
    }

    ProblemData& ins=(*LoadData(BoundingCoo, this->sensorRange));
}

/**
 * Constructor for MySensorsClass:
 */
QScriptValue RSensorsPlugin::createMySensorsClass(QScriptContext* context, QScriptEngine* engine) {
    if (context->thisObject().strictlyEquals(engine->globalObject())) {
        return REcmaHelper::throwError(QString::fromLatin1("MySensorsClass(): Did you forget to construct with 'new'?"), context);
    }
    
    // constructor without arguments:
    if(context->argumentCount() == 0) {
        MySensorsClass* cppResult = new MySensorsClass();
        return engine->newQObject(context->thisObject(), cppResult);
    }
    else if(context->argumentCount()==4 && context->argument(3).isArray()) {
        MySensorsClass* cppResult = new MySensorsClass();
        QList<RVector> fP;
        QList<RVector> cand;
        QList<RVector> box;
        int range;
        // convert ECMAScript array to QList<RVector>:
        range = context->argument(0).toInt32();
        cppResult->sensorRange = range;
        REcmaHelper::fromScriptValue(engine, context->argument(1), fP);
        cppResult->floorPoints = fP;
        REcmaHelper::fromScriptValue(engine, context->argument(2), cand);
        cppResult->candidates = cand;
        REcmaHelper::fromScriptValue(engine, context->argument(3), box);
        cppResult->boundingBox = box;
        return engine->newQObject(context->thisObject(), cppResult);
    }
    else {
        return REcmaHelper::throwError(QString::fromLatin1("MySensorsClass(): no matching constructor found."), context);
    }
}

/**
 * MySensorsClass::toString
 */
QScriptValue RSensorsPlugin::MySensorsClassToString(QScriptContext *context, QScriptEngine *engine) {
    Q_UNUSED(engine)

    MySensorsClass* self = getSelfMySensorsClass("toString", context);
    return QScriptValue(QString("MySensorsClass(0x%1)").arg((unsigned long int)self, 0, 16));
}

MySensorsClass* RSensorsPlugin::getSelfMySensorsClass(const QString& fName, QScriptContext* context) {
    MySensorsClass* self = REcmaHelper::scriptValueTo<MySensorsClass >(context->thisObject());
    if (self == NULL){
        if (fName!="toString") {
            REcmaHelper::throwError(QString("MySensorsClass.%1(): This object is not a MySensorsClass").arg(fName), context);
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
