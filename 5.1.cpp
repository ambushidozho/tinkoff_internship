#include <vector>
#include <iostream>

const int N = 1e5 + 10;
int sqrtN = 300;

class Child
{
public:
    std::vector<Child*> heavyfriends;
    std::vector<Child*> lightfriends;
    std::vector<Child*> friends;
    int storage;
    int value;
    int degree;
    Child(int val) : value(val) {};
};

void run() {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<Child*> children(n);

    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        children[i] = new Child(a);
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        children[u]->friends.push_back(children[v]);
        children[v]->friends.push_back(children[u]);
        children[u]->degree++;
        children[v]->degree++;
    }

    for (int v = 0; v < n; ++v) {
        for (auto child : children[v]->friends) {
            if (child->degree > sqrtN) {
                children[v]->heavyfriends.push_back(child);
            }
            else {
                children[v]->lightfriends.push_back(child);
            }
        }
    }

    while (q--) {
        char op;
        int v;
        std::cin >> op >> v;
        v--;
        if (op == '+') {
            int value;
            std::cin >> value;
            for (auto child : children[v]->heavyfriends) {
                child->value += value;
            }
            if (children[v]->degree > sqrtN) {
                children[v]->storage += value;
            }
            else {
                for (auto child : children[v]->lightfriends) {
                    child->value += value;
                }
            }
        }
        else {
            if (children[v]->degree > sqrtN) {
                int sum = children[v]->value;
                std::cout << sum << std::endl;
            }
            else {
                int sum = children[v]->value;
                for (auto child : children[v]->friends) {
                    sum += child->storage;
                }
                std::cout << sum << std::endl;
            }
        }
    }

}

int main() {
    run();
}