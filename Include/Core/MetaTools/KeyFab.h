#pragma once 

#include "Identification/KeyChain.h"
#include "MetaTools/GetType.h"


namespace pg{


//Creates a keychain and joins with this pointer;
template<class CURRENT_TYPE>
void createKey_base(KeyChainptr createdKey)
{
    CURRENT_TYPE c;
    createdKey->join(Tools::getType(c));
}

template<class CURRENT_TYPE, class NEXT_TYPE, class ...TYPES>
void createKey_base(KeyChainptr createdKey)
{
    CURRENT_TYPE c;
    createdKey->join(Tools::getType(c));
    createKey_base<NEXT_TYPE, TYPES...>(createdKey);
}



template<class CURRENT_TYPE>
void createKey_base_params(KeyChainptr createdKey,CURRENT_TYPE& current)
{
    createdKey->join(Tools::getType(current));
}

template<class CURRENT_TYPE, class ...TYPES>
void createKey_base_params(KeyChainptr createdKey,CURRENT_TYPE& current, TYPES&... other)
{
    createdKey->join(Tools::getType(current));
    createKey_base_params(createdKey, other...);
}



template<class OUTPUT, class ...INPUT>
Datatypeptr createKey()
{
    OUTPUT output;
    Datatypeptr outputKey = Tools::getType(output);
    KeyChainptr inputKeyset = std::make_shared<KeyChain>();
    createKey_base<INPUT...>(inputKeyset);

    Datatypeptr par = std::make_shared<DataPair>(outputKey, inputKeyset);
    return par;
}

}
