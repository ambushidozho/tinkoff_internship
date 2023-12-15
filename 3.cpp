#include <iostream>
#include <vector>
#include <algorithm>

int maxMoneyLeft(int credLim, std::vector<int> gifts)
{
    std::vector<int> resultarr;
    for(int i = 0; i < credLim; i++)
    {
        int credit = i;
        for (auto gift : gifts)
        {
            if(credit >= gift) 
            {
                credit -= gift; 
            }
        }
        resultarr.push_back(credit);
    }
    return *std::max_element(resultarr.begin(), resultarr.end());
}

int main()
{
    std::vector<int> gifts;
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        gifts.push_back(x);
    } 
    std::cout << maxMoneyLeft(m, gifts) << std::endl;
    return 0;
}