#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>

int main() {
    int t;
    bool result = true;
    std::vector<int> workers;
    std::unordered_map<int, int> graph;
    std::cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n;
        int a;
        std::cin >> n;
        for (int j = 0; j < n; j++)
        {
            std::cin >> a;
            workers.push_back(a);
        }

        std::sort(workers.rbegin(), workers.rend());

        for (int j = 0; j < workers.size(); j++)
        {
            if (j == 0) {
                graph[j] = workers[j];
                continue;
            }
            if (workers[j] == 0 || graph.empty()) {
                result = false;
                break;
            }
            int key;
            for (auto &node : graph)
            {
                key = node.first;
                graph[key]--;
                break;
            }
            if (workers[j] - 1 != 0)
            {
                graph[j] = --workers[j];
            }
            if (graph[key] == 0) {
                graph.erase(key);
            }
        }
        graph.clear();
        workers.clear();
        result ? std::cout << "YES" << std::endl : std::cout << "NO" << std::endl;
        result = true;
    }
    return 0;
}


