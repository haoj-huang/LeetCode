bool isMatch(string s, string p){
	if (s == "" && p == "")
		return true;
	if (s != "" && p == "")
		return false;
	if (p[1] == '*')
	{
		int m = 0;
		int x = 0;
		char c = p[0];
		while (x < p.size() - 2)
		{
			if (p[x + 2] == c && p[x + 3] == '*')
				x += 2;
			else
				break;
		}
		string p_ = p.substr(x + 2);
		do
		{
			s = s.substr(m);
			if (isMatch(s, p_))
				return true;
			m = 0;
		} while (s != "" && (s[m++] == c || c == '.'));
		return false;
	}
	if (s != "" && (p[0] == '.' || p[0] == s[0]))
		return isMatch(s.substr(1), p.substr(1));
	return false;
}