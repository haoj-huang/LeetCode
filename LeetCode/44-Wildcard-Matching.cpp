bool isMatch(string s, string p){
    if (s == "" && p == "")
		return true;
	if (s != "" && p == "")
		return false;
	if (p[0] == '*')
	{
		int ind_p = p.find_first_not_of('*');
		if (ind_p != -1)
		{
			p = p.substr(ind_p);
			int ind_star = p.find('*');
			if (ind_star == -1)
			{
				if (s.size() < p.size())
					return false;
				return isMatch(s.substr(s.size() - p.size(), p.size()), p);
			}
			string interval = p.substr(0, ind_star);
			if (interval.size() == 1)
			{
				char c = p[0];
				if (c == '?')
					return isMatch(s, p);
				int ind_s = s.find(c);
				if (ind_s == -1)
					return false;
				s = s.substr(ind_s);
				return isMatch(s, p);
			}
			if (interval.size() > s.size())
				return false;
			int ind_a = interval.find('?');
			if (ind_a == -1)
			{
				if (s.find(interval) == -1)
					return false;
				s = s.substr(s.find(interval));
				return isMatch(s, p);
			}
			else
			{
				do
				{
					if (isMatch(s, p))
						return true;
					s = s.substr(1);
				} while (s.size() >= interval.size());
				return false;
			}
		}
		return true;
	}
	if (s != "" && (p[0] == '?' || p[0] == s[0]))
		return isMatch(s.substr(1), p.substr(1));
	return false;
}