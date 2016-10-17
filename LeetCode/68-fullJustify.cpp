vector<string> fullJustify(vector<string>& words, int maxWidth)
{
	int L = maxWidth;
	vector<string> vo;
	queue<string> q, qt;
	auto f_text = [&]() {
		int l = L + (int)q.size();
		if (q.size() == 1)
		{
			q.front().append(string(l, ' '));
			vo.push_back(q.front());
		}
		else
		{
			string st;
			int t = (int)q.size() - 1 - l % ((int)q.size() - 1);
			while (q.size() > 1) { qt.push(q.front()); q.pop(); }
			while (l > 0) { qt.front().push_back(' '); qt.push(qt.front()); qt.pop(); --l; }
			while (t > 0) { qt.push(qt.front()); qt.pop(); --t; }
			while (!qt.empty()) { st.append(qt.front()); qt.pop(); }
			vo.push_back(st.append(q.front()));
		}
		q.pop();
		L = maxWidth;
	};
	for(size_t i=0;i<words.size();)
		if ((int)words[i].size() <= L) { q.push(words[i]); L -= (words[i].size() + 1); ++i; }
		else f_text();
	string str;
	if (L >= 0)
	{
		while (!q.empty()) { q.front().push_back(' '); str.append(q.front()); q.pop(); }
		if (L > 0) str.append(string(L, ' '));
	}
	else
	{
		while (q.size() > 1) { q.front().push_back(' '); str.append(q.front()); q.pop(); }
		str.append(q.front());
		q.pop();
	}
	vo.push_back(str);
	return vo;
}