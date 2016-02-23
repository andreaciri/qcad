// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMAMAINWINDOWQT_H
        #define RECMAMAINWINDOWQT_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RMainWindowQt.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaMainWindowQt {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getQMainWindow(QScriptContext *context,
            QScriptEngine *engine)
        ;static  QScriptValue getRMainWindow(QScriptContext *context,
            QScriptEngine *engine)
        ;static  QScriptValue getRProgressHandler(QScriptContext *context,
            QScriptEngine *engine)
        ;static  QScriptValue getRMessageHandler(QScriptContext *context,
            QScriptEngine *engine)
        ;

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;
        // properties of secondary base class RMainWindow:
        

        // methods of secondary base class RMainWindow:
        static  QScriptValue
        hasMainWindow
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        installMessageHandler
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDocumentInterfaceStatic
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addCoordinateListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeCoordinateListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyCoordinateListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addSelectionListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeSelectionListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifySelectionListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addPropertyListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removePropertyListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyPropertyListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addExportListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeExportListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyExportListenersPre
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyExportListenersPost
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyExportListenersEnd
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addEntityExportListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeEntityExportListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyEntityExportListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addImportListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeImportListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyImportListenersPre
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyImportListenersPost
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addTransactionListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeTransactionListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyTransactionListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addInterTransactionListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeInterTransactionListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyInterTransactionListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addNewDocumentListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeNewDocumentListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyNewDocumentListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addSnapListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeSnapListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifySnapListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addFocusListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeFocusListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyFocusListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addViewFocusListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeViewFocusListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyViewFocusListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        propertyChangeEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addUcsListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeUcsListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyUcsListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addLayerListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeLayerListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyLayerListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addBlockListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeBlockListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyBlockListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addViewListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeViewListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyViewListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addPenListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removePenListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        notifyPenListeners
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        ucsSetEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        eval
        (QScriptContext* context, QScriptEngine* engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        getMainWindow
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getWidth
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getHeight
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPositionX
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPositionY
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        resize
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        move
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        disable
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        enable
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDocument
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDocumentInterface
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleUserMessage
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleUserInfo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleUserWarning
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        handleUserCommand
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        postSelectionChangedEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        postTransactionEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        postCloseEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMdiChild
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getTabBar
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMdiArea
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        cancelProgress
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setProgress
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setProgressEnd
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setProgressText
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setCommandPrompt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setLeftMouseTip
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setRightMouseTip
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        showContextMenu
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        escapeEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setGraphicsViewCursor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        readSettings
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        writeSettings
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        createPopupMenu
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getChildWidget
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDockWidgets
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getToolBars
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        quit
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        currentTabChanged
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        subWindowActivated
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RMainWindowQt* getSelf(const QString& fName, QScriptContext* context)
    ;static RMainWindowQt* getSelfShell(const QString& fName, QScriptContext* context)
    ;static  void fromScriptValue(const QScriptValue& value,
        RMainWindowQt*
        &out) {
            QObject* o = value.toQObject();
            out = qobject_cast<
            RMainWindowQt*>(o);
        }
    static  QScriptValue toScriptValue(QScriptEngine *engine,
        RMainWindowQt*
        const &in){
            QScriptValue s = engine->newQObject(in, QScriptEngine::QtOwnership,
            QScriptEngine::PreferExistingWrapperObject);
            /*
            if(s.isNull()){
               REcmaHelper::throwError("This object is null.", engine->currentContext());
            }
            */
            return s;
        }
    };
    #endif
    