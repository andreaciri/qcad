// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMADOCUMENTVARIABLES_H
        #define RECMADOCUMENTVARIABLES_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RDocumentVariables.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaDocumentVariables {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getRObject(QScriptContext *context,
            QScriptEngine *engine)
        ;

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        init
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        clone
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isSelectedForPropertyEditing
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        clear
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCustomPropertyTypeIds
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setKnownVariable
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getKnownVariable
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasKnownVariable
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCurrentLayerId
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setCurrentLayerId
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getUnit
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setUnit
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMeasurement
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setMeasurement
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getLinetypeScale
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setLinetypeScale
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDimensionFont
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDimensionFont
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        print
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RDocumentVariables* getSelf(const QString& fName, QScriptContext* context)
    ;static RDocumentVariables* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    