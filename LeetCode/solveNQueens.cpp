int solveNQueens(int n) {
	int k = 0;
	int count = 0;
	vector<int> v(n);
	auto check = [&](int k) {
		for (int i = 0; i < k; i++)
		{
			if (v[k] == v[i] || abs(k - i) == abs(v[k] - v[i]))
				return false;
		}
		return true;
	};
	function<void(int)> trace = [&](int k) {
		if (k >= n)
			++count;
		else
		{
			for (int i = 0; i < n; i++)
			{
				v[k] = i;
				if (check(k)) trace(k + 1);
			}
		}
	};
	int nn = n >> 1;
	if (n % 2 == 0)
	{
		for (int i = 0; i < nn; ++i)
		{
			v[0] = i;
			trace(1);
		}
		return count << 1;
	}
	else
	{
		for (int i = 0; i < nn; ++i)
		{
			v[0] = i;
			trace(1);
		}
		count = count << 1;
		v[0] = n / 2 + 1;
		trace(1);
		return count;
	}
}