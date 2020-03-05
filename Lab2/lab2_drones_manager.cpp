/**
 * LAB 2: Linked List Data Structure and C++ Inheritance
 * Mary McPhee: 20717047
 * Sammy Robens-Paradise: 20709541
 */

#include "lab2_drones_manager.h"

// creates new empty DronesManager
DronesManager::DronesManager() {
    first = nullptr;
    last = nullptr;
    size = 0;
}

// Destroys instance and frees up dynamically allocated memory
DronesManager::~DronesManager() {
}

/**
 *
 * @param lhs
 * @param rhs
 * @return bool
 */
bool operator==(const DronesManager::DroneRecord &lhs, const DronesManager::DroneRecord &rhs) {
    /**  TA says we only need to compare the ID */
    return (lhs.droneID == rhs.droneID);
}

/**
 * returns the size or list
 * @return size
 */

unsigned int DronesManager::get_size() const {
    return size;
}

/**
 * returns true if a list is NULL
 * @return bool
 */
bool DronesManager::empty() const {
    return (first == NULL && last == NULL && size == 0);
}

/**
 * returns the drone record from a given index
 * @param index
 * @return *DroneRecord
 */
DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    if (index < 0) {
        cout << "Unable to select: Index is outside of bounds" << endl;
        return NULL;
    } else if (index >= size) {
        return *last;
    } else if (empty()) {
        cout << "Unable to select: List is empty returning DroneRecord(0)" << endl;
        return DroneRecord(0);
    } else {
        int count = 0;
        DroneRecord *current = first;
        while (count < index && current != NULL) {
            current = current->next;
            count++;
        }
        return *current;
    }
}

/**
 * searches for a specific element in the list
 * @param value
 * @return
 */
unsigned int DronesManager::search(DroneRecord value) const {
    if (empty()) {
        return 0;
    } else {
        DroneRecord *current = first;
        for (int i = 0; i < size; ++i) {
            if (*current == value) {
                return i;
            }
            current = current->next;
        }
        return size;
    }
}

/**
 * print helper
 */
void DronesManager::print() const {
    DroneRecord *cur = first;
    for (int i = 0; i < size; i++) {
        cout << "Drone ID = " << cur->droneID << endl;
        cout << "Year bought = " << cur->yearBought << endl;
        cout << "Range = " << cur->range << endl;
        cur = cur->next;
    }
}

/**
 * inserts value at a given index in the list
 * @param value
 * @param index
 * @return bool
 */

bool DronesManager::insert(DroneRecord value, unsigned int index) {
    if (index > size) {
        return false;
    } else if (empty()) {
        if (index == 0) {
            DroneRecord *recordToInsert = new DroneRecord(value);
            first = recordToInsert;
            last = recordToInsert;
            recordToInsert->prev = nullptr;
            recordToInsert->next = nullptr;
            size++;
            return true;
        }
    } else {
        DroneRecord *current = this->first;
        DroneRecord *prev = nullptr;
        DroneRecord *recordToInsert = new DroneRecord(value);
        // sets the new drone equal to value
        if (index == 0) {
            first = recordToInsert;
            recordToInsert->prev = nullptr;
            recordToInsert->next = current;
            current->prev = first;
            size++;
            return true;
        } else if (index >= size) { // since unsigned int, no need to check neg case
            cout << "index out of bounds." << endl;
            last->next = recordToInsert;
            recordToInsert->prev = last;
            last = recordToInsert;
            recordToInsert->next = NULL;
            size++;
            return true;
        } else {
            int ittVerifySize = 0;
            while (current->next != nullptr && ittVerifySize != index) {
                prev = current;
                current = current->next;
                ittVerifySize++;
            }
            prev->next = recordToInsert;
            recordToInsert->next = current;
            current->prev = recordToInsert;
            recordToInsert->prev = prev;
            size++;
            return true;
        }
    }
}

/**
 * inserts node at the beginning of the list
 * @param value
 * @return bool
 */
bool DronesManager::insert_front(DroneRecord value) {
    DroneRecord *recordToInsert = new DroneRecord(value);
    if (empty()) {
        first = recordToInsert;
        last = recordToInsert;
        recordToInsert->prev = NULL;
        recordToInsert->next = NULL;
        size++;
        return true;
    } else {
        first->prev = recordToInsert;
        recordToInsert->next = first;
        first = recordToInsert;
        recordToInsert->prev = NULL;
        size++;
        return true;
    }
}

