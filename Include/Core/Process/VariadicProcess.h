
#pragma once


#include "DataType/DataTuple.h"
#include "Process/GenericProcess.h"
#include "MetaTools/ApplyTuple.h"

namespace pg{



template <class OUTPUT, class ...INPUT>
class VariadicProcess: public Process
{
public:
 using FunctionType=  OUTPUT (*)(Entityptr, INPUT...);
 using FunctorType =  std::function<OUTPUT(Entityptr, INPUT... )>;

 template<class T>
 static VariadicProcess* createProcess(
         OUTPUT (myfunc)(std::shared_ptr<T>, INPUT...))
 {
     //Creates new Process object with a function pointer as executer
     auto lambdaFunc = [myfunc](Entityptr entity, INPUT...input)
     {
         std::shared_ptr<T> alce = std::dynamic_pointer_cast<T>(entity);

         return myfunc(alce, input...);
     };
     auto novo = new VariadicProcess<OUTPUT,INPUT...>();
     novo->_func = lambdaFunc;
     return novo;
 }    virtual void handle(Entityptr ent, Packet packet)
    {
//        INPUT input;
       DataTuple<INPUT...> placeholder;
       //TODO remove this useless constructor
       _callFunc( placeholder , ent, packet);
    }
    VariadicProcess():Process( createKey<OUTPUT, INPUT...>())
    {
    }

private:



     template<class T>
    void _callFunc(T& placeholder,Entityptr& ent, Packet& packet)
    {
        T *input = dynamic_cast<T*>(packet.data.get());

        OUTPUT output = Tools::applyTuple(_func, ent, *input);

        auto result = Tools::getData(output);
        packet.futureAnswer.set(result);
    }


    virtual Processptr getBase() const
    {
      return std::make_shared<VariadicProcess>();
    }


    FunctorType _func;

};


}
