// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMAIMPORTER_H
        #define RECMAIMPORTER_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RImporter.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaImporter {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        startImport
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        endImport
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        importObject
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setCurrentBlockId
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCurrentBlockId
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDocument
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDocument
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setKnownVariable
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RImporter* getSelf(const QString& fName, QScriptContext* context)
    ;static RImporter* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    