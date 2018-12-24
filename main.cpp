#include "lazy_sync_set.h"
#include "lazy_sync_set.cpp"

#include "cg_sync_set.h"
#include "cg_sync_set.cpp"

#include "set_test.h"
#include "set_test.cpp"
	

int main(void) {

    // create tested sets
	Set<int> * lazySyncSet = new LazySyncSet<int>();
	Set<int> * cgSyncSet   = new CGSyncSet<int>();

    // init set tests
    SetTest lazySyncSetTest(lazySyncSet);
    SetTest cgSyncSetTest(cgSyncSet);

    // run writers tests
    lazySyncSetTest.runWritersTest();
    cgSyncSetTest.runWritersTest();

    // run readers tests
    lazySyncSetTest.runReadersTest();
    /cgSyncSetTest.runReadersTest();

    // run removal tests
    lazySyncSetTest.runRemovalTest();
    cgSyncSetTest.runRemovalTest();

    //lazySyncSetTest.runWritersReadersTest();
    lazySyncSetTest.runWritersReadersTest();
    cgSyncSetTest.runWritersReadersTest();

    // delete tested sets
    delete lazySyncSet;
    delete cgSyncSet; 

	return 0;
}