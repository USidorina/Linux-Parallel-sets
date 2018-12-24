#ifndef LAZY_SYNC_SET_H
#define LAZY_SYNC_SET_H

#include "set.h"

template <class T>

class LazySyncSet : public Set<T> {

public:

    LazySyncSet();

	bool add(const T & item);
    bool remove(const T & item);
    bool contains(const T & item);
    void print();

    ~LazySyncSet();

private:

	class Node {

	public:

        Node(T initItem);

        bool lock();
        bool unlock();

        ~Node() = default;

        // public variables
        T      item;
        int    key;
        bool   marked;
        Node * next;

    private:

    	pthread_mutex_t mutex;
    };

    Node * head;

   	bool validate(Node * pred, Node * curr);
};

#endif