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

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
//  TA says we only need to compare the ID but I'm skeptical
    return (lhs.droneID == rhs.droneID);
}

unsigned int DronesManager::get_size() const {
    return size;
}

bool DronesManager::empty() const {
    return (first == nullptr && last == nullptr && size == 0);
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    if(index > size || index < 0){
        return size;
    } else if (empty()){
        return 0;
    } else {
        return DroneRecord(index);
    }
}

unsigned int DronesManager::search(DroneRecord value) const {
    for(int i = 0; i < size; i++){
        if (DroneRecord(i) == value) {
            return i;
        } else if (empty()) {
            return 0;
        } else if (i < 0 || i > size){
            return size;
        }
    }
}

void DronesManager::print() const {
    DroneRecord* cur = first;
    for(int i = 0; i < size; i++){
        cout << "Drone ID = " << cur->droneID << endl;
        cout << "Year bought = " << cur->yearBought << endl;
        cout << "Range = " << cur->range << endl;
        cur = cur->next;
    }
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
    return false;
}

bool DronesManager::insert_front(DroneRecord value) {
    return false;
}

bool DronesManager::insert_back(DroneRecord value) {
    return false;
}

bool DronesManager::remove(unsigned int index) {
    return false;
}

bool DronesManager::remove_front() {
    return false;
}

bool DronesManager::remove_back() {
    return false;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    return false;
}

bool DronesManager::reverse_list() {
    return false;
}

bool DronesManagerSorted::is_sorted_asc() const {
    return false;
}

bool DronesManagerSorted::is_sorted_desc() const {
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    return false;
}

void DronesManagerSorted::sort_asc() {
}

void DronesManagerSorted::sort_desc() {
}
