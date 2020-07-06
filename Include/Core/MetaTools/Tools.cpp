#include "Communication/Future.h"
#include "GetType.h"

namespace Tools{


pg::Datatypeptr getType(pg::Future& t){
    return t.getType();
}

}
