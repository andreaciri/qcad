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
#include "types.hpp"
#include "solution.hpp"

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

class CoveragePlugin : public QObject {
Q_OBJECT
public:
    CoveragePlugin() : QObject() {}
    QVector<int> sensorRange;
    QVector<int> sensorCost;
    float aimedCoverage;
    bool wantCandidates;
    QList<RVector> floorPoints;
    QList<RVector> candidates;
    QList<RVector> boundingBox;
    QList<int> roomSides;
public slots:
    QString start();
};

QString generateJSONResult(ProblemData* pData, SMC sparseMC, float coverageRate);

solution binarySearch(int low, solution lower, int up, solution upper, float aimedCoverage);

Q_DECLARE_METATYPE(CoveragePlugin*)

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

    static QScriptValue createCoveragePlugin(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue CoveragePluginToString(QScriptContext *context, QScriptEngine *engine);
    static CoveragePlugin* getSelfCoveragePlugin(const QString& fName, QScriptContext* context);
};
