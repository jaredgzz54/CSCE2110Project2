#include "DepartmentTree.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

DepartmentTree::DepartmentTree() : root(nullptr) {}

DepartmentTree::~DepartmentTree() {
    clearTree(root);
}

// Deletes children and the parent node. Deletes Children first ofc
void DepartmentTree::clearTree(Node* node) {
    if (!node) return;
    for (Node* child : node->children) {
        clearTree(child);
    }
    delete node;
}

// Helper function to check if the main tree is empty
bool DepartmentTree::isEmpty() const { return root == nullptr; }

// Cuts off unneccesary spaces from strings we want to check. (Makes it easier to work with)
string normalizeStr(const string& str) {
    // Cuts off beginning spaces
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";

    // Cuts off ending spaces
    size_t last = str.find_last_not_of(" \t\r\n");
    
    return str.substr(first, (last - first + 1));
}

// Finds node in the tree from the node specified. (Basically checks children nodes from the node its given for the given string)
DepartmentTree::Node* DepartmentTree::findNode(Node* current, const string& name) const {
    if (!current) return nullptr;
    string currNorm = current->name;
    string targetNorm = name;

    // Lowercases all strings to check
    transform(currNorm.begin(), currNorm.end(), currNorm.begin(), ::tolower);
    transform(targetNorm.begin(), targetNorm.end(), targetNorm.begin(), ::tolower);

    if (currNorm == targetNorm) return current;

    // Starts to check for children nodes
    for (Node* child : current->children) {
        Node* found = findNode(child, name);
        if (found) return found;
    }
    return nullptr;
}

// Adds department to tree
bool DepartmentTree::addDepartment(const string& name, const string& parentName) {
    string normName = normalizeStr(name);
    if (normName.empty()) return false;
    if (findNode(root, normName)) return false; // Duplicate check

    if (!root) {
        root = new Node(normName, nullptr);
        return true;
    }

    string normParent = normalizeStr(parentName);
    Node* parentNode = findNode(root, normParent);
    if (!parentNode) return false;

    Node* newNode = new Node(normName, parentNode);
    parentNode->children.push_back(newNode);
    return true;
}

// 
bool DepartmentTree::searchDepartment(const string& name) const {
    Node* node = findNode(root, name);
    if (!node) {
        cout << "Department not found: " << name << endl;
        return false;
    }

    // Calculate depth
    int depth = 0;
    Node* curr = node;
    while (curr->parent) {
        depth++;
        curr = curr->parent;
    }

    cout << "Found Department: " << node->name << endl;
    cout << "Parent: " << (node->parent ? node->parent->name : "None") << endl;
    cout << "Direct Children Count: " << node->children.size() << endl;
    cout << "Depth: " << depth << endl;
    return true;
}

void DepartmentTree::displayIndented(Node* current, int depth) const {
    if (!current) return;
    for (int i = 0; i < depth; ++i) cout << "    ";
    cout << current->name << endl;
    for (Node* child : current->children) {
        displayIndented(child, depth + 1);
    }
}

// Displays hierarchy of the tree. Rejects if root is NULL
void DepartmentTree::displayHierarchy() const {
    if (!root) {
        cout << "No departments loaded." << endl;
        return;
    }
    displayIndented(root, 0);
}

// Helper for preorder traversal
void DepartmentTree::preorderHelper(Node* current, vector<string>& result) const {
    if (!current) return;
    result.push_back(current->name);
    for (Node* child : current->children) {
        preorderHelper(child, result);
    }
}

// Runs search algorithum via preorder
vector<string> DepartmentTree::getPreorderTraversal() const {
    vector<string> result;
    preorderHelper(root, result);
    return result;
}
