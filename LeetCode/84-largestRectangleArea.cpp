int largestRectangleArea(vector<int>& heights) 
{
	size_t sz = heights.size();
	stack<int> st;
	vector<int> L(sz);
	vector<int> R(sz);
	for (size_t i = 0; i < sz; ++i)
	{
		while (!st.empty() && heights[st.top()] >= heights[i]) st.pop();
		L[i] = st.empty() ? 0 : st.top() + 1;
		st.push(i);
	}
	while (!st.empty()) st.pop();
	for (int i = (int)sz - 1; i >= 0; --i)
	{
		while (!st.empty() && heights[st.top()] >= heights[i]) st.pop();
		R[i] = st.empty() ? sz : st.top();
		st.push(i);
	}
	long long o = 0;
	for (size_t i = 0; i < sz; ++i) o = max(o, (long long)heights[i] * (R[i] - L[i]));
	return o;
}