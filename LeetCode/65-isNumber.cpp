bool isNumber(string s)
{
    int i = 0;
	while (s[i] == ' ') ++i;
	s = s.substr(i);
	if (s == "") return false;
	while (s.back() == ' ') s.pop_back();
	int len = s.size();
	bool b = false;
	int nop = 0;
	int noe = 0;
	auto state = [&len，&s](int k) {
		if (k >= len || k < 0) return -1;
		else if (s[k] == '-' || s[k] == '+') return 1;
		else if (s[k] == '.')return 2;
		else if (s[k] >= '0' && s[k] <= '9') return 3;
		else if (s[k] == 'e') return 4;
		else return 0;
	};
	function<bool()> check = [&check, &state, &i, &b, &nop, &noe]() {
		switch (state(i))
		{
		case -1: break;
		case 1:
			switch (state(++i))
			{
				case 1:
				case 4: b = false; break;
				case 3:
				case 2:
				default:check(); break;
			}
			break;
		case 2:++nop; if (nop > 1 || noe > 0) { b = false; break; }
			switch (state(++i))
			{
				case 1:
				case 2: b = false; break;
				case 4:
					if (state(i - 2) != 3) b = false;
					else check();
					break;
				case 3:
				default:check(); break;
			}
			break;
		case 3:b |= true;
			switch (state(++i))
			{
				case 1:b = false; break;
				case 3:
				case 2:
				case 4:
				default:check(); break;
			}
			break;
		case 4:++noe; if (noe > 1) { b = false; break; }
				if (i == 0 || state(i + 1) == -1) b = false;
				else
					switch (state(++i))
					{
						case 2:
						case 4:b = false; break;
						case 1:
							if (state(i + 1) != 3) b = false;
							else check();
							break;
						case 3:
						default:check(); break;
					}
				break;
			default: b = false; break;
		}
		return b;
	};
	i = 0;
	return check();
}