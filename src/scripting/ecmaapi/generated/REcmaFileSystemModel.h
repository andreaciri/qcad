// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMAFILESYSTEMMODEL_H
        #define RECMAFILESYSTEMMODEL_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RFileSystemModel.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaFileSystemModel {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getQFileSystemModel(QScriptContext *context,
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
        setRootPath
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        rootPath
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        pathIndex
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        index
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        filePath
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setFilter
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isDir
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setHeaderData
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        rowCount
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setIconProvider
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setNameFilter
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setNameFilters
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setNameFilterDisables
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setItemData
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        itemData
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        canFetchMore
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        fetchMore
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        data
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RFileSystemModel* getSelf(const QString& fName, QScriptContext* context)
    ;static RFileSystemModel* getSelfShell(const QString& fName, QScriptContext* context)
    ;static  void fromScriptValue(const QScriptValue& value,
        RFileSystemModel*
        &out) {
            QObject* o = value.toQObject();
            out = qobject_cast<
            RFileSystemModel*>(o);
        }
    static  QScriptValue toScriptValue(QScriptEngine *engine,
        RFileSystemModel*
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
    