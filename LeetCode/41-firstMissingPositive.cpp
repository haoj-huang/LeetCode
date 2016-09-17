int firstMissingPositive(vector<int>& nums)
{
	if (nums.size() == 0)
		return 1;
	sort(nums.begin(), nums.end());
	int index;
	int n = 0;
	for (int i = 0; i < nums.size(); ++i)
	{
		int t = nums.at(i);
		if (t > 0)
		{
			index = i;
			break;
		}
		else
			++n;
	}
	if (n == nums.size())
		return 1;
	if (nums.at(index) != 1)
		return 1;
	int j = index + 1;
	if (j == nums.size())
		return 2;
	int d;
	while (j < nums.size())
	{
		d = nums.at(j) - nums.at(j - 1);
		if (d == 0 || d == 1)
			++j;
		else
			return nums.at(j - 1) + 1;
	}
	return nums.at(j - 1) + 1;
}