vector<int> inShuffle(vector<int>& sorted){
	// time: O(n), space: O(n)
	size_t n = sorted.size();
	size_t n2 = n >> 1;
	for (size_t i = n2; i < n - ((n + 1) >> 2); ++i)
		if (i != n - i % n2 - 1)
			swap(sorted[i], sorted[n - i % n2 - 1]);
	vector<int> output(sorted);
	for (int i = 0; i < n2; ++i)
		output[i * 2 + 1] = sorted[i];
	for (int i = n2; i < n; ++i)
		output[(i - n2) * 2] = sorted[i];
	return output;
}