#ifndef SET_TEST_H
#define SET_TEST_H

#include "set.h"

class SetTest {

public:

	SetTest(Set<int> * testedSet);

	void runWritersTest();
	void runReadersTest();
	void runRemovalTest();
	void runWritersReadersTest();

    ~SetTest() = default;

private:

	Set<int> * set;
};

#endif
