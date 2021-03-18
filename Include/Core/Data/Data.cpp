#include "Data.h"

//long int   pg::Data::id_cont =0;
namespace pg{

std::ostream& operator<<(std::ostream& os, const Dataptr& data ){
     os<<data->toString();
     return os;
 }



}
