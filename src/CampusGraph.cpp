#include "CampusGraph.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <cctype>
#php

CampusGraph::CampusGraph() {}

std::string CampusGraph::normalizeName(const std::string& name) const {
    std::string result = name;
    size_t first = result.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = result.find_last_not_of(" \t\r\n");
    return result.substr(first, (last - first + 1));
}

bool CampusGraph::addBuilding(const std::string& name) {
    std::string norm = normalizeName(name);
    if (norm.empty()) return false;
    std::string lower = norm;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (nameToIndex.find(lower) != nameToIndex.end()) return false;

    nameToIndex[lower] = buildings.size();
    buildings.push_back({norm, {}});
    return true;
}

bool CampusGraph::addConnection(const std::string& b1, const std::string& b2) {
    std::string l1 = normalizeName(b1);
    std::string l2 = normalizeName(b2);
    std::transform(l1.begin(), l1.end(), l1.begin(), ::tolower);
    std::transform(l2.begin(), l2.end(), l2.begin(), ::tolower);

    if (l1 == l2) return false;
    if (nameToIndex.find(l1) == nameToIndex.end() || nameToIndex.find(l2) == nameToIndex.end()) return false;

    size_t idx1 = nameToIndex[l1];
    size_t idx2 = nameToIndex[l2];

    auto& neighbors1 = buildings[idx1].neighbors;
    std::string targetName2 = buildings[idx2].name;
    if (std::find(neighbors1.begin(), neighbors1.end(), targetName2) != neighbors1.end()) return false;

    buildings[idx1].neighbors.push_back(targetName2);
    buildings[idx2].neighbors.push_back(buildings[idx1].name);
    return true;
}

bool CampusGraph::hasBuilding(const std::string& name) const {
    std::string lower = normalizeName(name);
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return nameToIndex.find(lower) != nameToIndex.end();
}

size_t CampusGraph::getBuildingCount() const { return buildings.size(); }

size_t CampusGraph::getConnectionCount() const {
    size_t total = 0;
    for (const auto& b : buildings) {
        total += b.neighbors.size();
    }
    return total / 2;
}

void CampusGraph::displayGraph() const {
    if (buildings.empty()) {
        std::cout << "No buildings loaded." << std::endl;
        return;
    }
    for (const auto& b : buildings) {
        std::cout << b.name << ": ";
        if (b.neighbors.empty()) {
            std::cout << "(no connections)";
        } else {
            for (size_t i = 0; i < b.neighbors.size(); ++i) {
                std::cout << b.neighbors[i] << (i + 1 < b.neighbors.size() ? ", " : "");
            }
        }
        std::cout << std::endl;
    }
}

void CampusGraph::displayCountsAndDegrees() const {
    std::cout << "Total buildings: " << getBuildingCount() << std::endl;
    std::cout << "Total connections: " << getConnectionCount() << std::endl;
    for (const auto& b : buildings) {
        std::cout << b.name << " degree: " << b.neighbors.size() << std::endl;
    }
}

void CampusGraph::bfsReachability(const std::string& startName) const {
    std::string norm = normalizeName(startName);
    std::string lower = norm;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (nameToIndex.find(lower) == nameToIndex.end()) {
        std::cout << "Error: Unknown building '" << startName << "'." << std::endl;
        return;
    }

    std::map<std::string, int> distances;
    std::queue<std::string> q;

    std::string startCanonical = buildings[nameToIndex.at(lower)].name;
    q.push(startCanonical);
    distances[startCanonical] = 0;

    std::vector<std::string> visitOrder;
    visitOrder.push_back(startCanonical);

    while (!q.empty()) {
        std::string curr = q.front();
        q.pop();

        std::string currLower = curr;
        std::transform(currLower.begin(), currLower.end(), currLower.begin(), ::tolower);
        size_t idx = nameToIndex.at(currLower);

        for (const auto& neighbor : buildings[idx].neighbors) {
            if (distances.find(neighbor) == distances.end()) {
                distances[neighbor] = distances[curr] + 1;
                q.push(neighbor);
                visitOrder.push_back(neighbor);
            }
        }
    }

    std::cout << "Reachable buildings from " << startCanonical << ":" << std::endl;
    for (const auto& b : visitOrder) {
        std::cout << b << " (distance " << distances[b] << ")" << std::endl;
    }
    std::cout << "Reachable: " << visitOrder.size() << " of " << buildings.size() << " buildings" << std::endl;
}
