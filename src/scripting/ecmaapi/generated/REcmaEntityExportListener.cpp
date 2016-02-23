// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #include "REcmaEntityExportListener.h"
        #include "RMetaTypes.h"
        #include "../REcmaHelper.h"

        // forwards declarations mapped to includes
        
                #include "RExporter.h"
            
            
        // includes for base ecma wrapper classes
         void REcmaEntityExportListener::initEcma(QScriptEngine& engine, QScriptValue* proto 
    
    ) 
    
    {

    bool protoCreated = false;
    if(proto == NULL){
        proto = new QScriptValue(engine.newVariant(qVariantFromValue(
                (REntityExportListener*) 0)));
        protoCreated = true;
    }

    

    QScriptValue fun;

    // toString:
    REcmaHelper::registerFunction(&engine, proto, toString, "toString");
    

    // destroy:
    REcmaHelper::registerFunction(&engine, proto, destroy, "destroy");
    

    // get class name
    REcmaHelper::registerFunction(&engine, proto, getClassName, "getClassName");
    

    // conversion to all base classes (multiple inheritance):
    REcmaHelper::registerFunction(&engine, proto, getBaseClasses, "getBaseClasses");
    

    // properties:
    

    // methods:
    
            REcmaHelper::registerFunction(&engine, proto, registerCustomProperty, "registerCustomProperty");
            
            REcmaHelper::registerFunction(&engine, proto, checkCustomProperty, "checkCustomProperty");
            
            REcmaHelper::registerFunction(&engine, proto, exportEntity, "exportEntity");
            
        engine.setDefaultPrototype(
            qMetaTypeId<REntityExportListener*>(), *proto);

        
    

    QScriptValue ctor = engine.newFunction(createEcma, *proto, 2);
    
    // static methods:
    

    // static properties:
    

    // enum values:
    

    // enum conversions:
    
        
    // init class:
    engine.globalObject().setProperty("REntityExportListener",
    ctor, QScriptValue::SkipInEnumeration);
    
    if( protoCreated ){
       delete proto;
    }
    
    }
     QScriptValue REcmaEntityExportListener::createEcma(QScriptContext* context, QScriptEngine* engine) 
    
    {
           return REcmaHelper::throwError("Abstract class REntityExportListener: Cannot be constructed.",
               context); 
    }
    

    // conversion functions for base classes:
    

    // returns class name:
     QScriptValue REcmaEntityExportListener::getClassName(QScriptContext *context, QScriptEngine *engine) 
        
    {
        return qScriptValueFromValue(engine, QString("REntityExportListener"));
    }
    

    // returns all base classes (in case of multiple inheritance):
     QScriptValue REcmaEntityExportListener::getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        
    {
        QStringList list;
        

        return qScriptValueFromSequence(engine, list);
    }
    

    // properties:
    

    // public methods:
     QScriptValue
        REcmaEntityExportListener::registerCustomProperty
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEntityExportListener::registerCustomProperty", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEntityExportListener::registerCustomProperty";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REntityExportListener* self = 
                        getSelf("registerCustomProperty", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isString()
        ) /* type: QString */
     && (
            context->argument(1).isString()
        ) /* type: QString */
    
    ){
    // prepare arguments:
    
                    // argument isStandardType
                    QString
                    a0 =
                    (QString)
                    
                    context->argument( 0 ).
                    toString();
                
                    // argument isStandardType
                    QString
                    a1 =
                    (QString)
                    
                    context->argument( 1 ).
                    toString();
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->registerCustomProperty(a0
        ,
    a1);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REntityExportListener.registerCustomProperty().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEntityExportListener::registerCustomProperty", context, engine);
            return result;
        }
         QScriptValue
        REcmaEntityExportListener::checkCustomProperty
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEntityExportListener::checkCustomProperty", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEntityExportListener::checkCustomProperty";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REntityExportListener* self = 
                        getSelf("checkCustomProperty", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: REntity * */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    REntity * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<REntity >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("REntityExportListener: Argument 0 is not of type REntity *REntity *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'bool'
    bool cppResult =
        
               self->checkCustomProperty(a0);
        // return type: bool
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REntityExportListener.checkCustomProperty().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEntityExportListener::checkCustomProperty", context, engine);
            return result;
        }
         QScriptValue
        REcmaEntityExportListener::exportEntity
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEntityExportListener::exportEntity", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEntityExportListener::exportEntity";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REntityExportListener* self = 
                        getSelf("exportEntity", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RExporter * */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: REntity * */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    RExporter * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<RExporter >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("REntityExportListener: Argument 0 is not of type RExporter *RExporter *.", context);                    
                    }
                
                    // argument is pointer
                    REntity * a1 = NULL;

                    a1 = 
                        REcmaHelper::scriptValueTo<REntity >(
                            context->argument(1)
                        );
                    
                    if (a1==NULL && 
                        !context->argument(1).isNull()) {
                        return REcmaHelper::throwError("REntityExportListener: Argument 1 is not of type REntity *REntity *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->exportEntity(a0
        ,
    a1);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REntityExportListener.exportEntity().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEntityExportListener::exportEntity", context, engine);
            return result;
        }
         QScriptValue REcmaEntityExportListener::toString
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    REntityExportListener* self = getSelf("toString", context);
    
    QString result;
    
            result = QString("REntityExportListener(0x%1)").arg((unsigned long int)self, 0, 16);
        
    return QScriptValue(result);
    }
     QScriptValue REcmaEntityExportListener::destroy(QScriptContext *context, QScriptEngine *engine)
    
    {

        REntityExportListener* self = getSelf("REntityExportListener", context);
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
    REntityExportListener* REcmaEntityExportListener::getSelf(const QString& fName, QScriptContext* context)
    
        {
            REntityExportListener* self = NULL;

            
                // self could be a normal object (e.g. from an UI file) or
                // an ECMA shell object (made from an ECMA script):
                //self = getSelfShell(fName, context);
                

            //if (self==NULL) {
                self = REcmaHelper::scriptValueTo<REntityExportListener >(context->thisObject())
                
                ;
            //}

            if (self == NULL){
                // avoid recursion (toString is used by the backtrace):
                if (fName!="toString") {
                    REcmaHelper::throwError(QString("REntityExportListener.%1(): "
                        "This object is not a REntityExportListener").arg(fName),
                        context);
                }
                return NULL;
            }

            return self;
        }
        REntityExportListener* REcmaEntityExportListener::getSelfShell(const QString& fName, QScriptContext* context)
    
        {
          REntityExportListener* selfBase = getSelf(fName, context);
                REntityExportListener* self = dynamic_cast<REntityExportListener*>(selfBase);
                //return REcmaHelper::scriptValueTo<REntityExportListener >(context->thisObject());
            if(self == NULL){
                REcmaHelper::throwError(QString("REntityExportListener.%1(): "
                    "This object is not a REntityExportListener").arg(fName),
                    context);
            }

            return self;
            


        }
        