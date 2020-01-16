#pragma once


#include <Apollo.h>


struct BoxInfo: public pg::GenericData<BoxInfo> {
    pg::Coord dim,pos;
BoxInfo(){}
    BoxInfo(int a,int b):pos(a,b){}
};

struct MyTesteFofinho: public pg::GenericData<MyTesteFofinho>
{
    MyTesteFofinho(){}
    MyTesteFofinho(int a):alce(a){}


    ~MyTesteFofinho(){}
    virtual pg::Datatypeptr getType() const
    {
        return std::make_shared<pg::Datatype>(name_id);
    }
    int alce;
};

class Box: public BoxInfo,  public pg::GenericEntity<Box>{
public:
    Box(): GenericEntity(__CLASS_NAME__ ,doShit){
    }
    Box(BoxInfo& b):BoxInfo(b){
    }

    static MyTesteFofinho doShit(Myptr me, MyTesteFofinho cmd){
        return MyTesteFofinho(cmd.alce+1);
    }


/*
    static Node paint(Myptr me,Command box){
        if(!me){
            std::cout<< "Fooo" << std::endl;
        }
        std::cout<< "Me:"<<me->getHashKey() <<std::endl;
        std::cout<<"Got box:"<< *box<<std::endl;
        std::cout<< "Key:"<<box->getType()->getHashKey() << std::endl;

        return Ack(666);
    }
    */




};
using Boxptr = std::shared_ptr<Box>;

class BoxCreator: public pg::GenericEntity<BoxCreator>{
public:

    BoxCreator():GenericEntity(__CLASS_NAME__,creator){
    }

    static std::shared_ptr<Box> creator(Myptr me, BoxInfo info){
        std::cout<<__PRETTY_FUNCTION__<<std::endl;
        //std::cout<<"Creating box:"<<info<<std::endl;
        return std::make_shared<Box>(info);
    }

};

