#include <QDebug>
#include <QObject>
#include <QScriptEngine>
#include <QStringList>

#include "RActionAdapter.h"
#include "RDocumentInterface.h"
#include "RGuiAction.h"
#include "RMainWindow.h"
#include "RPluginInterface.h"
#include "problem_data.hpp"

class MyAction : public RActionAdapter {
public:
    MyAction(RGuiAction* guiAction) : RActionAdapter(guiAction) {}

    static void factory(RGuiAction* guiAction) {
        qDebug() << "MyAction::factory";
        if (guiAction==NULL) {
            qDebug("guiAction is NULL");
            return;
        }
        RDocumentInterface* di = RMainWindow::getDocumentInterfaceStatic();

        if (di==NULL) {
            qDebug("di is NULL");
            return;
        }

        di->setCurrentAction(new MyAction(guiAction));
    }

    virtual void beginEvent() {
        qDebug() << "MyAction::beginEvent";
    }
};

class MySensorsClass : public QObject {
Q_OBJECT
public:
    MySensorsClass() : QObject() {}
    int sensorRange;
    QList<RVector> floorPoints;
    QList<RVector> candidates;
    QList<RVector> boundingBox;
public slots:
    void test();
};


Q_DECLARE_METATYPE(MySensorsClass*)

class RSensorsPlugin : public QObject, public RPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(RPluginInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qcad.sensorsplugin")
#endif

public:
    virtual bool init();
    virtual void uninit(bool) {}
    virtual void postInit(InitStatus status);
    virtual void initScriptExtensions(QScriptEngine& engine);
    virtual RPluginInfo getPluginInfo();

    static QScriptValue createMySensorsClass(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue MySensorsClassToString(QScriptContext *context, QScriptEngine *engine);
    static MySensorsClass* getSelfMySensorsClass(const QString& fName, QScriptContext* context);
};
