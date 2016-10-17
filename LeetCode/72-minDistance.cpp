int minDistance(string word1, string word2)
{
	int n1 = word1.size() + 1, n2 = word2.size() + 1;
	vector<int> dp(n1*n2);
	for (int i = 0; i < n1; ++i) dp[i*n2] = i;
	for (int i = 0; i < n2; ++i) dp[i] = i;
	for (int i = 0; i < n1 - 1; ++i)
		for (int j = 0; j < n2 - 1; ++j)
			if (word1[i] == word2[j]) dp[(i + 1)*n2 + j + 1] = dp[i*n2 + j];
			else dp[(i + 1)*n2 + j + 1] = min(min(dp[(i + 1)*n2 + j] + 1, dp[i*n2 + j + 1] + 1), dp[i*n2 + j] + 1);
	return dp.back();
}