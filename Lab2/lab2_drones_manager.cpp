#include "lab2_drones_manager.h"

// TODO: Implement all of the listed functions below

// creates new empty DronesManager
DronesManager::DronesManager() {
    first = nullptr;
    last = nullptr;
    size = 0;
}

// Destroys instance and frees up dynamically allocated memory
DronesManager::~DronesManager() {
}

bool operator==(const DronesManager::DroneRecord &lhs, const DronesManager::DroneRecord &rhs) {
//  TA says we only need to compare the ID but I'm skeptical
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
 * @return DroneRecord
 */
DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    if (index > size || index < 0) {
        cout << "Unable to select: Index is outside of bounds" << endl;
    } else if (empty()) {
        DroneRecord(0);
    } else {
        int count = 0;
        DroneRecord *current = first;
        while (count < index && current != nullptr) {
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
    for (int i = 0; i < size; i++) {
        if (DroneRecord(i) == value) {
            return i;
        } else if (empty()) {
            return 0;
        } else if (i < 0 || i > size) {
            return size;
        }
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
    if (empty()) {
        if (index == 0) {
            cout << "got to inserting at index == 0 for empty() instance" << endl;
            DroneRecord *recordToInsert = new DroneRecord();
            recordToInsert->droneID = value.droneID;
            recordToInsert->yearBought = value.yearBought;
            recordToInsert->range = value.range;
            first = recordToInsert;
            last = recordToInsert;
            recordToInsert->prev = nullptr;
            recordToInsert->next = nullptr;
            size++;
            return true;
        } else {
            cout << "Insertion rejected - index out of bounds." << endl;
            return false;
        }
    } else {
        DroneRecord *current = this->first;
        DroneRecord *prev = nullptr;
        DroneRecord *recordToInsert = new DroneRecord();
        // sets the new drone equal to value
        recordToInsert->droneID = value.droneID;
        recordToInsert->yearBought = value.yearBought;
        recordToInsert->range = value.range;
        if (index == 0) {
            cout << "got to inserting at index == 0 for !empty() instance." << endl;
            first = recordToInsert;
            recordToInsert->prev = nullptr;
            recordToInsert->next = current;
            current->prev = first;
            size++;
            return true;
        } else if (index >= size) {
            cout << "Insertion rejected - index out of bounds." << endl;
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
    DroneRecord *recordToInsert = new DroneRecord();
    recordToInsert->droneID = value.droneID;
    recordToInsert->yearBought = value.yearBought;
    recordToInsert->range = value.range;
    if (empty()) {
        first = recordToInsert;
        last = recordToInsert;
        recordToInsert->prev = NULL;
        recordToInsert->next = NULL;
        size++;
        return true;
    } else {
        DroneRecord *temp = first;
        first = recordToInsert;
        recordToInsert->prev = nullptr;
        recordToInsert->next = temp;
        recordToInsert->next->prev = recordToInsert;
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
    if (empty()) {
        first = &value;
        last = &value;
        first->prev = NULL;
        last->next = NULL;
        size++;
        return true;
    } else {
        DroneRecord *current = first;
        while (current->next) {
            current = current->next;
        }
        current->next = &value;
        last = &value;
        last->prev = current;
        last->next = NULL;
        first->prev = NULL;
        size++;
        return current->next == &value ? true : false;
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
    } else if (index == size && size == 1 && first->next == NULL ) {
        first->prev = NULL;
        first = NULL;
        last = NULL;
        size--;
    } else if(index == 0){
        first = first->next;
        delete first->prev;
        first->prev = NULL;
        size--;
        return true;
    }
    else {
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

// TODO Mary
/**
 * replaces the node at a given index
 * @param index
 * @param value
 * @return bool
 */
bool DronesManager::replace(unsigned int index, DroneRecord value) {
    return false;
}

// TODO Mary
/**
 * reverses the list in place
 * @return bool
 */
bool DronesManager::reverse_list() {
    return false;
}

/**
 * return true if a list is sorted in ascending order
 * @return
 */
bool DronesManagerSorted::is_sorted_asc() const {
    DroneRecord *current = first;
    while (current->next) {
        if (current > current->next) {
            return false;
        }
        current = current->next;
    }
    return true;
}

// TODO Mary
/**
 * returns true if a list  is sorted in descending order
 * @return
 */
bool DronesManagerSorted::is_sorted_desc() const {
    DroneRecord *cur;
    for (int i = 0; i > size; i++) {
        if (cur->droneID < cur->next->droneID) {
            return false;
        }
        cur = cur->next;
    }
    return true;
}

/**
 * Inserts a value so that the list remains sorted in ascending order
 * if the list is not sorted in appropriate order, insertion is rejected
 * @param val
 * @return bool
 */
bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    DroneRecord *recordToInsert = new DroneRecord();
    recordToInsert->droneID = val.droneID;
    recordToInsert->yearBought = val.yearBought;
    recordToInsert->range = val.range;
    if(!is_sorted_asc()){
        return false;
    } else {
        int index = 0;
        DroneRecord *current = first;
        while(recordToInsert->droneID > current->droneID){
            current = current->next;
            index++;
        }
        insert(val,index);
        return true;
    }
}

// TODO Mary
bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    return false;
}

// TODO Mary
void DronesManagerSorted::sort_asc() {
}

// TODO Sammy
void DronesManagerSorted::sort_desc() {

}
// TODO Sammy

DronesManager::DroneRecord* DronesManagerSorted::partition(DroneRecord *a,DroneRecord*b){
    // set pivot as h element
    int x = b->droneID;

    // similar to i = l-1 for array implementation
    DroneRecord *i = a->prev;

    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (DroneRecord *j = a; j != b; j = j->next)
    {
        if (j->droneID <= x)
        {
            // Similar to i++ for array
            i = (i == NULL)? a : i->next;

            swap_nodes((i), (j));
        }
    }
    i = (i == NULL)? a : i->next; // Similar to i++
    swap_nodes(i, b);
    return i;
}
// TODO Sammy
void DronesManagerSorted::_sort_desc(DroneRecord *l,DroneRecord *h){

};

void DronesManagerSorted::swap_nodes(DroneRecord *l,DroneRecord *h){

}