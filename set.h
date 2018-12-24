#ifndef SET_H
#define SET_H

#include <pthread.h>
#include <bits/stdc++.h> 
#include <iostream>

template <class T>

class Set {

public:	

    virtual bool add(const T & item) = 0;
    virtual bool remove(const T & item) = 0;
    virtual bool contains(const T & item) = 0;
    virtual void print() = 0;

    static void error(const char * errorMsg) {
    	std::cout << "ERROR: " << errorMsg << std::endl;
    }
} ;

#endif