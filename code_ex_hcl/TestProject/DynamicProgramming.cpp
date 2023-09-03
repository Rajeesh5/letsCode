#include<iostream>
#include<vector>
#include<map>
#define MAX(a, b) ((a) > (b) ? (a) : (b))


using namespace std;

class Item {
public:
	int price;
	int weigth;
	
};

int max(int a, int b) { return (a > b) ? a : b; }

class DynamicProg {
public:

	static int CoinMimChange_Recursive(vector<int>& coins, int totalMoney) {

		if (totalMoney == 0) return 0;
		int gMin = INT_MAX;
		for (auto coin : coins) {
			if (coin <= totalMoney) {
				int minCoin = CoinMimChange_Recursive(coins, totalMoney - coin) + 1;
				if (minCoin < gMin) {
					gMin = minCoin;
				}
				gMin = minCoin;
			}
		}
		return gMin;
	}
	
	
	// Returns the count of ways we can sum coins[0...n-1] coins to get sum "sum"
	static int CoinChangecount(vector<int>& coins, int n, int sum)	{

		// If sum is 0 then there is 1 solution (do not include any coin)
		if (sum == 0)	return 1;

		// If sum is less than 0 then no solution exists
		if (sum < 0)    return 0;

		// If there are no coins and sum is greater than 0, then no
		// solution exist
		if (n <= 0)  	return 0;

		// count is sum of solutions 
		// (i) excluding coins[n-1] (ii)  including coins[n-1]
		return CoinChangecount(coins, n - 1, sum)
			+  CoinChangecount(coins, n + 0, sum - coins[n - 1]);    
		
		   // why (n+0), because having un-limilted supply of coin
		   // this the diffrence between power problem, because there 
		   // element is fix (only one)
	}



	static int makeChange(vector<int>& coins, int totalMoney, vector<int>& cache) {

		if (cache.at(totalMoney) >= 0) {
			return cache.at(totalMoney);
		}
		int gMin = INT_MAX;
		for (auto coin : coins) {
			if (coin <= totalMoney) {
				int minCoin = makeChange(coins, totalMoney - coin, cache) + 1;
				if (minCoin < gMin) {
					gMin = minCoin;
				}
			}
		}
		// update the cache table.
		cache[totalMoney] = gMin;
		return cache[totalMoney];

	}

	static int CoinMakeChange_Recursive_withCache(vector<int>& coins, int totalMoney) {
		vector<int> cache;
		// Initialize the cache.
		for (int i = 0; i <= totalMoney; i++) {
			if (i == 0) {
				cache.push_back(0);		//Base Condition.
			}
			else {
				cache.push_back(-1);
			}
		}
		return makeChange(coins, totalMoney, cache);	
	}

	static int CoinMakeChange_DP(vector<int>& coins, int c) {
		
		int *cache = new int[c + 1];
		cache[0] = 0;

		for (int i = 1; i <= c; i++) {
			int minCoin = INT_MAX;

			for (auto coin : coins) {
				if (i - coin >= 0) {
					int currCoin = cache[i - coin] + 1;
					if (currCoin < minCoin) {
						minCoin = currCoin;
					}
				}
			}
			cache[i] = minCoin;
		}
		return cache[c];
	}

	static int RodCut_Recusive(vector<int>& rodSize, vector<int>& price, int len, int size) {
		int maxPrice = INT_MIN;

		if (len == 0) {
			return 0;
		}		

		for (int i = 0; i < size && len >= rodSize[i] ; i++) {			
			int currentPrice = RodCut_Recusive(rodSize, price, len - rodSize[i], size) + price[i];
			if (currentPrice > maxPrice) {
				maxPrice = currentPrice;
			}			
		}
		return maxPrice;
	}

	static int RodCut(vector<int>& rodSize, vector<int>& price, int len, int size, vector<int> &cache) {
		int maxPrice = INT_MIN;

		if (cache[len] >= 0) {
			return cache[len];
		}

		for (int i = 0; i < size && len >= rodSize[i]; i++) {

			int currentPrice = RodCut_Recusive(rodSize, price, len - rodSize[i], size) + price[i];
			if (currentPrice > maxPrice) {
				maxPrice = currentPrice;
			}
		}
		cache[len] = maxPrice;
		return cache[len];
	}
	
	static int RodCut_Recusive_withCache(vector<int>& rodSize, vector<int>& price, int len, int size) {

		vector<int> cache;
		// Initialize the cache.
		for (int i = 0; i <= len; i++) {
			if (i == 0) {
				cache.push_back(0);		//Base Condition.
			}
			else {
				cache.push_back(-1);
			}
		}

		return RodCut(rodSize, price, len, size, cache);
	}

