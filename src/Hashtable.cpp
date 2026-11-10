#include "HashTable.h"
#include <iostream>
#include <algorithm>
#include <cctype>

//constructor for hash table
HashTable::HashTable(size_t cap) : capacity(cap), totalEntries(0), collisionCount(0) 
{
    table.resize(capacity);
}

//makes the id into postion
size_t HashTable::hashFunction(const std::string& key) const 
{
    unsigned long hashValue = 0;
    for (char c : key) 
    {
        hashValue = (hashValue * 31) + static_cast<unsigned char>(c);
    }
    return hashValue % capacity;
}

bool HashTable::insert(const std::string& rawId, const Facility& facility)
{
    std::string normId = rawId;
    std::transform(normId.begin(), normId.end(), normId.begin(), ::toupper);

    size_t index = hashFunction(normId);

    for (const auto& node : table[index]) 
    {
        if (node.key == normId)
        {
            return false; // Duplicate key
        }
    }

    if (!table[index].empty())
    {
        collisionCount++;
    }

    table[index].push_back({normId, facility});
    fileOrderFacilities.push_back(facility);
    totalEntries++;
    return true;
}

bool HashTable::search(const std::string& rawId, Facility& outFacility) const
{
    std::string normId = rawId;
    std::transform(normId.begin(), normId.end(), normId.begin(), ::toupper);

    size_t index = hashFunction(normId);

    for (const auto& node : table[index])
    {
        if (node.key == normId)
        {
            outFacility = node.facility;
            return true;
        }
    }
    return false;
}

void HashTable::displayAll() const
{
    if (fileOrderFacilities.empty())
    {
        std::cout << "No facilities available." << std::endl;
        return;
    }
    for (const auto& f : fileOrderFacilities) 
    {
        f.display();
    }
    std::cout << "Total facilities: " << fileOrderFacilities.size() << std::endl;
}

size_t HashTable::getCapacity() const 
{
    return capacity; 
}

size_t HashTable::getEntries() const
{
    return totalEntries; 
}

size_t HashTable::getCollisions() const
{
    return collisionCount;
}

