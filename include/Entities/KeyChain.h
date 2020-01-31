#pragma once

#include <deque>
#include <string>

#include <map>
#include <iostream>
#include "DatatypeBase.h"
#include "KeySet.h"


namespace pg{

class KeyChain: public EditableDatatype {
public:
    KeyChain(){
    }
    virtual ~KeyChain(){}
    virtual void join(const Datatypeptr other);

    virtual bool contains(Datatypeptr d)const override;

    virtual std::string toString() const;
    virtual Datatypeptr junction( Datatypeptr other)const ;
    virtual Datatypeptr getHashKey() const;
    virtual Datatypeptr getFrom() const;
    virtual Datatypeptr getTo() const;
    virtual Datatypeptr getInverseDataPair()const;
    virtual Datatypeptr getDataPair()const;

private:
    std::deque< Datatypeptr> _internal;
};
using KeyChainptr = std::shared_ptr<KeyChain>;


}





