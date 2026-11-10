#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Facility.h"
#include <vector>
#include <list>

class HashTable {
private:
    struct HashNode 
    {
        std::string key; 
        Facility facility;
    };

    std::vector<std::list<HashNode>> table;
    std::vector<Facility> fileOrderFacilities; // holds file order for view all
    size_t capacity;
    size_t totalEntries;
    size_t collisionCount;

    size_t hashFunction(const std::string& key) const;

public:
    explicit HashTable(size_t cap = 101);

    bool insert(const std::string& rawId, const Facility& facility);
    bool search(const std::string& rawId, Facility& outFacility) const;
    void displayAll() const;

    size_t getCapacity() const;
    size_t getEntries() const;
    size_t getCollisions() const;
};

#endif
