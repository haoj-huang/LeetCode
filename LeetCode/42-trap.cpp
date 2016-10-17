int trap(vector<int>& height)
{
	vector<int>::iterator its = height.end();
	for(vector<int>::iterator it=height.begin();it!=height.end();++it)
		if (*it > *(it + 1)) { its = it; break; }
	if (its == height.end()) return 0;
	vector<int>::iterator itm = its;
	for (vector<int>::iterator it = its; it != height.end(); ++it)
		if (*it >= *itm) itm = it;
	auto trap_in = [](vector<int> v) {
		int o = 0, t = 0;
		vector<int>::iterator itb = v.begin();
		for(vector<int>::iterator ite=v.begin();ite!=v.end();)
			if (*(++ite) >= *itb) { o += (distance(itb, ite) - 1)*(*itb) - t; itb = ite; t = 0; }
			else t += *ite;
		return o;
	};
	vector<int> vl(its, itm + 1);
	if (itm + 1 == height.end()) return trap_in(vl);
	vector<int> vr(itm, height.end());
	reverse(vr.begin(), vr.end());
	return trap_in(vl) + trap(vr);
}