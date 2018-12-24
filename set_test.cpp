#include "set_test.h"

#define THREADS_NUMBER 4
#define ADDED_ELEMENTS_NUMBER 10000


void * remove_routine(void * arg) {

	Set<int> * set = reinterpret_cast<Set<int> *>(arg);

	for (int i = 0; i < ADDED_ELEMENTS_NUMBER; i++) {
	   
        bool isRemoved = set->remove(i);
        sum += i;

        if (isRemoved) {
            std::cout << "Thread remove " << i << std::endl;
        }
        else {
            std::cout << "Thread can't remove " << i << std::endl;
        }
	}

    pthread_exit(0);
}

void * read_routine(void * arg) {

	Set<int> * set = reinterpret_cast<Set<int> *>(arg);

	for (int i = 0; i < ADDED_ELEMENTS_NUMBER; i++) {
	   
        bool isContained = set->contains(i);

        if (isContained) {
            std::cout << "Thread read " << i << std::endl;
        }
        else {
            std::cout << "Thread can't read " << i << std::endl;
        }
	}

    pthread_exit(0);
}

void * write_routine(void * arg) {

	Set<int> * set = reinterpret_cast<Set<int> *>(arg);

	for (int i = 0; i < ADDED_ELEMENTS_NUMBER; i++) {

		bool isAdded = set->add(i);
	   
        if (isAdded) {
            std::cout << "Thread write " << i << std::endl;
        }
        else {
            std::cout << "Thread can't write " << i << std::endl;        	
        }
	}

    pthread_exit(0);
}

SetTest::SetTest(Set<int> * testedSet) {
    // init tested set
    set = testedSet;
}

void SetTest::runWritersTest() {

	std::cout << "Writers test start!" << std::endl;

	set->print();

	pthread_t writers[THREADS_NUMBER];

	for (int i = 0; i < THREADS_NUMBER; i++) {

		if (pthread_create(&writers[i], NULL, write_routine, set) != 0) {
            std::cout << "Writer " << i << " was failed" << std::endl;
		}

		pthread_join(writers[i], NULL);
	}

    set->print();

    std::cout << "Writers test end!" << std::endl;
}


void SetTest::runReadersTest() {

	std::cout << "Readers test start!" << std::endl;

	set->print();

	pthread_t readers[THREADS_NUMBER];

	for (int i = 0; i < THREADS_NUMBER; i++) {

		if (pthread_create(&readers[i], NULL, read_routine, set) != 0) {
            std::cout << "Reader " << i << " was failed" << std::endl;
		}

		pthread_join(readers[i], NULL);
	}

    set->print();

    std::cout << "Readers test end!" << std::endl;
}

void SetTest::runRemovalTest() {

	std::cout << "Removal test start!" << std::endl;

	set->print();

	pthread_t threads[THREADS_NUMBER];

	for (int i = 0; i < THREADS_NUMBER; i++) {

		if (pthread_create(&threads[i], NULL, remove_routine, set) != 0) {
            std::cout << "Thread " << i << " was failed" << std::endl;
		}

		pthread_join(threads[i], NULL);
	}

    set->print();

    std::cout << "Removal test end!" << std::endl;
}

void SetTest::runWritersReadersTest() {

	std::cout << "Writers-Readers test start!" << std::endl;

	set->print();

	pthread_t readers[THREADS_NUMBER];
	pthread_t writers[THREADS_NUMBER]; 

	for (int i = 0; i < THREADS_NUMBER; i++) {

        if (pthread_create(&writers[i], NULL, write_routine, set) != 0) {
            std::cout << "Writer " << i << " was failed" << std::endl;
		}

		if (pthread_create(&readers[i], NULL, read_routine, set) != 0) {
            std::cout << "Reader " << i << " was failed" << std::endl;
		}

		pthread_join(writers[i], NULL);
		pthread_join(readers[i], NULL);
	}

    set->print();

    std::cout << "Writers-Readers test end!" << std::endl;

}