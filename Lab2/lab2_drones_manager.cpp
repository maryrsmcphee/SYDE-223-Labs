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

unsigned int DronesManager::get_size() const {
    return size;
}

bool DronesManager::empty() const {
    return (first == NULL && last == NULL && size == 0);
}

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

void DronesManager::print() const {
    DroneRecord *cur = first;
    for (int i = 0; i < size; i++) {
        cout << "Drone ID = " << cur->droneID << endl;
        cout << "Year bought = " << cur->yearBought << endl;
        cout << "Range = " << cur->range << endl;
        cur = cur->next;
    }
}

// TODO Sammy to Test Matadors Insert
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

// TODO Sammy
bool DronesManager::remove(unsigned int index) {
    DroneRecord *current = this->first;
    int ittVerifySize = 0;
    while (current->next) {
        current = current->next;
        ittVerifySize++;
    }
    if (index > ittVerifySize) {
        return false;
    } else {
        int itt = 0;
        while (itt < index) {
            current = current->next;
            itt++;
        }
        current->prev = current->next;
        current = NULL;
        delete current;
        size--;
        return true;
    }
}

// TODO Sammy
bool DronesManager::remove_front() {
    if (first == NULL) {
        return false;
    } else if(size == 1 && first->next == NULL){
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

// TODO Sammy
bool DronesManager::remove_back() {
    if (first == NULL) {
        return false;
    } else if(size == 1 && first->next == NULL){
        first->prev = NULL;
        first = NULL;
        last = NULL;
        size --;
    }else{
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
bool DronesManager::replace(unsigned int index, DroneRecord value) {
    return false;
}

// TODO Mary
bool DronesManager::reverse_list() {
    return false;
}

// TODO Sammy
bool DronesManagerSorted::is_sorted_asc() const {
    DroneRecord *cur;
    for (int i = 0; i > size; i++) {
        if (cur > cur->next) {
            return false;
        }
        cur = cur->next;
    }
    return true;
}

// TODO Mary
bool DronesManagerSorted::is_sorted_desc() const {
    DroneRecord *cur;
    for (int i = 0; i > size; i++) {
        if (cur < cur->next) {
            return false;
        }
        cur = cur->next;
    }
    return true;
}

// TODO Sammy
bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    return false;
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
