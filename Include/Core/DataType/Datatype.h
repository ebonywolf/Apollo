#pragma once
#ifndef DATA_TYPE_H
#define DATA_TYPE_H

//

#include <DatatypeBase.h>
#include <Identification/KeySet.h>

namespace pg {


struct Datatype: public EditableDatatype
{ //defines dataTypes, not data itself
    static const Datatypeptr getNull();

    Datatype() :_key( std::make_shared<KeySet>() )
    {
    }
    Datatype(std::string _name):
        _key( std::make_shared<KeySet>() )
    {
        _key->join(std::make_shared<HashKey>(_name));
    }
    virtual bool contains(Datatypeptr d)const override{
        return _key->contains(d);
    }

    virtual void join( Datatypeptr other)override;
    virtual std::string toString() const override;
    virtual Datatypeptr getFrom() const override;
    virtual Datatypeptr getTo() const override;
    virtual Datatypeptr getHashKey() const override;
    virtual Datatypeptr getInverseDataPair()const override;
    virtual Datatypeptr getDataPair()const override;
    virtual Datatypeptr junction( Datatypeptr other)const override;


private:
    std::shared_ptr<KeySet> _key;
};







}

#endif // DATA_TYPE_H
