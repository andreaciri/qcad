// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #include "REcmaToolMatrixItemDelegate.h"
        #include "RMetaTypes.h"
        #include "../REcmaHelper.h"

        // forwards declarations mapped to includes
        
            
        // includes for base ecma wrapper classes
         void REcmaToolMatrixItemDelegate::initEcma(QScriptEngine& engine, QScriptValue* proto 
    
    ) 
    
    {

    bool protoCreated = false;
    if(proto == NULL){
        proto = new QScriptValue(engine.newVariant(qVariantFromValue(
                (RToolMatrixItemDelegate*) 0)));
        protoCreated = true;
    }

    
        // primary base class QItemDelegate:
        
            QScriptValue dpt = engine.defaultPrototype(
                qMetaTypeId<QItemDelegate*>());

            if (dpt.isValid()) {
                proto->setPrototype(dpt);
            }
          
        /*
        
        */
    

    QScriptValue fun;

    // toString:
    REcmaHelper::registerFunction(&engine, proto, toString, "toString");
    

    // destroy:
    REcmaHelper::registerFunction(&engine, proto, destroy, "destroy");
    
        // conversion for base class QItemDelegate
        REcmaHelper::registerFunction(&engine, proto, getQItemDelegate, "getQItemDelegate");
        

    // get class name
    REcmaHelper::registerFunction(&engine, proto, getClassName, "getClassName");
    

    // conversion to all base classes (multiple inheritance):
    REcmaHelper::registerFunction(&engine, proto, getBaseClasses, "getBaseClasses");
    

    // properties:
    

    // methods:
    
            REcmaHelper::registerFunction(&engine, proto, paint, "paint");
            
            REcmaHelper::registerFunction(&engine, proto, sizeHint, "sizeHint");
            
        engine.setDefaultPrototype(
            qMetaTypeId<RToolMatrixItemDelegate*>(), *proto);

        
                        qScriptRegisterMetaType<
                        RToolMatrixItemDelegate*>(
                        &engine, toScriptValue, fromScriptValue, *proto);
                    
    

    QScriptValue ctor = engine.newFunction(createEcma, *proto, 2);
    
    // static methods:
    

    // static properties:
    

    // enum values:
    

    // enum conversions:
    
        
    // init class:
    engine.globalObject().setProperty("RToolMatrixItemDelegate",
    ctor, QScriptValue::SkipInEnumeration);
    
    if( protoCreated ){
       delete proto;
    }
    
    }
     QScriptValue REcmaToolMatrixItemDelegate::createEcma(QScriptContext* context, QScriptEngine* engine) 
    
    {
    if (context->thisObject().strictlyEquals(
       engine->globalObject())) {
       return REcmaHelper::throwError(
       QString::fromLatin1("RToolMatrixItemDelegate(): Did you forget to construct with 'new'?"),
           context);
    }

    QScriptValue result;
        
            // generate constructor variants:
            
    if( context->argumentCount() ==
        2
                && (
                
                        context->argument(
                        0
                        ).isVariant()
                        ||
                    
                        context->argument(
                        0
                        ).isQObject()
                        ||
                    
                        context->argument(
                        0
                        ).isNull()
                ) /* type: QTreeView * */
            
                && (
                
                        context->argument(
                        1
                        ).isQObject()
                        ||
                    
                        context->argument(
                        1
                        ).isNull()
                ) /* type: QWidget * */
            
    ){
    // prepare arguments:
    
                    // argument is pointer
                    QTreeView * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<QTreeView >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("RToolMatrixItemDelegate: Argument 0 is not of type QTreeView *QTreeView *.", context);                    
                    }
                
            // argument isQObject
            QWidget *
            a1 =
            qobject_cast<
            QWidget *>
            ( context->argument(
            1
            ).
            toQObject()
            );
        
    // end of arguments

    // call C++ constructor:
    
            // non-copyable class:
            REcmaShellToolMatrixItemDelegate
                    * cppResult =
                    new
                    REcmaShellToolMatrixItemDelegate
                    (
                    a0
        ,
    a1
                    );
                
                    result = engine->newQObject(context->thisObject(), cppResult, QScriptEngine::QtOwnership);
                
        cppResult->__qtscript_self = result;
    
    } else 

    {
       return REcmaHelper::throwError(
       QString::fromLatin1("RToolMatrixItemDelegate(): no matching constructor found."),
           context);
    }
    
    return result;
    }
    

    // conversion functions for base classes:
     QScriptValue REcmaToolMatrixItemDelegate::getQItemDelegate(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                QItemDelegate* cppResult =
                    qscriptvalue_cast<RToolMatrixItemDelegate*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
            

    // returns class name:
     QScriptValue REcmaToolMatrixItemDelegate::getClassName(QScriptContext *context, QScriptEngine *engine) 
        
    {
        return qScriptValueFromValue(engine, QString("RToolMatrixItemDelegate"));
    }
    

    // returns all base classes (in case of multiple inheritance):
     QScriptValue REcmaToolMatrixItemDelegate::getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        
    {
        QStringList list;
        
        list.append("QItemDelegate");
    

        return qScriptValueFromSequence(engine, list);
    }
    

    // properties:
    

    // public methods:
     QScriptValue
        REcmaToolMatrixItemDelegate::paint
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaToolMatrixItemDelegate::paint", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaToolMatrixItemDelegate::paint";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RToolMatrixItemDelegate* self = 
                        getSelf("paint", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    3 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: QPainter * */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: QStyleOptionViewItem */
     && (
            context->argument(2).isVariant() || 
            context->argument(2).isQObject() || 
            context->argument(2).isNull()
        ) /* type: QModelIndex */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    QPainter * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<QPainter >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("RToolMatrixItemDelegate: Argument 0 is not of type QPainter *QPainter *.", context);                    
                    }
                
                    // argument is reference
                    QStyleOptionViewItem*
                    ap1 =
                    qscriptvalue_cast<
                    QStyleOptionViewItem*
                        >(
                        context->argument(
                        1
                        )
                    );
                    if( ap1 == NULL ){
                           return REcmaHelper::throwError("RToolMatrixItemDelegate: Argument 1 is not of type QStyleOptionViewItem*.",
                               context);                    
                    }
                    QStyleOptionViewItem& a1 = *ap1;
                
                    // argument is reference
                    QModelIndex*
                    ap2 =
                    qscriptvalue_cast<
                    QModelIndex*
                        >(
                        context->argument(
                        2
                        )
                    );
                    if( ap2 == NULL ){
                           return REcmaHelper::throwError("RToolMatrixItemDelegate: Argument 2 is not of type QModelIndex*.",
                               context);                    
                    }
                    QModelIndex& a2 = *ap2;
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->paint(a0
        ,
    a1
        ,
    a2);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RToolMatrixItemDelegate.paint().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaToolMatrixItemDelegate::paint", context, engine);
            return result;
        }
         QScriptValue
        REcmaToolMatrixItemDelegate::sizeHint
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaToolMatrixItemDelegate::sizeHint", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaToolMatrixItemDelegate::sizeHint";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RToolMatrixItemDelegate* self = 
                        getSelf("sizeHint", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: QStyleOptionViewItem */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: QModelIndex */
    
    ){
    // prepare arguments:
    
                    // argument is reference
                    QStyleOptionViewItem*
                    ap0 =
                    qscriptvalue_cast<
                    QStyleOptionViewItem*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if( ap0 == NULL ){
                           return REcmaHelper::throwError("RToolMatrixItemDelegate: Argument 0 is not of type QStyleOptionViewItem*.",
                               context);                    
                    }
                    QStyleOptionViewItem& a0 = *ap0;
                
                    // argument is reference
                    QModelIndex*
                    ap1 =
                    qscriptvalue_cast<
                    QModelIndex*
                        >(
                        context->argument(
                        1
                        )
                    );
                    if( ap1 == NULL ){
                           return REcmaHelper::throwError("RToolMatrixItemDelegate: Argument 1 is not of type QModelIndex*.",
                               context);                    
                    }
                    QModelIndex& a1 = *ap1;
                
    // end of arguments

    // call C++ function:
    // return type 'QSize'
    QSize cppResult =
        
               self->sizeHint(a0
        ,
    a1);
        // return type: QSize
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RToolMatrixItemDelegate.sizeHint().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaToolMatrixItemDelegate::sizeHint", context, engine);
            return result;
        }
         QScriptValue REcmaToolMatrixItemDelegate::toString
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    RToolMatrixItemDelegate* self = getSelf("toString", context);
    
    QString result;
    
            result = QString("RToolMatrixItemDelegate(0x%1)").arg((unsigned long int)self, 0, 16);
        
    return QScriptValue(result);
    }
     QScriptValue REcmaToolMatrixItemDelegate::destroy(QScriptContext *context, QScriptEngine *engine)
    
    {

        RToolMatrixItemDelegate* self = getSelf("RToolMatrixItemDelegate", context);
        //Q_ASSERT(self!=NULL);
        if (self==NULL) {
            return REcmaHelper::throwError("self is NULL", context);
        }
        
    
        delete self;
        context->thisObject().setData(engine->nullValue());
        context->thisObject().prototype().setData(engine->nullValue());
        context->thisObject().setPrototype(engine->nullValue());
        context->thisObject().setScriptClass(NULL);
        return engine->undefinedValue();
    }
    RToolMatrixItemDelegate* REcmaToolMatrixItemDelegate::getSelf(const QString& fName, QScriptContext* context)
    
        {
            RToolMatrixItemDelegate* self = NULL;

            
                // self could be a normal object (e.g. from an UI file) or
                // an ECMA shell object (made from an ECMA script):
                //self = getSelfShell(fName, context);
                

            //if (self==NULL) {
                self = REcmaHelper::scriptValueTo<RToolMatrixItemDelegate >(context->thisObject())
                
                ;
            //}

            if (self == NULL){
                // avoid recursion (toString is used by the backtrace):
                if (fName!="toString") {
                    REcmaHelper::throwError(QString("RToolMatrixItemDelegate.%1(): "
                        "This object is not a RToolMatrixItemDelegate").arg(fName),
                        context);
                }
                return NULL;
            }

            return self;
        }
        REcmaShellToolMatrixItemDelegate* REcmaToolMatrixItemDelegate::getSelfShell(const QString& fName, QScriptContext* context)
    
        {
          RToolMatrixItemDelegate* selfBase = getSelf(fName, context);
                REcmaShellToolMatrixItemDelegate* self = dynamic_cast<REcmaShellToolMatrixItemDelegate*>(selfBase);
                //return REcmaHelper::scriptValueTo<REcmaShellToolMatrixItemDelegate >(context->thisObject());
            if(self == NULL){
                REcmaHelper::throwError(QString("RToolMatrixItemDelegate.%1(): "
                    "This object is not a RToolMatrixItemDelegate").arg(fName),
                    context);
            }

            return self;
            


        }
         void fromScriptValue(const QScriptValue& value,
        RToolMatrixItemDelegate*
        &out) {
            QObject* o = value.toQObject();
            out = qobject_cast<
            RToolMatrixItemDelegate*>(o);
        }
     QScriptValue toScriptValue(QScriptEngine *engine,
        RToolMatrixItemDelegate*
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
    