/**
 * inserts node at the end of a list
 * @param value
 * @return bool
 */
bool DronesManager::insert_back(DroneRecord value) {
    DroneRecord *recordToInsert = new DroneRecord(value);
    if (empty()) {
        first = recordToInsert;
        last = recordToInsert;
        recordToInsert->prev = NULL;
        recordToInsert->next = NULL;
        size++;
        return true;
    } else {
        last->next = recordToInsert;
        recordToInsert->prev = last;
        last = recordToInsert;
        recordToInsert->next = NULL;
        size++;
        return true;
    }
}

/**
 * removes node at a given index in the list
 * @param index
 * @return bool
 */
bool DronesManager::remove(unsigned int index) {
    if (index > size || index < 0 || empty()) {
        return false;
    } else if (index == size && size == 1 && first->next == NULL) {
        first->prev = NULL;
        first = NULL;
        last = NULL;
        size--;
    } else if (index == 0) {
        first = first->next;
        delete first->prev;
        first->prev = NULL;
        size--;
        return true;
    } else {
        int count = 0;
        DroneRecord *nodeToRemove = first;
        while (count < index && nodeToRemove != nullptr) {
            nodeToRemove = nodeToRemove->next;
            count++;
        }
        if (nodeToRemove == last) {
            last = last->prev;
            delete last->next;
            last->next = NULL;
            size--;
            return true;
        } else {
            nodeToRemove->prev->next = nodeToRemove->next;
            nodeToRemove->next->prev = nodeToRemove->prev;
            nodeToRemove = NULL;
            delete nodeToRemove;
            size--;
            return true;
        }
    }
}

/**
 * removes first node in a list and decrements the size
 * @return bool
 * */
bool DronesManager::remove_front() {
    if (first == NULL) {
        return false;
    } else if (size == 1 && first->next == NULL) {
        first->prev = NULL;
        first = NULL;
        last = NULL;
        size--;
        return true;
    } else {
        first = first->next;
        delete first->prev;
        first->prev = NULL;
        size--;
        return true;
    }
}

/**
 * removes last node in list
 * @return bool
 */
bool DronesManager::remove_back() {
    if (first == NULL) {
        return false;
    } else if (size == 1 && first->next == NULL) {
        first->prev = NULL;
        first = NULL;
        last = NULL;
        size--;
    } else {
        DroneRecord *current = first;
        while (current->next->next) {
            current = current->next;
        }
        last = last->prev;
        delete last->next;
        last->next = NULL;
        size--;
        return true;
    }
}

/**
 * replaces the node at a given index
 * @param index
 * @param value
 * @return bool
 */
bool DronesManager::replace(unsigned int index, DroneRecord value) {
    DroneRecord *current = this->first;
    if (empty()) {
        cout << "Replace rejected: list empty." << endl;
    } else if (index < 0 || index >= this->size) {
        cout << "Replace rejected: index out of bounds." << endl;
        return false;
    } else {
        int i = 0;
        while (i != index) {
            current = current->next;
            i++;
        }
        current->droneID = value.droneID;
        current->yearBought = value.yearBought;
        current->droneType = value.yearBought;
        return true;
    }
}

/**
 * reverses the list in place
 * @return bool
 */
bool DronesManager::reverse_list() {
    DroneRecord *current = first;
    if (empty()) {
        return false;
    } else if (this->size == 1) {
        return true;
    } else {
        while (current != NULL) {
            DroneRecord *tmp = current->next;
            current->next = current->prev;
            current->prev = tmp;
            if (tmp == NULL) {
                last = first;
                first = current;
            }
            current = tmp;
        }
        return true;
    }
}

/**
 * return true if a list is sorted in ascending order
 * @return
 */
bool DronesManagerSorted::is_sorted_asc() const {
    if (empty()) {
        return true;
    } else {
        DroneRecord *current = first;
        while (current->next) {
            if (current->droneID > current->next->droneID) {
                return false;
            }
            current = current->next;
        }
        return true;
    }
}

/**
 * returns true if a list  is sorted in descending order
 * @return
 */
bool DronesManagerSorted::is_sorted_desc() const {
    if (empty()) {
        return true;
    } else {
        DroneRecord *current = first;
        while (current->next) {
            if (current->droneID < current->next->droneID) {
                return false;
            }
            current = current->next;
        }
        return true;
    }
}

