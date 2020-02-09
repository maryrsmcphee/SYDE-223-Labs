#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.h"
//Define Assertions
#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {

public:
    /** PURPOSE: New empty list is valid */
    bool test1() {
        DronesManager manager;
        ASSERT_TRUE(manager.get_size() == 0)
        ASSERT_TRUE(manager.empty() == true)
        ASSERT_TRUE(manager.first == NULL)
        ASSERT_TRUE(manager.last == NULL)
        return true;
    }

    /** PURPOSE: insert_front() and insert_back() on zero-element list */
    bool test2() {
        DronesManager manager1, manager2;
        manager1.insert_front(DronesManager::DroneRecord(100));
        manager2.insert_back(DronesManager::DroneRecord(100));

        ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
        ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
        ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
        ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
        ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
        ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
        return true;
    }

    // TODO: Mary
    // PURPOSE: select() and search() work properly
    bool test3() {
        DronesManager manager1, manager2;
        manager1.insert(1, 0);
        ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(1));
        return true;
    }

    /** PURPOSE: remove_front() and remove_back() on one-element list  */
    bool test4() {
        /** ----- Test  remove_front() on Multi Element List----- */
        DronesManager manager3, manager4;
        // Populate List ADT
        const int initialListSize = 30;
        for (int i = 1; i <= initialListSize; i++) {
            manager3.insert_front(DronesManager::DroneRecord(i));
            manager4.insert_front(DronesManager::DroneRecord(i));
            // check to make sure size is correctly indexed
            ASSERT_TRUE(manager3.size == i);
            ASSERT_TRUE(manager4.size == i);
        }
        manager3.remove_front();
        manager4.remove_front();
        ASSERT_TRUE(manager3.select(0) == initialListSize - 1);
        ASSERT_TRUE(manager4.select(0) == initialListSize - 1);
        manager3.remove_front();
        manager4.remove_front();
        ASSERT_TRUE(manager3.select(0) == initialListSize - 2);
        ASSERT_TRUE(manager4.select(0) == initialListSize - 2);
        manager3.remove_front();
        manager4.remove_front();
        ASSERT_TRUE(manager3.select(0) == initialListSize - 3);
        ASSERT_TRUE(manager4.select(0) == initialListSize - 3);

        /** ----- Test remove_front() on Single Element List----- */
        DronesManager manager5, manager6;
        manager5.insert_front(DronesManager::DroneRecord(10));
        manager6.insert_front(DronesManager::DroneRecord(10));
        manager5.remove_front();
        manager6.remove_front();
        // assert that the size has be decremented
        ASSERT_TRUE(manager5.size == 0);
        ASSERT_TRUE(manager6.size == 0);
        ASSERT_TRUE(manager5.first == NULL && manager5.last == NULL);
        ASSERT_TRUE(manager6.first == NULL && manager6.last == NULL);

        /** Test  remove_front() on Multi Element List----- */
        DronesManager manager7, manager8;
        // Populate List ADT
        const int initialListSize2 = 30;
        for (int i = 1; i <= initialListSize2; i++) {
            manager7.insert_front(DronesManager::DroneRecord(i));
            manager8.insert_front(DronesManager::DroneRecord(i));
            // check to make sure size is correctly indexed
            ASSERT_TRUE(manager7.size == i);
            ASSERT_TRUE(manager8.size == i);
        }
        manager7.remove_back();
        manager8.remove_back();
        ASSERT_TRUE(manager7.last->droneID == 2);
        ASSERT_TRUE(manager8.last->droneID == 2);
        manager7.remove_back();
        manager8.remove_back();
        ASSERT_TRUE(manager7.last->droneID == 3);
        ASSERT_TRUE(manager8.last->droneID == 3);
        manager7.remove_back();
        manager8.remove_back();
        ASSERT_TRUE(manager7.last->droneID == 4);
        ASSERT_TRUE(manager8.last->droneID == 4);

        /** ----- Test remove_front() on Single Element List----- */
        DronesManager manager9, manager10;
        manager5.insert_front(DronesManager::DroneRecord(10));
        manager6.insert_front(DronesManager::DroneRecord(10));
        manager5.remove_back();
        manager6.remove_back();
        // assert that the size has be decremented
        ASSERT_TRUE(manager9.size == 0);
        ASSERT_TRUE(manager10.size == 0);
        ASSERT_TRUE(manager9.first == NULL && manager5.last == NULL && manager9.size == 0);
        ASSERT_TRUE(manager10.first == NULL && manager6.last == NULL && manager10.size == 0);

        return true;
    }

    // PURPOSE: replace() and reverse_list() work properly
    // TODO: Mary
    bool test5() {
        return false;
    }

    /** PURPOSE: insert_front() keeps moving elements forward */
    bool test6() {
        DronesManager manager3, manager4;
        // Populate List ADT
        const int initialListSize = 3000;
        for (int i = 1; i <= initialListSize; i++) {
            manager3.insert_front(DronesManager::DroneRecord(i));
            manager4.insert_front(DronesManager::DroneRecord(i));
            // check to make sure size is correctly indexed
            ASSERT_TRUE(manager3.size == i);
            ASSERT_TRUE(manager4.size == i);
        }
        /*
         * Above we have created a list ADT where the last node's droneID is
         * going to be the greatest. To ensure that the list is
         * always pushing elements forward we can iterate through
         * the linked list and assert that the nth element is always less
         * then nth-1 element. If this is the case, then it means that
         * the elements are being added to the beginning of the list.
         * */
        for (int i = 0; i < initialListSize - 1; i++) {
            ASSERT_TRUE(manager3.select(i).droneID > manager3.select(i + 1).droneID);
            ASSERT_TRUE(manager4.select(i).droneID > manager4.select(i + 1).droneID)
        }
        return true;
    }

    /** PURPOSE: inserting at different positions in the list */
    bool test7() {
        DronesManager manager11, manager12;
        // Populate List ADT
        const int initialListSize = 100;
        for (int i = 1; i <= initialListSize; i++) {
            manager11.insert_front(DronesManager::DroneRecord(i));
            manager12.insert_front(DronesManager::DroneRecord(i));
            // check to make sure size is correctly indexed
            ASSERT_TRUE(manager11.size == i);
            ASSERT_TRUE(manager12.size == i);
        }
        /** Insert at random position */
        int pos1 = rand() % 100 + 1;
        int pos2 = rand() % 100 + 1;
        manager11.insert(DronesManager::DroneRecord(500), pos1);
        manager12.insert(DronesManager::DroneRecord(500), pos2);
        ASSERT_TRUE(manager11.select(pos1).droneID == 500);
        ASSERT_TRUE(manager12.select(pos2).droneID == 500);

        /** insert at beginning */
        manager11.insert(DronesManager::DroneRecord(500), 0);
        manager12.insert(DronesManager::DroneRecord(500), 0);
        ASSERT_TRUE(manager11.select(0).droneID == 500);
        ASSERT_TRUE(manager12.select(0).droneID == 500);

        /** insert at end */
        manager11.insert(DronesManager::DroneRecord(500), 100);
        manager12.insert(DronesManager::DroneRecord(500), 100);
        ASSERT_TRUE(manager11.select(100).droneID == 500);
        ASSERT_TRUE(manager12.select(100).droneID == 500);
        return true;
    }

    /** PURPOSE: try to remove too many elements, then add a few elements */
    bool test8() {
        DronesManager manager13, manager14;
        // Populate List ADT
        const int initialListSize = 2;
        const int secondaryListSize = 20;
        for (int i = 1; i <= initialListSize; i++) {
            manager13.insert_front(DronesManager::DroneRecord(i));
            manager14.insert_front(DronesManager::DroneRecord(i));
            // check to make sure size is correctly indexed
            ASSERT_TRUE(manager13.size == i);
            ASSERT_TRUE(manager14.size == i);
        }

        manager13.remove_back();
        manager13.remove_back();
        manager14.remove_back();
        manager14.remove_back();

        /** Attempt to remove element when first is NULL */
        ASSERT_FALSE(manager13.remove_back());
        ASSERT_FALSE(manager14.remove_back());

        /** Add elements */
        for (int i = 1; i <= secondaryListSize; i++) {
            manager13.insert_front(DronesManager::DroneRecord(i));
            manager14.insert_front(DronesManager::DroneRecord(i));
            // check to make sure size is correctly indexed
            ASSERT_TRUE(manager13.size == i);
            ASSERT_TRUE(manager14.size == i);

            /** Assert that the first node is always the last node added and that the last doesnt change */
            ASSERT_TRUE(manager13.last->droneID == 1 && manager13.first->droneID == i);
            ASSERT_TRUE(manager14.last->droneID == 1 && manager14.first->droneID == i)
        }
        return true;
    }

    /** PURPOSE: lots of inserts and deletes, some of them invalid */
    bool test9() {
        DronesManager manager, manager1;
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(100), 0))
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(102), 0))
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(101), 1))

        /** insertion out of bounds */
        ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(100), 8))
        manager.print();

        /** removal of nodes */
        const int initialListSize = 100;
        for (int i = 1; i <= initialListSize; i++) {
            manager1.insert_front(DronesManager::DroneRecord(i));
            // check to make sure size is correctly indexed
            ASSERT_TRUE(manager1.size == i);
        }
        // decrement testing by 1 since our array in in decreasing order
        /** test 1 */
        unsigned int postID1 = manager1.select(5).droneID - 1;
        manager1.remove(5);
        ASSERT_TRUE(manager1.select(5).droneID == postID1);
        /** test  2 */
        unsigned int postID2 = manager1.select(30).droneID - 1;
        manager1.remove(30);
        ASSERT_TRUE(manager1.select(30).droneID == postID2);

        /** invalid index[s] */
        ASSERT_FALSE(manager1.remove(-4)); // invalid
        ASSERT_FALSE(manager1.remove(initialListSize + 1)) // out of bounds

        /** remove last node */
        unsigned int postID3 = manager1.select(manager1.size - 1).droneID + 1;
        manager1.remove(manager1.size - 1);
        ASSERT_TRUE(manager1.select(manager1.size - 1).droneID == postID3);
        /** remove first node */
        unsigned int postID4 = manager1.select(0).droneID - 1;
        manager1.remove(0);
        ASSERT_TRUE(manager1.select(0).droneID == postID4);

        return true;
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
