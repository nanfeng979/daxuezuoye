#include <iostream>

using namespace std;
const int N = 1e3 + 10;
int dp[N][N];
const int maxLoop = 1000;
int gcd(int a, int b)
{
	return !b ? a : gcd(b, a % b);
}
int main()
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			dp[N][N] = 0;
		}
	}

	for (int i = 1; i <= maxLoop; i++)
	{
		for (int j = 1; j <= maxLoop; j++)
		{
			dp[i][j] = max(dp[i - 1][j] + (gcd(i, j) == 1), dp[i][j - 1] + (gcd(i, j) == 1));
		}
	}

	while (true)
	{
		int a, b;
		cout << "please input a hang: ";
		cin >> a;
		cout << "please input b lie: ";
		cin >> b;

		cout << dp[a][b] << endl;
		cout << "---------------" << endl;
	}
	return 0;
}