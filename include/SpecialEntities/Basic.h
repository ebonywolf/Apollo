#pragma once

#include <Entity/SpecialEntities.h>
#include <memory>

namespace pg
{

template <class MY_TYPE>
struct Singleton: public pg::GenericEntity<MY_TYPE> {
    Singleton(){}

    template<class ...T>
    Singleton(std::string args, T...t):
        GenericEntity<MY_TYPE>(args,t...){
    }
    //template<typename ...T>
    //Singleton( T...t):GenericEntity( typeid(MY_TYPE).name(), t... ){}

    Singleton(const Singleton<MY_TYPE>&) = delete;
    Singleton& operator=(const Singleton<MY_TYPE>&) = delete;

    ~Singleton(void){}

    static std::shared_ptr<MY_TYPE> get( MY_TYPE* val=0  )
    {
        if(val) {
            _me.reset(val);
        }
        if(!_me) {
            _me=std::make_shared<MY_TYPE>();
        }
        return _me;
    }

    template<class ...T>
    static std::shared_ptr<MY_TYPE> get( T...t  )
    {
        return get(new MY_TYPE(t...) );
    }

private:
    inline static std::shared_ptr<MY_TYPE> _me;
};


template <class MY_TYPE>
struct MultiInstance : public pg::GenericEntity<MY_TYPE> {
    template<typename ...T>
    MultiInstance(std::string args, T...t):GenericEntity<MY_TYPE>(args,t...){}

    template<typename ...T>
    MultiInstance( T...t):GenericEntity<MY_TYPE>( typeid(MY_TYPE).name(), t... ){}


    static std::shared_ptr<MY_TYPE> get()
    {
        //TODO guarantee cleanup
        return std::make_shared<MY_TYPE>();
    }
};


template < class KEY,class MY_TYPE>
struct MapInstance  {

    std::shared_ptr<MY_TYPE> at(KEY key)
    {
        if(!instance_map[key]) {
            instance_map[key] = std::make_shared<MY_TYPE>();
        }
        return  instance_map[key];
    }
private:
    std::unordered_map<KEY, std::shared_ptr<MY_TYPE>> instance_map;
};


}

