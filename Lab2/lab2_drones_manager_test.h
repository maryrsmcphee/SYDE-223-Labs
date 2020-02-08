#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.h"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
    // PURPOSE: New empty list is valid
    bool test1() {
        DronesManager manager;
        ASSERT_TRUE(manager.get_size() == 0)
        ASSERT_TRUE(manager.empty() == true)
        ASSERT_TRUE(manager.first == NULL)
        ASSERT_TRUE(manager.last == NULL)
        return true;
    }

    // PURPOSE: insert_front() and insert_back() on zero-element list
    bool test2() {
        DronesManager manager1, manager2;
        manager1.insert_front(DronesManager::DroneRecord(100));
        manager2.insert_back(DronesManager::DroneRecord(100));

        ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
        ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last )
        ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
        ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
        ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
        ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
        return true;
    }

    // TODO: Mary
    // PURPOSE: select() and search() work properly
    bool test3() {
        return false;
    }

    // PURPOSE: remove_front() and remove_back() on one-element list
    // TODO Sammy
    bool test4() {
        DronesManager manager3, manager4;
        // Populate List ADT
        const int initialListSize = 30;
        for(int i = 1; i <= initialListSize; i ++){
            manager3.insert_front(DronesManager::DroneRecord(i));
            manager4.insert_front(DronesManager::DroneRecord(i));
            // check to make sure size is correctly indexed
            ASSERT_TRUE(manager3.size  == i);
            ASSERT_TRUE(manager4.size == i);
        }
        cout<<manager3.select(1).droneID<<endl;
     //   manager3.remove_front();
      //  manager4.remove_front();
    //    ASSERT_TRUE(manager3.select(0). == 1);
        return true;
    }

    // PURPOSE: replace() and reverse_list() work properly
    // TODO: Mary
    bool test5() {
        return false;
    }

    // PURPOSE: insert_front() keeps moving elements forward
    // TODO Sammy
    bool test6() {
        return false;
    }

    // PURPOSE: inserting at different positions in the list
    // TODO Sammy
    bool test7() {
        return false;
    }
    // TODO Sammy
    // PURPOSE: try to remove too many elements, then add a few elements
    bool test8() {
        return false;
    }

    // PURPOSE: lots of inserts and deletes, some of them invalid
    // TODO Sammy
    bool test9() {
        return false;
    }

    // PURPOSE: inserts into an unsorted list, then sort the list
    // TODO Mary
    bool test10() {
        return false;
    }

    // PURPOSE: insert and remove into sorted manager in ascending order
    // TODO Mary
    bool test11() {
        return false;
    }

    // PURPOSE: insert and remove into sorted manager in descending order
    // TODO Mary
    bool test12() {
        return false;
    }
};

#endif
