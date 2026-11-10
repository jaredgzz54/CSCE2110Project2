#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>
#include <map>

class CampusGraph {
private:
    struct BuildingNode {
        std::string name;
        std::vector<std::string> neighbors; 
    };

    std::vector<BuildingNode> buildings;
    std::map<std::string, size_t> nameToIndex;

    std::string normalizeName(const std::string& name) const;

public:
    CampusGraph();

    bool addBuilding(const std::string& name);
    bool addConnection(const std::string& b1, const std::string& b2);
    bool hasBuilding(const std::string& name) const;

    size_t getBuildingCount() const;
    size_t getConnectionCount() const;

    void displayGraph() const;
    void displayCountsAndDegrees() const;
    void bfsReachability(const std::string& startName) const;
};

#endif
