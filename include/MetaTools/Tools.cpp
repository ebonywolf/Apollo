#include "GetType.h"
#include "Entities/Future.h"

namespace Tools{


pg::Datatypeptr getType(pg::Future& t){
    return t.getType();
}

}
