#pragma once

#include <tuple>
#include <memory>


namespace Tools
{

#define Entityptr std::shared_ptr<pg::EditableProcess>
#define Functor std::function<OUTPUT(Entityptr, INPUT_F... )>&
#define Function_ptr OUTPUT (*func)(Entityptr, INPUT_F... )

class PlaceHolder;

template <unsigned int N >
struct _apply_func {


    template <typename OUTPUT, typename ...INPUT_F, typename ...INPUT_T, typename ...INPUT_S >
    static OUTPUT applyTuple( Function_ptr, Entityptr entity, const std::tuple<INPUT_T...>& t, INPUT_S&... args )
    {
        return _apply_func<N-1>::applyTuple( func,entity, t, std::get<N-1>( t ), args... );
    }

    template <typename OUTPUT, typename ...INPUT_F, typename ...INPUT_T, typename ...INPUT_S >
    static OUTPUT applyTuple( Functor func, Entityptr entity, const std::tuple<INPUT_T...>& t,INPUT_S&... args )
    {

        return _apply_func<N-1>::applyTuple( func,entity, t, std::get<N-1>( t ), args... );
    }
};


template <>
struct _apply_func<0> {
    template <typename OUTPUT, typename ...INPUT_F, typename ...INPUT_T, typename ...INPUT_S >
    static OUTPUT applyTuple( Function_ptr,Entityptr entity, const std::tuple<INPUT_T...>&,INPUT_S&... args )
    {
        return func(entity, args... );
    }
    template <typename OUTPUT, typename ...INPUT_F, typename ...INPUT_T, typename ...INPUT_S >
    static OUTPUT applyTuple( Functor func,Entityptr entity, const std::tuple<INPUT_T...>&,INPUT_S&... args )
    {
        return func(entity, args... );
    }
};


template < typename OUTPUT, typename ...INPUT_F, typename ...INPUT_T >
OUTPUT applyTuple( Function_ptr,Entityptr entity, std::tuple<INPUT_T...> const& input )
{
    return _apply_func<sizeof...(INPUT_T)>::applyTuple( func, entity, input );
}

template < typename OUTPUT, typename ...INPUT_F, typename ...INPUT_T>
OUTPUT applyTuple( Functor func,Entityptr entity, std::tuple<INPUT_T...> const& input )
{
    return _apply_func<sizeof...(INPUT_T)>::applyTuple( func,entity, input );
}

#undef Functor
#undef Func_ptr
#undef Entityptr


}

