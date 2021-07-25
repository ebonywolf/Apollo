#pragma once

#include "DataType/Datatype.h"


#include "DataType/GenericDatatype.h"
#include "Communication/Packet.h"
#include "Process/Process.h"
#include "MetaTools/GetData.h"
#include "MetaTools/ApplyTuple.h"

namespace pg{

template<class OUTPUT, class INPUT >
struct GenericProcess: public Process
{

    using Functiontype= std::function<OUTPUT(Entityptr,INPUT)>;

    template<class T>
    static GenericProcess* createProcess(
            OUTPUT (myfunc)(std::shared_ptr<T>, INPUT))
    {
        //Creates new Process object with a function pointer as executer
        auto lambdaFunc = [myfunc](Entityptr entity, INPUT input)
        {
            std::shared_ptr<T> alce = std::dynamic_pointer_cast<T>(entity);
            if(!alce)throw "Foo";
            return myfunc(alce, input);
        };
        auto novo = new GenericProcess<OUTPUT,INPUT>();
        novo->_func = lambdaFunc;
        return novo;
    }
    virtual Processptr getBase() const
    {
        return std::make_shared<GenericProcess>();
    }

    template<class T>
    void _callFunc_set( pg::DataSet *dataset, Entityptr &ent, Future &future)
    {
        for (Dataptr data : dataset->getData())
        {
            _callFunc_cast<INPUT>(data, ent, future);
        }
    }


    template<class T>
    void _callFunc_tuple(pg::DataTuple<INPUT>* input, Entityptr& ent, Future& future){
        OUTPUT output = Tools::applyTuple(_func, ent, *input);
        auto result = Tools::getData(output);
        future.set(result);
    }

     template<class T>
    void _callFunc(Dataptr data, Entityptr& ent, Future& future, std::true_type )
    {
        using PrimitivePtr = std::shared_ptr< pg::Primitive_Data<INPUT>>;
        PrimitivePtr input = std::dynamic_pointer_cast<pg::Primitive_Data<INPUT>>(data);
        OUTPUT output = _func(ent, input->getValue());
        auto result = Tools::getData(output);
        future.set(result);
    }

    template<class T>
    void _callFunc(Dataptr data, Entityptr& ent, Future& future, std::false_type)
    {
        INPUT *input = dynamic_cast<INPUT*>(data.get());
        OUTPUT output = _func(ent, *input);
        auto result = Tools::getData(output);
        future.set(result);
    }


    template<class T>
    void _callFunc_cast(Dataptr data, Entityptr& ent, Future& future)
    {
        auto tupleCast =  dynamic_cast<pg::DataTuple<INPUT>*>(data.get() );
        if(tupleCast){
            _callFunc_tuple<T>(tupleCast, ent, future);
            return;
        }
        auto setCast = dynamic_cast<DataSet*>(data.get());
        if(setCast){
            _callFunc_set<T>(setCast,ent,future);
            return;
        }

        _callFunc<T>(data, ent, future, std::is_fundamental<INPUT>());

    }

    virtual void handle(Entityptr ent, Packet packet)
    {

        auto tupleCast =  dynamic_cast<pg::DataTuple<INPUT>*>(packet.data.get() );
       // INPUT placeholder;
        if(tupleCast !=0 ){
            _callFunc_tuple<INPUT>(tupleCast,ent,packet.futureAnswer);
        }else{
            _callFunc_cast<INPUT>(packet.data, ent, packet.futureAnswer);
        }

    }
    GenericProcess():
        Process( std::make_shared<GenericDataPair<OUTPUT,INPUT>>() )
    {
    }

private:

    Functiontype _func;

};

}

