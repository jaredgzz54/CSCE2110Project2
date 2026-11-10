#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include <vector>

using namespace std;

// Department Tree Class
class DepartmentTree {
private:

    // Struct Base For Tree
    struct Node {
        string name;
        vector<Node*> children;
        Node* parent;

        Node( string n, Node* p = nullptr) : name(n), parent(p) {}
    };

    Node* root;

    void clearTree(Node* node);
    Node* findNode(Node* current, const string& name) const;
    void preorderHelper(Node* current, vector<string>& result) const;
    void displayIndented(Node* current, int depth) const;

public:
    // Destructor/creator
    DepartmentTree();
    ~DepartmentTree();

    // Supporting functions
    bool isEmpty() const;
    bool addDepartment(const string& name, const string& parentName);
    bool searchDepartment(const string& name) const;
    void displayHierarchy() const;

     vector<string> getPreorderTraversal() const;
};

#endif
