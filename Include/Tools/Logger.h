#pragma once
#include <iostream>
#include <string>
#define _bitset(byte,nbit)   ((byte) |=  (1<<(nbit)))
#define _bitclear(byte,nbit) ((byte) &= ~(1<<(nbit)))
#define _bitflip(byte,nbit)  ((byte) ^=  (1<<(nbit)))
#define _bitcheck(byte,nbit) ((byte) &   (1<<(nbit)))
#define DEBUG

#define Debug(...) Logger::debug (__PRETTY_FUNCTION__, __VA_ARGS__)
#define Info(...) Logger::debug (__CLASS_NAME__, __VA_ARGS__)

#define INFO
struct Logger {

    Logger(std::ostream* out):_out(out){

    }
    template<class ...T>
    static void debug(const T&...t){
        #ifdef DEBUG
           console_out()._base(t...);
           console_out().print("\n");
        #else
        #endif
    }
    template<class ...T>
    static void info(const T&...t){
       #ifdef INFO
          console_out()._base(t...);
          console_out().print("\n");
       #endif
    }
    static Logger console_out(){
        static Logger coutLogger = Logger(&std::cout);
        return coutLogger;
    }

private:
    std::ostream* _out;


    void print(const std::string& s){
        auto& out = *_out;
        out<<s;
    }


    void print(const char* s){
        auto& out = *_out;
        out<<s;
    }

    template<class T>
    void print(const T& d){
        print(std::to_string(d));
    }
    template <class D>
    void _base(const D& d){
        print(d);
    }

    template <class D, class ...T>
    void _base(const D& d, const T&...t){
        _base(d);
        _base(t...);
    }

};
