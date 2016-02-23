// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #include "REcmaSnapEntityBase.h"
        #include "RMetaTypes.h"
        #include "../REcmaHelper.h"

        // forwards declarations mapped to includes
        
                #include "RMouseEvent.h"
            
            
        // includes for base ecma wrapper classes
        
                  #include "REcmaSnap.h"
                 void REcmaSnapEntityBase::initEcma(QScriptEngine& engine, QScriptValue* proto 
    
    ) 
    
    {

    bool protoCreated = false;
    if(proto == NULL){
        proto = new QScriptValue(engine.newVariant(qVariantFromValue(
                (RSnapEntityBase*) 0)));
        protoCreated = true;
    }

    
        // primary base class RSnap:
        
            QScriptValue dpt = engine.defaultPrototype(
                qMetaTypeId<RSnap*>());

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
    
        // conversion for base class RSnap
        REcmaHelper::registerFunction(&engine, proto, getRSnap, "getRSnap");
        

    // get class name
    REcmaHelper::registerFunction(&engine, proto, getClassName, "getClassName");
    

    // conversion to all base classes (multiple inheritance):
    REcmaHelper::registerFunction(&engine, proto, getBaseClasses, "getBaseClasses");
    

    // properties:
    

    // methods:
    
            REcmaHelper::registerFunction(&engine, proto, snap, "snap");
            
        engine.setDefaultPrototype(
            qMetaTypeId<RSnapEntityBase*>(), *proto);

        
    

    QScriptValue ctor = engine.newFunction(createEcma, *proto, 2);
    
    // static methods:
    

    // static properties:
    

    // enum values:
    

    // enum conversions:
    
        
    // init class:
    engine.globalObject().setProperty("RSnapEntityBase",
    ctor, QScriptValue::SkipInEnumeration);
    
    if( protoCreated ){
       delete proto;
    }
    
    }
     QScriptValue REcmaSnapEntityBase::createEcma(QScriptContext* context, QScriptEngine* engine) 
    
    {
           return REcmaHelper::throwError("Abstract class RSnapEntityBase: Cannot be constructed.",
               context); 
    }
    

    // conversion functions for base classes:
     QScriptValue REcmaSnapEntityBase::getRSnap(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RSnap* cppResult =
                    qscriptvalue_cast<RSnapEntityBase*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
            

    // returns class name:
     QScriptValue REcmaSnapEntityBase::getClassName(QScriptContext *context, QScriptEngine *engine) 
        
    {
        return qScriptValueFromValue(engine, QString("RSnapEntityBase"));
    }
    

    // returns all base classes (in case of multiple inheritance):
     QScriptValue REcmaSnapEntityBase::getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        
    {
        QStringList list;
        
        list.append("RSnap");
    

        return qScriptValueFromSequence(engine, list);
    }
    

    // properties:
    

    // public methods:
     QScriptValue
        REcmaSnapEntityBase::snap
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaSnapEntityBase::snap", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaSnapEntityBase::snap";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RSnapEntityBase* self = 
                        getSelf("snap", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RGraphicsView */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RSnapEntityBase: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument is reference
                    RGraphicsView*
                    ap1 =
                    qscriptvalue_cast<
                    RGraphicsView*
                        >(
                        context->argument(
                        1
                        )
                    );
                    if( ap1 == NULL ){
                           return REcmaHelper::throwError("RSnapEntityBase: Argument 1 is not of type RGraphicsView*.",
                               context);                    
                    }
                    RGraphicsView& a1 = *ap1;
                
    // end of arguments

    // call C++ function:
    // return type 'RVector'
    RVector cppResult =
        
               self->snap(a0
        ,
    a1);
        // return type: RVector
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    3 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RGraphicsView */
     && (
            context->argument(2).isNumber()
        ) /* type: double */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RSnapEntityBase: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument is reference
                    RGraphicsView*
                    ap1 =
                    qscriptvalue_cast<
                    RGraphicsView*
                        >(
                        context->argument(
                        1
                        )
                    );
                    if( ap1 == NULL ){
                           return REcmaHelper::throwError("RSnapEntityBase: Argument 1 is not of type RGraphicsView*.",
                               context);                    
                    }
                    RGraphicsView& a1 = *ap1;
                
                    // argument isStandardType
                    double
                    a2 =
                    (double)
                    
                    context->argument( 2 ).
                    toNumber();
                
    // end of arguments

    // call C++ function:
    // return type 'RVector'
    RVector cppResult =
        
               self->snap(a0
        ,
    a1
        ,
    a2);
        // return type: RVector
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    4 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RGraphicsView */
     && (
            context->argument(2).isArray()
        ) /* type: QSet < REntity::Id > */
     && (
            context->argument(3).isVariant() || 
            context->argument(3).isQObject() || 
            context->argument(3).isNull()
        ) /* type: RBox */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RSnapEntityBase: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument is reference
                    RGraphicsView*
                    ap1 =
                    qscriptvalue_cast<
                    RGraphicsView*
                        >(
                        context->argument(
                        1
                        )
                    );
                    if( ap1 == NULL ){
                           return REcmaHelper::throwError("RSnapEntityBase: Argument 1 is not of type RGraphicsView*.",
                               context);                    
                    }
                    RGraphicsView& a1 = *ap1;
                
                    // argument isArray
                    QSet < REntity::Id >
                    a2;
                    REcmaHelper::fromScriptValue(
                        engine,
                        context->argument(2),
                        a2
                    );
                
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RBox*
                    ap3 =
                    qscriptvalue_cast<
                    RBox*
                        >(
                        context->argument(
                        3
                        )
                    );
                    if (ap3 == NULL) {
                           return REcmaHelper::throwError("RSnapEntityBase: Argument 3 is not of type RBox.",
                               context);                    
                    }
                    RBox 
                    a3 = 
                    *ap3;
                
    // end of arguments

    // call C++ function:
    // return type 'RVector'
    RVector cppResult =
        
               self->snap(a0
        ,
    a1
        ,
    a2
        ,
    a3);
        // return type: RVector
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RSnapEntityBase.snap().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaSnapEntityBase::snap", context, engine);
            return result;
        }
         QScriptValue REcmaSnapEntityBase::toString
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    RSnapEntityBase* self = getSelf("toString", context);
    
    QString result;
    
            result = QString("RSnapEntityBase(0x%1)").arg((unsigned long int)self, 0, 16);
        
    return QScriptValue(result);
    }
     QScriptValue REcmaSnapEntityBase::destroy(QScriptContext *context, QScriptEngine *engine)
    
    {

        RSnapEntityBase* self = getSelf("RSnapEntityBase", context);
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
    RSnapEntityBase* REcmaSnapEntityBase::getSelf(const QString& fName, QScriptContext* context)
    
        {
            RSnapEntityBase* self = NULL;

            
                // self could be a normal object (e.g. from an UI file) or
                // an ECMA shell object (made from an ECMA script):
                //self = getSelfShell(fName, context);
                

            //if (self==NULL) {
                self = REcmaHelper::scriptValueTo<RSnapEntityBase >(context->thisObject())
                
                ;
            //}

            if (self == NULL){
                // avoid recursion (toString is used by the backtrace):
                if (fName!="toString") {
                    REcmaHelper::throwError(QString("RSnapEntityBase.%1(): "
                        "This object is not a RSnapEntityBase").arg(fName),
                        context);
                }
                return NULL;
            }

            return self;
        }
        RSnapEntityBase* REcmaSnapEntityBase::getSelfShell(const QString& fName, QScriptContext* context)
    
        {
          RSnapEntityBase* selfBase = getSelf(fName, context);
                RSnapEntityBase* self = dynamic_cast<RSnapEntityBase*>(selfBase);
                //return REcmaHelper::scriptValueTo<RSnapEntityBase >(context->thisObject());
            if(self == NULL){
                REcmaHelper::throwError(QString("RSnapEntityBase.%1(): "
                    "This object is not a RSnapEntityBase").arg(fName),
                    context);
            }

            return self;
            


        }
        