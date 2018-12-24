#ifndef CG_SYNC_SET_H
#define CG_SYNC_SET_H

#include "set.h"

template <class T>

class CGSyncSet : public Set <T> {

public:

    CGSyncSet();

	bool add(const T & item);
    bool remove(const T & item);
    bool contains(const T & item);
    void print();

    ~CGSyncSet();

private:

	class Node {

	public:

        Node(T initItem);
        ~Node() = default;

        // public variables
        T      item;
        int    key;
        Node * next;
    };

    Node *          head;
    pthread_mutex_t mutex;
};

#endif