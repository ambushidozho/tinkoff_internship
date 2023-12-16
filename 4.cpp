#include <iostream>
#include <vector>
#include <limits>
#include <unordered_set>
#include <stack>
#include <queue>

class Cluster;

class Node {
public:
    int value = 0;
    std::string company;
    std::vector<Node*> children;
    Node* parent = nullptr;
    Cluster* cluster = nullptr;
    Node(Node* par, int val, const std::string& comp) : parent(par), value(val), company(comp) {}
};

class Cluster {
public:
    std::vector<Node*> nodes;
    std::unordered_set<std::string> companies;
    int value = 0;
    int parentValue = 0;
    Cluster() = default;
};

class Tree {
public:
    Node* root;

    Tree() {
        root = nullptr;
    }

    ~Tree() {
        delete root;
    }

    void addChild(Node* parent, int childValue, const std::string& childCompany) {
        Node* child = new Node(parent, childValue, childCompany);
        parent->children.push_back(child);
    }

    void addRoot(Node* node) {
        root = node;
    }

};

bool isEqual(std::unordered_set<std::string> required, std::unordered_set<std::string> recieved) {
    for (auto company : required) {
        if (recieved.find(company) == recieved.end()) {
            return false;
        }
    }
    return true;
}

void mergeClusters(Cluster* parent, Cluster* child) {
    parent->value += child->value;
    parent->companies.insert(child->companies.begin(), child->companies.end());
}

int main() {
    int n, k;
    int counter = 0;
    std::stack<Cluster*> clusters;
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
        int parent;
        int val;
        std::string comp;
        std::cin >> parent >> val >> comp;
       
        if (i == 0) {
            tree.addRoot(new Node(nullptr, val, comp));
            nodes.push_back(tree.root);
        }
        else {
            Node* node = new Node(nodes[parent - 1], val, comp);
            nodes[parent - 1]->children.push_back(node);
            nodes.push_back(node);
        }
    }

    std::queue<Node*> queue;
    queue.push(tree.root);
    queue.push(nullptr);
    auto cluster = new Cluster();
    cluster->nodes.push_back(tree.root);
    tree.root->cluster = cluster;
    clusters.push(cluster);
    while (!queue.empty())
    {
        Node* node = queue.front();
        queue.pop();
        if (node == nullptr) {
            if (!queue.empty()) {
                queue.push(nullptr);
            }
            continue;
        }
        auto cluster = new Cluster();
        for (auto child : node->children)
        {
            child->cluster = cluster;
            cluster->nodes.push_back(child);
            queue.push(child);
        }
        if (cluster->nodes.size() > 0) {
            clusters.push(cluster);
        }
    }

    int minCost = std::numeric_limits<int>::max();

    while (!clusters.empty())
    {
        auto cluster = clusters.top();
        clusters.pop();
        for (auto node : cluster->nodes)
        {
            if (companies.size() == 1 && companies.count(node->company) && node->children.empty()) {
                minCost = std::min(minCost, node->value);
            }
            cluster->companies.insert(node->company);
            cluster->value += node->value;
        }
        if (cluster->nodes[0]->parent != nullptr) {
            cluster->companies.insert(cluster->nodes[0]->parent->company);
            if (isEqual(companies, cluster->companies)) {
                minCost = std::min(minCost, cluster->value + cluster->nodes[0]->parent->value);
            }
            mergeClusters(cluster->nodes[0]->parent->cluster, cluster);
        }
        else {
            if (isEqual(companies, cluster->companies)) {
                minCost = std::min(minCost, cluster->value);
            }
        }
    }

    if (minCost == std::numeric_limits<int>::max()) {
        std::cout << -1 << std::endl;
    }
    else {
        std::cout << minCost << std::endl;
    }
    
    return 0;
}