/**
 * Inserts a value so that the list remains sorted in ascending order
 * if the list is not sorted in appropriate order, insertion is rejected
 * @param val
 * @return bool
 */
bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    DroneRecord *recordToInsert = new DroneRecord(val);
    if (!is_sorted_asc()) {
        return false;
    } else {
        DroneRecord *current = first;
        if(empty()){
            insert(val,0);
            return true;
        }else{
            int index = 0;
            cout<<recordToInsert->droneID<<current->droneID<<endl;
            while (current != NULL && recordToInsert->droneID > current->droneID) {
                current = current->next;
                index++;
            }
            insert(val, index);
            return true;
        }
    }
}

/**
 * Inserts a value so that the list remains sorted in descending order
 * if the list is not sorted in appropriate order, insertion is rejected
 * @param val
 * @return
 */
bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    DroneRecord *recordToInsert = new DroneRecord();
    recordToInsert->droneID = val.droneID;
    recordToInsert->yearBought = val.yearBought;
    recordToInsert->range = val.range;
    if (!is_sorted_desc()) {
        return false;
    } else {
        int index = 0;
        DroneRecord *current = first;
        while (current != NULL && recordToInsert->droneID < current->droneID) {
            current = current->next;
            index++;
        }
        insert(val, index);
        return true;
    }
}

/**
 * sorts ascending (quicksort)
 */
void DronesManagerSorted::sort_asc() {
    if (empty()) {
        cout << "Sort ascending rejected, list empty" << endl;
        return;
    }
    DroneRecord *h = last;
    _sort_asc(first, h);
}

/**
 * sorts descending (quicksort)
 */
void DronesManagerSorted::sort_desc() {
    if (empty()) {
        cout << "Sort descending rejected, list empty" << endl;
        return;
    }
    DroneRecord *h = last;
    _sort_desc(first, h);
}

/**
 *
 * @param *a
 * @param *b
 * @return  *DroneRecord
 */
DronesManager::DroneRecord *DronesManagerSorted::partition_desc(DroneRecord *a, DroneRecord *b) {
    // set pivot as h element
    int x = b->droneID;
    DroneRecord *i = a->prev;
    for (DroneRecord *j = a; j != b; j = j->next) {
        if (j->droneID >= x) {
            i = (i == NULL) ? a : i->next;
            swap_nodes(i, j);
        }
    }
    i = (i == NULL) ? a : i->next; // Similar to i++
    swap_nodes(i, b);
    return i;
}

/**
 *
 * @param *a
 * @param *b
 * @return *DroneRecord
 */
DronesManager::DroneRecord *DronesManagerSorted::partition_asc(DroneRecord *a, DroneRecord *b) {
    // set pivot as h element
    int x = b->droneID;
    DroneRecord *i = a->prev;
    for (DroneRecord *j = a; j != b; j = j->next) {
        if (j->droneID <= x) {
            i = (i == NULL) ? a : i->next;
            swap_nodes(i, j);
        }
    }
    i = (i == NULL) ? a : i->next; // Similar to i++
    swap_nodes(i, b);
    return i;
}

/**
 * recursive sort descending
 * @param l
 * @param h
 */
void DronesManagerSorted::_sort_desc(DroneRecord *l, DroneRecord *h) {
    if (h != NULL && l != h->next) {
        DroneRecord *p = partition_desc(l, h);
        _sort_desc(l, p->prev);
        _sort_desc(p->next, h);
    }
};

/**
 * recursive sort ascending
 * @param l
 * @param h
 */
void DronesManagerSorted::_sort_asc(DroneRecord *l, DroneRecord *h) {
    if (h != NULL && l != h->next) {
        DroneRecord *p = partition_asc(l, h);
        _sort_asc(l, p->prev);
        _sort_asc(p->next, h);
    }
};

/**
 * utility method to swap all the values in the given nodes
 * @param l
 * @param h
 */
void DronesManagerSorted::swap_nodes(DroneRecord *l, DroneRecord *h) {

    DroneRecord *temp = new DroneRecord();
    temp->droneID = l->droneID;
    temp->yearBought = l->yearBought;
    temp->range = l->range;

    l->droneID = h->droneID;
    l->yearBought = h->yearBought;
    l->range = h->yearBought;

    h->droneID = temp->droneID;
    h->yearBought = temp->yearBought;
    h->range = temp->range;
}