	static int knapsack01_recursive(vector<Item>& Items, int totalWeight, int size) {

		if (size == -1 || totalWeight == 0) {		// Means Iterate thru all Item 
			return 0;
		}

		// If weight of the nth item is more than Knapsack capacity W, then
		// this item cannot be included in the optimal solution
		else if (totalWeight < Items[size].weigth) {
			return knapsack01_recursive(Items, totalWeight, size-1);
		}

		else {
			return max(
				knapsack01_recursive(Items, totalWeight - Items[size].weigth, size - 1) 
				+ Items[size].price ,								// Include Item.
				knapsack01_recursive(Items, totalWeight, size - 1)	// Exclude Item.;
				);	
		}
	}

	static int knapsack01_DP(vector<Item>& Items, int W, int n) {

		// table[n][w] ~ table[0..3][0..50]
		// where n=3, w=50 

		std::vector<std::vector<int>> table(n+1, vector<int>(W+1));     

		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= W; j++)
			{
							   				 			  			  
				if (i == 0 || j == 0)
					table[i][j] = 0;
				else if (Items[i - 1].weigth <= j) {
					table[i][j] = max(Items[i - 1].price +	table[i - 1][j - Items[i - 1].weigth],
						    			table[i - 1][j]);
				} else
					table[i][j] = table[i - 1][j];
			}
		}
		return table[n][W];
	}

	static int knapsack01_DP_optimised(vector<Item>& Items, const int W, int n)
	{
		// making and initializing dp array
		int *dp = new int[W + 1];
		memset(dp, 0, sizeof(dp));

		for (int i = 1; i < n + 1; i++) {
			for (int w = W; w >= 0; w--) {

				if (Items[i - 1].weigth <= w)
					// finding the maximum value
					dp[w] = max(dp[w],
						dp[w - Items[i - 1].weigth] + Items[i - 1].price);
			}
		}
		return dp[W]; // returning the maximum value of knapsack
	}

	static int Longest_increasing_seq(vector<int> arr) {

		int *LIS = new int[arr.size()];

		LIS[0] = 1;
		int n = arr.size();
		for (int i = 1; i < n; i++) {
			LIS[i] = 1;			
			for (int j = 0; j < i; j++) {
				if (arr[i] > arr[j] && LIS[i] < LIS[j] + 1)
					LIS[i] = LIS[j] + 1;
				}
			}
		for (int i = 0; i < n; i++) {
			cout << LIS[i] << " ";
		}

		return 0;

	}

	static int maxSum_increasing_seq(vector<int> arr)
	{
		int i, j, max = 0;
		vector<int> msis;
		int n = arr.size();

		msis.assign(arr.begin(), arr.end());

		/* Compute maximum sum values in bottom up manner */
		for (i = 1; i < n; i++) {
			for (j = 0; j < i; j++) {
				int sum = msis[j] + arr[i];
				if (arr[i] > arr[j] && msis[i] < sum)
					msis[i] = sum;
			}
		}
			/* Pick maximum of	all msis values */
		for (i = 0; i < n; i++)
			if (max < msis[i])
				max = msis[i];

		return max;
	}

};


int main() {

	vector<int> coins		= { 10, 6, 1 };
	vector<int> coins1      = { 2, 5, 3, 6 };
	vector<int> rodSize		= { 1,2,3,4,5,6,7,8 };
	vector<int> price		= { 1,5,8,9,10,17,17,20 };
	vector<Item> Items		= { {60,10},{100,20},{120,30} };
	std::map<Item, int> cache;

	//cout << DynamicProg::CoinMimChange_Recursive(coins, 12) << endl;
	
	cout << DynamicProg::CoinChangecount(coins1, coins1.size(), 10) << endl;
	
	//cout << DynamicProg::CoinMakeChange_Recursive_withCache(coins, 5) << endl;
	//cout << DynamicProg::CoinMakeChange_DP(coins, 16);
	//
	//cout << DynamicProg::RodCut_Recusive(rodSize, price, 5, rodSize.size() - 1);
	//cout << DynamicProg::RodCut_Recusive(rodSize, price, 4, rodSize.size() - 1);
	//
	//cout << DynamicProg::knapsack01_recursive(Items, 50, Items.size()-1);
	//
	//cout << DynamicProg::knapsack01_DP(Items, 50 , Items.size());
	//
	//cout << DynamicProg::knapsack01_DP_optimised(Items, 50, Items.size());	
	//cout << DynamicProg::Longest_increasing_seq({ 10, 22, 9, 33, 21, 50, 41, 60, 80 });	
	//cout << DynamicProg::maxSum_increasing_seq({ 1, 101, 2, 3, 100, 4, 5 });
	
	return 0;

}


