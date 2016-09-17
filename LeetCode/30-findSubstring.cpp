vector<int> findSubstring(string s, vector<string>& words){
	vector<int> output;
	int n = words.size();
	int m = 0;
	int l = words.front().size();
	int t = n * l;
	int sl = s.size();
	bool condition = true;
	string r = "";
	while (m < l)
	{
		r += "*";
		++m;
	}
	m = 0;
	string ra = "";
	while (m < n)
	{
		ra += r;
		++m;
	}
	m = 0;
	while (m <= sl - t)
	{
		int j = 0;
		string s_ = s.substr(m, t);
		while(j < n)
		{
			int x = s_.find(words.at(j));
			while (x != -1 && x % l != 0)
				x = s_.find(words.at(j), x + 1);
			if (x == -1)
			{
				condition = false;
				break;
			}
			else
				s_ = s_.replace(x, l, r);
			++j;
		}
		if (s_ != ra)
			condition = false;
		if (condition)
			output.push_back(m);
		condition = true;
		++m;
	}
	return output;
}