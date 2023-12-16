#include <iostream>
#include <vector>
#include <algorithm>

int maxaMoneyLeft(int credLim, std::vector<int> gifts)
{
    int jump = 0;
    int result = 0;
    int left = 0;
    int right = 0;
    int current = 0;
    while(gifts[left] > credLim) {
        left++;
    }
    right = left + 1;
    current += gifts[right - 1];
    for (; right < gifts.size() - 1 && current < credLim; ++right)
    {
        if(current + gifts[right] < credLim)
        {
           if((gifts[right] - gifts[right - 1]) > jump) {
               jump = (gifts[right] - gifts[right - 1]);
               result = std::max(credLim - current, gifts[right] - 1);
            } 
            current += gifts[right];
        }
    }
    return std::max(result, credLim - current);
}

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