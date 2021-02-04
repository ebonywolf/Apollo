#include "DataPair.h"
#include "Identification/KeyChain.h"


namespace pg {


Datatypeptr DataPair::getHashKey() const  {
    KeyChainptr key = KeyChainptr(new KeyChain());
    key->join(_from);
    key->join(_to);
    return key;
}


}
