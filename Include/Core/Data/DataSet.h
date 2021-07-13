#pragma once

#include "Data.h"

namespace pg{

struct DataSet: public  Data {

    DataSet(Datatypeptr type):type(type){
    }

    void join( Dataptr other){
        //Todo update Type
        auto ptr = std::dynamic_pointer_cast<DataSet>(other);
         if(ptr){
             join(ptr->_internal);
         }else{
             _internal.push_back(other);
         }
    }
    void join(std::vector<Dataptr> other){
        _internal.insert(std::end(_internal), std::begin(other), std::end(other));
    }

    virtual std::string toString() const {
        std::string alce="";
        for(const auto& x: _internal){
            alce+= x->toString() += " | ";
        }
        if(_internal.empty())
            alce = "Empty set:"+type->toString();
        return alce;
    }

    virtual Datatypeptr getType() const{
        return type;
    }

private:
     std::vector<Dataptr> _internal;
     Datatypeptr type;
};

}
