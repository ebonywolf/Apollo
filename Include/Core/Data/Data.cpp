#include "Data.h"

//long int   pg::Data::id_cont =0;
namespace pg{

std::ostream& operator<<(std::ostream& os, const Dataptr& data ){
     os<<data->toString();
     return os;
 }

/*
Dataptr Data::junction(  Dataptr other) const {
     auto ptr = std::static_pointer_cast<DataSet>(other);
     auto type = getType()->junction(other->getType());
     auto result = std::make_shared<DataSet>(type);

     result->join( _internal);
     if(ptr){
         result->join( ptr->_internal );
     }else{
         result->
     }
     join(other);

 }
*/
}
