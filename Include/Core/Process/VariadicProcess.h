
#pragma once


#include "Data/DataTuple.h"
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
       callFunc( placeholder , ent, packet);
    }
    VariadicProcess():Process( createKeyPair<OUTPUT, INPUT...>())
    {
    }

private:


    template<class T>
    void _callFunc_set(Entityptr& ent, pg::DataSet* dataset, Packet& packet){
        for(Dataptr data :dataset->getData()){
            T *input = dynamic_cast<T*>(data.get());
            if(input == 0){
           //     _callFunc_casts<T>(ent, data, packet.futureAnswer);
                handle(ent, Packet(data, packet.futureAnswer, packet.context));
            }else{
               _callFunc_result<T>(ent, data,  packet);
            }
        }
    }

    template<class T>
    void _callFunc_result(Entityptr& ent, Dataptr data, Packet& packet){
        T *input = dynamic_cast<T*>(data.get());
        OUTPUT output = Tools::applyTuple(_func, ent, *input);
        auto result = Tools::getData(output);
        packet.futureAnswer.set(result);
    }

    template<class T>
    void callFunc(T& placeholder,Entityptr& ent, Packet& packet)
    {
        T *input = dynamic_cast<T*>(packet.data.get());
        if(input == 0 ){
            _callFunc_casts<T>(ent,packet.data,  packet);
        }else{
            _callFunc_result<T>(ent,packet.data,  packet);
        }
    }

    template<class T>
    void _callFunc_casts(Entityptr& ent, Dataptr data,  Packet& packet){
        pg::DataSet* setcast = dynamic_cast<DataSet*>(data.get());
        if( setcast != 0 ){
           _callFunc_set<T>( ent,setcast, packet);
        }else{
           throw std::runtime_error("Cast failed");
        }
    }


    virtual Processptr getBase() const
    {
      return std::make_shared<VariadicProcess>();
    }


    FunctorType _func;

};


}
