#include <iostream>
#include <vector>

int maxMoneyLeft() {
    int n, m;
    std::cin >> n >> m;
    std::vector <int> gifts(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> gifts[i];
    }
    int currentmax = m;
    for (int i = 0; i < n; i++) {
        if (currentmax >= gifts[i]) {
            int leftMax = gifts[i] - 1;
            int rightMax = currentmax - gifts[i];
            currentmax = std::max(leftMax, rightMax);
        }
    }
    return currentmax;
}

int main()
{
    std::cout << maxMoneyLeft() << std::endl;
    return 0;
}
