#include "lazy_sync_set.h"

template <class T>

LazySyncSet<T>::LazySyncSet() {

    // init head pointer
	head = new Node(INT_MIN);
	if (head == nullptr) {
		Set<T>::error("Function new() returns nullptr");
	}

	head->next = new Node(INT_MAX);
	if (head->next == nullptr) {
		Set<T>::error("new() returns nullptr");
	}
}

template <class T>

bool LazySyncSet<T>::add(const T & item) {

	int key = std::hash<T>()(item);

    while (true) {
        Node * pred = head;
        Node * curr = head->next;

        while (curr->key < key) {
            pred = curr;
            curr = curr->next;
        }

        pred->lock();
        curr->lock();
        
        if (validate(pred, curr)) {

            if (curr->key == key) {
                pred->unlock();
                curr->unlock();

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

                pred->unlock();
                curr->unlock();

                return true;
            }
        }
    }
}

template <class T>

bool LazySyncSet<T>::remove(const T & item) {

    int key = std::hash<T>()(item);

    while (true) {
        Node * pred = head;
        Node * curr = head->next;

        while (curr->key < key) {
            pred = curr;
            curr = curr->next;
        }

        pred->lock();
        curr->lock();

        if (validate(pred, curr)) {

            if (curr->key != key) {
            	pred->unlock();
                curr->unlock();

                return false;
            }
            else {

            	// delete curr node
                curr->marked = true;
                pred->next = curr->next;

                pred->unlock();
                curr->unlock();

                delete curr;

                return true;
            }
        }
    }
}

template <class T>

bool LazySyncSet<T>::contains(const T & item) {

    int key = std::hash<T>()(item);
    
    Node * curr = head;

    while (curr->key < key) {
        curr = curr->next;
    }
    
    return curr->key == key && !curr->marked;
}

template <class T>

void LazySyncSet<T>::print() {

	Node * curr = head;

	std::cout << "LazySyncSet: ";

	while (curr != nullptr) {
		std::cout << curr->item << "  ";
        curr = curr->next;
	}

	std::cout << std::endl;
}

template <class T>

LazySyncSet<T>::~LazySyncSet() {

	Node * curr = head;
	Node * next = nullptr;

	while (curr != nullptr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
}

template <class T>

bool LazySyncSet<T>::validate(Node * pred, Node * curr) {

    return !pred->marked && !curr->marked && pred->next == curr;
}

template <class T>

LazySyncSet<T>::Node::Node(T initItem) {

    // init node variables
	item   = initItem;
    key    = std::hash<T>()(item);
    marked = false;
    next   = nullptr;

    // init mutex
    mutex = PTHREAD_MUTEX_INITIALIZER;
    if (pthread_mutex_init(&mutex, NULL) != 0) {
    	Set<T>::error("Mutex initialization was failed");
    }
}

template <class T>

bool LazySyncSet<T>::Node::lock() {

	  if (pthread_mutex_lock(&mutex) != 0) {
        Set<T>::error("Mutex locking was failed");
	  	return false;
	  }

	  return true;
}
  
template <class T>

bool LazySyncSet<T>::Node::unlock() {

	if (pthread_mutex_unlock(&mutex) != 0) {
        Set<T>::error("Mutex unlocking was failed");
		return false;
	}

	return true;
}
