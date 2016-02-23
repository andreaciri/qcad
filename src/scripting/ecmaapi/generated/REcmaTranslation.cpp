// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #include "REcmaTranslation.h"
        #include "RMetaTypes.h"
        #include "../REcmaHelper.h"

        // forwards declarations mapped to includes
        
            
        // includes for base ecma wrapper classes
        
                  #include "REcmaTransformation.h"
                 void REcmaTranslation::initEcma(QScriptEngine& engine, QScriptValue* proto 
    
    ) 
    
    {

    bool protoCreated = false;
    if(proto == NULL){
        proto = new QScriptValue(engine.newVariant(qVariantFromValue(
                (RTranslation*) 0)));
        protoCreated = true;
    }

    
        // primary base class RTransformation:
        
            QScriptValue dpt = engine.defaultPrototype(
                qMetaTypeId<RTransformation*>());

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
    
        // conversion for base class RTransformation
        REcmaHelper::registerFunction(&engine, proto, getRTransformation, "getRTransformation");
        

    // get class name
    REcmaHelper::registerFunction(&engine, proto, getClassName, "getClassName");
    

    // conversion to all base classes (multiple inheritance):
    REcmaHelper::registerFunction(&engine, proto, getBaseClasses, "getBaseClasses");
    

    // properties:
    

    // methods:
    
        engine.setDefaultPrototype(
            qMetaTypeId<RTranslation*>(), *proto);

        
    

    QScriptValue ctor = engine.newFunction(createEcma, *proto, 2);
    
    // static methods:
    

    // static properties:
    

    // enum values:
    

    // enum conversions:
    
        
    // init class:
    engine.globalObject().setProperty("RTranslation",
    ctor, QScriptValue::SkipInEnumeration);
    
    if( protoCreated ){
       delete proto;
    }
    
    }
     QScriptValue REcmaTranslation::createEcma(QScriptContext* context, QScriptEngine* engine) 
    
    {
    if (context->thisObject().strictlyEquals(
       engine->globalObject())) {
       return REcmaHelper::throwError(
       QString::fromLatin1("RTranslation(): Did you forget to construct with 'new'?"),
           context);
    }

    QScriptValue result;
        
            // generate constructor variants:
            
    if( context->argumentCount() ==
        1
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
                ) /* type: RVector */
            
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
                           return REcmaHelper::throwError("RTranslation: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
    // end of arguments

    // call C++ constructor:
    
            // non-copyable class:
            RTranslation
                    * cppResult =
                    new
                    RTranslation
                    (
                    a0
                    );
                
                    // TODO: triggers: Warning: QScriptEngine::newVariant(): changing class of non-QScriptObject not supported:
                    result = engine->newVariant(context->thisObject(), qVariantFromValue(cppResult));
                
    } else 

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
                ) /* type: RVector */
            
                && (
                
                        context->argument(
                        1
                        ).isNumber()
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
                           return REcmaHelper::throwError("RTranslation: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isStandardType
                    double
                    a1 =
                    (double)
                    
                    context->argument( 1 ).
                    toNumber();
                
    // end of arguments

    // call C++ constructor:
    
            // non-copyable class:
            RTranslation
                    * cppResult =
                    new
                    RTranslation
                    (
                    a0
        ,
    a1
                    );
                
                    // TODO: triggers: Warning: QScriptEngine::newVariant(): changing class of non-QScriptObject not supported:
                    result = engine->newVariant(context->thisObject(), qVariantFromValue(cppResult));
                
    } else 

    if( context->argumentCount() ==
        3
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
                ) /* type: RVector */
            
                && (
                
                        context->argument(
                        1
                        ).isNumber()
                ) /* type: double */
            
                && (
                
                        context->argument(
                        2
                        ).isNumber()
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
                           return REcmaHelper::throwError("RTranslation: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isStandardType
                    double
                    a1 =
                    (double)
                    
                    context->argument( 1 ).
                    toNumber();
                
                    // argument isStandardType
                    double
                    a2 =
                    (double)
                    
                    context->argument( 2 ).
                    toNumber();
                
    // end of arguments

    // call C++ constructor:
    
            // non-copyable class:
            RTranslation
                    * cppResult =
                    new
                    RTranslation
                    (
                    a0
        ,
    a1
        ,
    a2
                    );
                
                    // TODO: triggers: Warning: QScriptEngine::newVariant(): changing class of non-QScriptObject not supported:
                    result = engine->newVariant(context->thisObject(), qVariantFromValue(cppResult));
                
    } else 

    if( context->argumentCount() ==
        4
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
                ) /* type: RVector */
            
                && (
                
                        context->argument(
                        1
                        ).isNumber()
                ) /* type: double */
            
                && (
                
                        context->argument(
                        2
                        ).isNumber()
                ) /* type: double */
            
                && (
                
                        context->argument(
                        3
                        ).isVariant()
                        ||
                    
                        context->argument(
                        3
                        ).isQObject()
                        ||
                    
                        context->argument(
                        3
                        ).isNull()
                ) /* type: RVector */
            
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
                           return REcmaHelper::throwError("RTranslation: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isStandardType
                    double
                    a1 =
                    (double)
                    
                    context->argument( 1 ).
                    toNumber();
                
                    // argument isStandardType
                    double
                    a2 =
                    (double)
                    
                    context->argument( 2 ).
                    toNumber();
                
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap3 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        3
                        )
                    );
                    if (ap3 == NULL) {
                           return REcmaHelper::throwError("RTranslation: Argument 3 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a3 = 
                    *ap3;
                
    // end of arguments

    // call C++ constructor:
    
            // non-copyable class:
            RTranslation
                    * cppResult =
                    new
                    RTranslation
                    (
                    a0
        ,
    a1
        ,
    a2
        ,
    a3
                    );
                
                    // TODO: triggers: Warning: QScriptEngine::newVariant(): changing class of non-QScriptObject not supported:
                    result = engine->newVariant(context->thisObject(), qVariantFromValue(cppResult));
                
    } else 

    {
       return REcmaHelper::throwError(
       QString::fromLatin1("RTranslation(): no matching constructor found."),
           context);
    }
    
    return result;
    }
    

    // conversion functions for base classes:
     QScriptValue REcmaTranslation::getRTransformation(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RTransformation* cppResult =
                    qscriptvalue_cast<RTranslation*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
            

    // returns class name:
     QScriptValue REcmaTranslation::getClassName(QScriptContext *context, QScriptEngine *engine) 
        
    {
        return qScriptValueFromValue(engine, QString("RTranslation"));
    }
    

    // returns all base classes (in case of multiple inheritance):
     QScriptValue REcmaTranslation::getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        
    {
        QStringList list;
        
        list.append("RTransformation");
    

        return qScriptValueFromSequence(engine, list);
    }
    

    // properties:
    

    // public methods:
     QScriptValue REcmaTranslation::toString
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    RTranslation* self = getSelf("toString", context);
    
    QString result;
    
            result = QString("RTranslation(0x%1)").arg((unsigned long int)self, 0, 16);
        
    return QScriptValue(result);
    }
     QScriptValue REcmaTranslation::destroy(QScriptContext *context, QScriptEngine *engine)
    
    {

        RTranslation* self = getSelf("RTranslation", context);
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
    RTranslation* REcmaTranslation::getSelf(const QString& fName, QScriptContext* context)
    
        {
            RTranslation* self = NULL;

            
                // self could be a normal object (e.g. from an UI file) or
                // an ECMA shell object (made from an ECMA script):
                //self = getSelfShell(fName, context);
                

            //if (self==NULL) {
                self = REcmaHelper::scriptValueTo<RTranslation >(context->thisObject())
                
                ;
            //}

            if (self == NULL){
                // avoid recursion (toString is used by the backtrace):
                if (fName!="toString") {
                    REcmaHelper::throwError(QString("RTranslation.%1(): "
                        "This object is not a RTranslation").arg(fName),
                        context);
                }
                return NULL;
            }

            return self;
        }
        RTranslation* REcmaTranslation::getSelfShell(const QString& fName, QScriptContext* context)
    
        {
          RTranslation* selfBase = getSelf(fName, context);
                RTranslation* self = dynamic_cast<RTranslation*>(selfBase);
                //return REcmaHelper::scriptValueTo<RTranslation >(context->thisObject());
            if(self == NULL){
                REcmaHelper::throwError(QString("RTranslation.%1(): "
                    "This object is not a RTranslation").arg(fName),
                    context);
            }

            return self;
            


        }
        