int jump(vector<int>& nums)
{
	size_t sz = nums.size();
	if (sz <= 1) return 0;
	int n = 0;
	auto max_pos = [](vector<int>::iterator its, vector<int>::iterator ite) {
		vector<int>::iterator itm = its;
		for (vector<int>::iterator it = its; it != ite; ++it)
			if (*it + distance(its, it) >= *itm + distance(its, itm)) itm = it;
		return itm;
	};
	for (vector<int>::iterator it = nums.begin(); distance(nums.begin(), it) <= (int)sz;)
	{
		++n;
		if (*it + distance(nums.begin(), it) + 1 >= (int)sz) break;
		it = max_pos(it, it + (*it) + 1);
		if (*it + distance(nums.begin(), it) + 1 >= (int)sz) { ++n; break; }
	}
	return n;
}