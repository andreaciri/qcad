// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #include "REcmaNewDocumentListener.h"
        #include "RMetaTypes.h"
        #include "../REcmaHelper.h"

        // forwards declarations mapped to includes
        
                #include "RDocument.h"
            
                #include "RTransaction.h"
            
            
        // includes for base ecma wrapper classes
         void REcmaNewDocumentListener::initEcma(QScriptEngine& engine, QScriptValue* proto 
    
    ) 
    
    {

    bool protoCreated = false;
    if(proto == NULL){
        proto = new QScriptValue(engine.newVariant(qVariantFromValue(
                (RNewDocumentListener*) 0)));
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
    
            REcmaHelper::registerFunction(&engine, proto, updateNewDocumentListener, "updateNewDocumentListener");
            
        engine.setDefaultPrototype(
            qMetaTypeId<RNewDocumentListener*>(), *proto);

        
    

    QScriptValue ctor = engine.newFunction(createEcma, *proto, 2);
    
    // static methods:
    

    // static properties:
    

    // enum values:
    

    // enum conversions:
    
        
    // init class:
    engine.globalObject().setProperty("RNewDocumentListener",
    ctor, QScriptValue::SkipInEnumeration);
    
    if( protoCreated ){
       delete proto;
    }
    
    }
     QScriptValue REcmaNewDocumentListener::createEcma(QScriptContext* context, QScriptEngine* engine) 
    
    {
           return REcmaHelper::throwError("Abstract class RNewDocumentListener: Cannot be constructed.",
               context); 
    }
    

    // conversion functions for base classes:
    

    // returns class name:
     QScriptValue REcmaNewDocumentListener::getClassName(QScriptContext *context, QScriptEngine *engine) 
        
    {
        return qScriptValueFromValue(engine, QString("RNewDocumentListener"));
    }
    

    // returns all base classes (in case of multiple inheritance):
     QScriptValue REcmaNewDocumentListener::getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        
    {
        QStringList list;
        

        return qScriptValueFromSequence(engine, list);
    }
    

    // properties:
    

    // public methods:
     QScriptValue
        REcmaNewDocumentListener::updateNewDocumentListener
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaNewDocumentListener::updateNewDocumentListener", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaNewDocumentListener::updateNewDocumentListener";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RNewDocumentListener* self = 
                        getSelf("updateNewDocumentListener", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RDocument * */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RTransaction * */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    RDocument * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<RDocument >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("RNewDocumentListener: Argument 0 is not of type RDocument *RDocument *.", context);                    
                    }
                
                    // argument is pointer
                    RTransaction * a1 = NULL;

                    a1 = 
                        REcmaHelper::scriptValueTo<RTransaction >(
                            context->argument(1)
                        );
                    
                    if (a1==NULL && 
                        !context->argument(1).isNull()) {
                        return REcmaHelper::throwError("RNewDocumentListener: Argument 1 is not of type RTransaction *RTransaction *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->updateNewDocumentListener(a0
        ,
    a1);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RNewDocumentListener.updateNewDocumentListener().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaNewDocumentListener::updateNewDocumentListener", context, engine);
            return result;
        }
         QScriptValue REcmaNewDocumentListener::toString
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    RNewDocumentListener* self = getSelf("toString", context);
    
    QString result;
    
            result = QString("RNewDocumentListener(0x%1)").arg((unsigned long int)self, 0, 16);
        
    return QScriptValue(result);
    }
     QScriptValue REcmaNewDocumentListener::destroy(QScriptContext *context, QScriptEngine *engine)
    
    {

        RNewDocumentListener* self = getSelf("RNewDocumentListener", context);
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
    RNewDocumentListener* REcmaNewDocumentListener::getSelf(const QString& fName, QScriptContext* context)
    
        {
            RNewDocumentListener* self = NULL;

            
                // self could be a normal object (e.g. from an UI file) or
                // an ECMA shell object (made from an ECMA script):
                //self = getSelfShell(fName, context);
                

            //if (self==NULL) {
                self = REcmaHelper::scriptValueTo<RNewDocumentListener >(context->thisObject())
                
                ;
            //}

            if (self == NULL){
                // avoid recursion (toString is used by the backtrace):
                if (fName!="toString") {
                    REcmaHelper::throwError(QString("RNewDocumentListener.%1(): "
                        "This object is not a RNewDocumentListener").arg(fName),
                        context);
                }
                return NULL;
            }

            return self;
        }
        RNewDocumentListener* REcmaNewDocumentListener::getSelfShell(const QString& fName, QScriptContext* context)
    
        {
          RNewDocumentListener* selfBase = getSelf(fName, context);
                RNewDocumentListener* self = dynamic_cast<RNewDocumentListener*>(selfBase);
                //return REcmaHelper::scriptValueTo<RNewDocumentListener >(context->thisObject());
            if(self == NULL){
                REcmaHelper::throwError(QString("RNewDocumentListener.%1(): "
                    "This object is not a RNewDocumentListener").arg(fName),
                    context);
            }

            return self;
            


        }
        