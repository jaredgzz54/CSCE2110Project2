#include "DepartmentTree.h"
#include <iostream>
#include <algorithm>
#include <cctype>

DepartmentTree::DepartmentTree() : root(nullptr) {}

DepartmentTree::~DepartmentTree() {
    clearTree(root);
}

void DepartmentTree::clearTree(Node* node) {
    if (!node) return;
    for (Node* child : node->children) {
        clearTree(child);
    }
    delete node;
}

bool DepartmentTree::isEmpty() const { return root == nullptr; }

std::string normalizeStr(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

DepartmentTree::Node* DepartmentTree::findNode(Node* current, const std::string& name) const {
    if (!current) return nullptr;
    std::string currNorm = current->name;
    std::string targetNorm = name;
    std::transform(currNorm.begin(), currNorm.end(), currNorm.begin(), ::tolower);
    std::transform(targetNorm.begin(), targetNorm.end(), targetNorm.begin(), ::tolower);

    if (currNorm == targetNorm) return current;

    for (Node* child : current->children) {
        Node* found = findNode(child, name);
        if (found) return found;
    }
    return nullptr;
}

bool DepartmentTree::addDepartment(const std::string& name, const std::string& parentName) {
    std::string normName = normalizeStr(name);
    if (normName.empty()) return false;
    if (findNode(root, normName)) return false; // Duplicate check

    if (!root) {
        root = new Node(normName, nullptr);
        return true;
    }

    std::string normParent = normalizeStr(parentName);
    Node* parentNode = findNode(root, normParent);
    if (!parentNode) return false;

    Node* newNode = new Node(normName, parentNode);
    parentNode->children.push_back(newNode);
    return true;
}

bool DepartmentTree::searchDepartment(const std::string& name) const {
    Node* node = findNode(root, name);
    if (!node) {
        std::cout << "Department not found: " << name << std::endl;
        return false;
    }

    // Calculate depth
    int depth = 0;
    Node* curr = node;
    while (curr->parent) {
        depth++;
        curr = curr->parent;
    }

    std::cout << "Found Department: " << node->name << std::endl;
    std::cout << "Parent: " << (node->parent ? node->parent->name : "None") << std::endl;
    std::cout << "Direct Children Count: " << node->children.size() << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    return true;
}

void DepartmentTree::displayIndented(Node* current, int depth) const {
    if (!current) return;
    for (int i = 0; i < depth; ++i) std::cout << "    ";
    std::cout << current->name << std::endl;
    for (Node* child : current->children) {
        displayIndented(child, depth + 1);
    }
}

void DepartmentTree::displayHierarchy() const {
    if (!root) {
        std::cout << "No departments loaded." << std::endl;
        return;
    }
    displayIndented(root, 0);
}

void DepartmentTree::preorderHelper(Node* current, std::vector<std::string>& result) const {
    if (!current) return;
    result.push_back(current->name);
    for (Node* child : current->children) {
        preorderHelper(child, result);
    }
}

std::vector<std::string> DepartmentTree::getPreorderTraversal() const {
    std::vector<std::string> result;
    preorderHelper(root, result);
    return result;
}
