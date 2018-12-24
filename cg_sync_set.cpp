#include "cg_sync_set.h"

template <class T>

CGSyncSet<T>::CGSyncSet() {

    // init head pointer
	head = new Node(INT_MIN);
	if (head == nullptr) {
		Set<T>::error("Function new() returns nullptr");
	}

	head->next = new Node(INT_MAX);
	if (head->next == nullptr) {
		Set<T>::error("new() returns nullptr");
	}

    // init mutex 
	mutex = PTHREAD_MUTEX_INITIALIZER;
    if (pthread_mutex_init(&mutex, NULL) != 0) {
    	Set<T>::error("Mutex initialization was failed");
    }
}

template <class T>

bool CGSyncSet<T>::add(const T & item) {

    int key = std::hash<T>()(item);
    
    // lock mutex
    if (pthread_mutex_lock(&mutex) != 0) {
    	Set<T>::error("Mutex locking was failed");
    }

    Node * pred = head;
    Node * curr = pred->next;
    
    while (curr->key < key) {
        pred = curr;
        curr = curr->next;
    }
    
    if (curr->key == key) {

    	// unlock mutex
        if (pthread_mutex_unlock(&mutex) != 0) {
        	Set<T>::error("Mutex unlocking was failed");
        }

        return false;
    } 
    else { 

        // create new node       
        Node * node = new Node(item);
        if (node == nullptr) {
        	Set<T>::error("new() returns nullptr");
        }

        node->next = curr;
        pred->next = node;

        // unlock mutex
        if (pthread_mutex_unlock(&mutex) != 0) {
        	Set<T>::error("Mutex unlocking was failed");
        }

        return true;
    }
}

template <class T>

bool CGSyncSet<T>::remove(const T & item) {

    int key = std::hash<T>()(item);

    // lock mutex
    if (pthread_mutex_lock(&mutex) != 0) {
    	Set<T>::error("Mutex locking was failed");
    }

    Node * pred = head;
    Node * curr = pred->next;

    while (curr->key < key) {
        pred = curr;
        curr = curr->next;
    }

    if (curr->key == key) {

    	// delete curr node
        pred->next = curr->next;
        delete curr;

        // unlock mutex
        if (pthread_mutex_unlock(&mutex) != 0) {
        	Set<T>::error("Mutex unlocking was failed");
        }

        return true;
    } 
    else {
    	
    	// unlock mutex
        if (pthread_mutex_unlock(&mutex) != 0) {
        	Set<T>::error("Mutex unlocking was failed");
        }

        return false;
    }
}

template <class T>

bool CGSyncSet<T>::contains(const T & item) {

	int key = std::hash<T>()(item);

	// lock mutex
    if (pthread_mutex_lock(&mutex) != 0) {
    	Set<T>::error("Mutex locking was failed");
    }

    Node * curr = head;
    while (curr->key < key) {
        curr = curr->next;
    }
    
    // unlock mutex
    if (pthread_mutex_unlock(&mutex) != 0) {
     	Set<T>::error("Mutex unlocking was failed");
    }
    
    return curr->key == key;
}

template <class T>

void CGSyncSet<T>::print() {

	Node * curr = head;

	std::cout << "CGSyncSet: ";

	while (curr != nullptr) {
		std::cout << curr->item << "  ";
        curr = curr->next;
	}

	std::cout << std::endl;
}

template <class T>

CGSyncSet<T>::~CGSyncSet() {

	Node * curr = head;
	Node * next = nullptr;

	while (curr != nullptr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
}

template <class T>

CGSyncSet<T>::Node::Node(T initItem) {

	item   = initItem;
    key    = std::hash<T>()(item);
    next   = nullptr;
}
