#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Facility.h"
#include "HashTable.h"
#include "CampusGraph.h"
#include "DepartmentTree.h"

void printLoadSummary(const std::string& filename, int accepted, int rejected, const std::string& extra = "") {
    std::cout << filename << ": " << accepted << " accepted, " << rejected << " rejected";
    if (!extra.empty()) {
        std::cout << " " << extra;
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::string dataDir = "data/";
    if (argc > 1) {
        dataDir = argv[1];
        if (dataDir.back() != '/' && dataDir.back() != '\\') {
            dataDir += "/";
        }
    }

    CampusGraph graph;
    HashTable facilityTable(101);
    DepartmentTree deptTree;

    // 1. Load buildings.txt
    int bAccepted = 0, bRejected = 0;
    std::ifstream bFile(dataDir + "buildings.txt");
    if (!bFile.is_open()) {
        std::cout << "Error: Cannot open " << (dataDir + "buildings.txt") << std::endl;
    } else {
        std::string line;
        int lineNum = 0;
        while (std::getline(bFile, line)) {
            lineNum++;
            if (line.empty() || line[0] == '#') continue;
            if (graph.addBuilding(line)) {
                bAccepted++;
            } else {
                bRejected++;
                std::cout << "Warning: buildings.txt line " << lineNum << " rejected." << std::endl;
            }
        }
        bFile.close();
    }
    printLoadSummary("buildings.txt", bAccepted, bRejected);

    // 2. Load connections.txt
    int cAccepted = 0, cRejected = 0;
    std::ifstream cFile(dataDir + "connections.txt");
    if (!cFile.is_open()) {
        std::cout << "Error: Cannot open " << (dataDir + "connections.txt") << std::endl;
    } else {
        std::string line;
        int lineNum = 0;
        while (std::getline(cFile, line)) {
            lineNum++;
            if (line.empty() || line[0] == '#') continue;
            size_t delimiter = line.find('|');
            if (delimiter == std::string::npos) {
                cRejected++;
                continue;
            }
            std::string b1 = line.substr(0, delimiter);
            std::string b2 = line.substr(delimiter + 1);
            if (graph.addConnection(b1, b2)) {
                cAccepted++;
            } else {
                cRejected++;
            }
        }
        cFile.close();
    }
    printLoadSummary("connections.txt", cAccepted, cRejected);

    // 3. Load facilities.txt
    int fAccepted = 0, fRejected = 0;
    std::ifstream fFile(dataDir + "facilities.txt");
    if (!fFile.is_open()) {
        std::cout << "Error: Cannot open " << (dataDir + "facilities.txt") << std::endl;
    } else {
        std::string line;
        int lineNum = 0;
        while (std::getline(fFile, line)) {
            lineNum++;
            if (line.empty() || line[0] == '#') continue;
            std::stringstream ss(line);
            std::string id, name, building, category;
            if (std::getline(ss, id, '|') && std::getline(ss, name, '|') &&
                std::getline(ss, building, '|') && std::getline(ss, category)) {
                
                if (!graph.hasBuilding(building)) {
                    fRejected++;
                    continue;
                }
                Facility fac(id, name, building, category);
                if (facilityTable.insert(id, fac)) {
                    fAccepted++;
                } else {
                    fRejected++;
                }
            } else {
                fRejected++;
            }
        }
        fFile.close();
    }
    std::string extraHashInfo = "(hash capacity " + std::to_string(facilityTable.getCapacity()) + 
                                ", entries " + std::to_string(facilityTable.getEntries()) + 
                                ", collisions " + std::to_string(facilityTable.getCollisions()) + ")";
    printLoadSummary("facilities.txt", fAccepted, fRejected, extraHashInfo);

    // 4. Load departments.txt
    int dAccepted = 0, dRejected = 0;
    std::ifstream dFile(dataDir + "departments.txt");
    if (!dFile.is_open()) {
        std::cout << "Error: Cannot open " << (dataDir + "departments.txt") << std::endl;
    } else {
        std::string line;
        int lineNum = 0;
        while (std::getline(dFile, line)) {
            lineNum++;
            if (line.empty() || line[0] == '#') continue;
            size_t delimiter = line.find('|');
            if (delimiter == std::string::npos) {
                dRejected++;
                continue;
            }
            std::string dept = line.substr(0, delimiter);
            std::string parent = line.substr(delimiter + 1);
            if (deptTree.addDepartment(dept, parent)) {
                dAccepted++;
            } else {
                dRejected++;
            }
        }
        dFile.close();
    }
    printLoadSummary("departments.txt", dAccepted, dRejected);

    // Milestone 1 Interactive Menu
    int choice = -1;
    while (choice != 10) {
        std::cout << "\n=== Milestone 1 Menu ===\n";
        std::cout << "1. View all facilities\n";
        std::cout << "2. Search facility by ID\n";
        std::cout << "3. View campus graph\n";
        std::cout << "4. Display graph counts and degrees\n";
        std::cout << "5. Find reachable buildings (BFS)\n";
        std::cout << "6. Add department\n";
        std::cout << "7. Search department\n";
        std::cout << "8. Display department hierarchy\n";
        std::cout << "9. Run preorder traversal\n";
        std::cout << "10. Exit\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n');

        if (choice == 10) {
            std::cout << "Exiting program. Goodbye!" << std::endl;
            break;
        }

        switch (choice) {
            case 1:
                facilityTable.displayAll();
                break;
            case 2: {
                std::string searchId;
                std::cout << "Enter Facility ID (e.g., F001): ";
                std::getline(std::cin, searchId);
                Facility foundFac;
                if (facilityTable.search(searchId, foundFac)) {
                    std::cout << "Found: ";
                    foundFac.display();
                } else {
                    std::cout << "Facility not found or invalid format for ID: " << searchId << std::endl;
                }
                break;
            }
            case 3:
                graph.displayGraph();
                break;
            case 4:
                graph.displayCountsAndDegrees();
                break;
            case 5: {
                std::string startBldg;
                std::cout << "Enter starting building: ";
                std::getline(std::cin, startBldg);
                graph.bfsReachability(startBldg);
                break;
            }
            case 6: {
                std::string newDept, parentDept;
                if (deptTree.isEmpty()) {
                    std::cout << "Tree is empty. Enter root department name: ";
                    std::getline(std::cin, newDept);
                    parentDept = "NONE";
                } else {
                    std::cout << "Enter new department name: ";
                    std::getline(std::cin, newDept);
                    std::cout << "Enter existing parent department name: ";
                    std::getline(std::cin, parentDept);
                }
                if (deptTree.addDepartment(newDept, parentDept)) {
                    std::cout << "Department added successfully." << std::endl;
                } else {
                    std::cout << "Error: Could not add department (check duplicate names or unknown parent)." << std::endl;
                }
                break;
            }
            case 7: {
                std::string queryDept;
                std::cout << "Enter department name to search: ";
                std::getline(std::cin, queryDept);
                deptTree.searchDepartment(queryDept);
                break;
            }
            case 8:
                deptTree.displayHierarchy();
                break;
            case 9: {
                auto seq = deptTree.getPreorderTraversal();
                std::cout << "Preorder Traversal: ";
                for (const auto& d : seq) {
                    std::cout << d << " ";
                }
                std::cout << std::endl;
                break;
            }
            default:
                std::cout << "Invalid choice. Please select between 1 and 10." << std::endl;
                break;
        }
    }

    return 0;
}
