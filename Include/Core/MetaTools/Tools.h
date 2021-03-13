#pragma once
#include <memory>


namespace pg{
    class Data;
    using Dataptr = std::shared_ptr<Data>;

    template <class T>
    struct GenericData;

    template <class T>
    struct Generic_GenericData;

}




