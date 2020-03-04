#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int min_coin(vector<int> coins, int amount)
{
    vector<int> dp(amount + 1, amount + 1);
    
    dp[0] = 0;

    for (int i = 0; i < dp.size(); i++)
    {
        for (int coin : coins)
        {
            if (i - coin < 0) continue;
            dp[i] = min(dp[i], 1 + dp[i - coin]);
        }
    }
    
    return (dp[amount] == amount + 1) ? -1 : dp[amount];
}

int main()
{
    vector<int> coins_test1 = {1,2,5};
    std::cout << min_coin(coins_test1, 14) << std::endl;
}

