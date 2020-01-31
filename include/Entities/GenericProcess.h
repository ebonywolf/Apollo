#pragma once

#include "Process.h"
#include "Packet.h"
#include "GenericDatatype.h"
#include "MetaTools/GetData.h"
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

    //   virtual Dataptr handle(Entityptr ent, Dataptr d) const=0;
   // virtual Dataptr handle(Entityptr ent, Dataptr d) const override

    template<class T>
    void _callFunc(T& placeholder,Entityptr& ent, Packet& packet)
    {
        INPUT *input = dynamic_cast<INPUT*>(packet.data.get());
        OUTPUT output = _func(ent, *input);
        auto result = Tools::getData(output);
        packet.futureAnswer.set(result);
    }

    template<class T>
    void _callFunc(std::shared_ptr<T>& t,Entityptr& ent, Packet& packet)
    {
        INPUT input = std::static_pointer_cast<T>(packet.data);
        OUTPUT output = _func(ent, input);
        auto result = Tools::getData(output);
        packet.futureAnswer.set(result);
    }


    virtual void handle(Entityptr ent, Packet packet)
    {
        INPUT input;
        //TODO remove this useless constructor
        _callFunc( input , ent, packet);
    }
    GenericProcess():
        Process( std::make_shared<GenericDataPair<OUTPUT,INPUT>>() )
    {
    }

private:

    Functiontype _func;
};



}
