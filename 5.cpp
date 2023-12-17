#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>

class Child
{
public:
    std::vector<Child*> friends;
    int value;
    Child(int val) : value(val) {};

    void sendStickers(int stickers)
    {
        for (Child* child : friends)
        {
            child->value += stickers;
        }
    }
};

int main() {
    std::vector<Child*> children;
    int m, n, q;
    std::cin >> n >> m >> q;
    for (int i = 0; i < n; i++)
    {
        int a;
        std::cin >> a;
        children.push_back(new Child(a));
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        std::cin >> a >> b;
        children[a - 1]->friends.push_back(children[b - 1]);
        children[b - 1]->friends.push_back(children[a - 1]);
    }

    char op;
    int childIndex, stickers;

    for (int i = 0; i < q; i++)
    {
        std::cin >> op;
        switch (op)
        {
        case '+':
            std::cin >> childIndex >> stickers;
            children[childIndex - 1]->sendStickers(stickers);
            break;
        case '?':
            std::cin >> childIndex;
            std::cout << children[childIndex - 1]->value << std::endl;
            break;
        }
    }
    return 0;
}