int longestValidParentheses(string s)
{
	if (s == "") return 0;
	vector<int> v;
	int len = s.size();
	int i = 0;
	int n = 0;
	while (i < len)
	{
		if (s[i] == '(')
		{
			++n;
			v.push_back(i);
		}
		else
		{
			if (n == 0)
				v.push_back(i);
			else
			{
				--n;
				v.pop_back();
			}
		}
		++i;
	}
	v.push_back(s.size());
	i = v.size() - 1;
	while (i >= 1)
	{
		v[i] = v[i] - (v[i - 1] + 1);
		--i;
	}
	return *max_element(v.begin(), v.end());
}