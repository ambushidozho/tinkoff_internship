#include <iostream>
#include <vector>
#include <limits>
#include <unordered_set>

class Node {
public:
    int value;
    std::string company;
    std::vector<Node*> children;
    bool hasAllComponies;
    Node(int val, const std::string& comp) : value(val), company(comp) {}
};

int minCost = std::numeric_limits<int>::max();

class Tree {
public:
    Node* root;

    Tree() {
        root = nullptr;
    }

    Tree(int rootValue, const std::string& rootCompany) {
        root = new Node(rootValue, rootCompany);
    }

    ~Tree() {
        delete root;
    }

    void addChild(Node* parent, int childValue, const std::string& childCompany) {
        Node* child = new Node(childValue, childCompany);
        parent->children.push_back(child);
    }

    void addRoot(Node* node) {
        root = node;
    }
};

bool hasCompany(const Node* node, std::string targetCompany) {
    if (node->company == targetCompany) {
        return true;
    }

    for (Node* child : node->children) {
        if (hasCompany(child, targetCompany)) {
            return true;
        }
    }

    return false;
}

int dfs(Node* node, const std::unordered_set<std::string>& targetCompanies) {
    int currentCost = 0;

    for (Node* child : node->children) {
        currentCost += dfs(child, targetCompanies);
    }

    if (hasCompany(node, node->company)) {
        currentCost += node->value;
    }

    minCost = std::min(minCost, currentCost);

    return currentCost;
}


int main() {
    int n, k;
    std::unordered_set<std::string> companies;
    std::vector<Node*> nodes;
    std::cin >> n >> k;
    Tree tree;
    for (int i = 0; i < k; i++) {
        std::string x;
        std::cin >> x;
        companies.insert(x);
    }

    for (int i = 0; i < n; i++)
    {
        int val;
        int parent;
        std::string comp;
        std::cin >> parent >> val >> comp;
        Node* node = new Node(val, comp);
        i == 0 ? tree.addRoot(node) : nodes[parent - 1]->children.push_back(node);
        nodes.push_back(node);
    }

    dfs(tree.root, companies);
    std::cout << minCost;
    return 0;
}