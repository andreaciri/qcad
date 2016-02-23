// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is copyable.
        
        #ifndef RECMAIMAGEDATA_H
        #define RECMAIMAGEDATA_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RImageData.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaImageData {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getREntityData(QScriptContext *context,
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
        operator_assign
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getBoundingBox
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPointOnEntity
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDistanceTo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        intersectsWith
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getReferencePoints
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        moveReferencePoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        move
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        rotate
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        scale
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        mirror
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        castToShape
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getShapes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getFileName
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setFileName
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getInsertionPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setInsertionPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getAngle
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setAngle
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getUVector
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getVVector
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setWidth
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setHeight
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getWidth
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getHeight
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPixelWidth
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPixelHeight
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getBrightness
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getContrast
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getFade
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getImage
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        load
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        reload
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getEdges
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue copy
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RImageData* getSelf(const QString& fName, QScriptContext* context)
    ;static RImageData* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    