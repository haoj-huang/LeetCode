#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <iterator>
#include <set>
#include <future>
#include <thread>
#include <chrono>
#include <ppl.h>
#include "windows.h"
using namespace std;
using namespace concurrency;
class Solution
{
public:
	Solution();
	~Solution();
	int firstMissingPositive(vector<int>& nums);
	bool isMatch(string s, string p);
	vector<int> findSubstring(string s, vector<string>& words);
	vector<int> inShuffle(vector<int>& sorted);
	void solveSudoku(vector<vector<char>>& board);
	void solveN_Queens(int n);
	int solveNQueens(int n);
private:

};

Solution::Solution()
{
}

Solution::~Solution()
{
}

// 41. First Missing Positive
int Solution::firstMissingPositive(vector<int>& nums)
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

bool Solution::isMatch(string s, string p){
	// 10. Regular Expreesion Matching
	/*
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
	*/

	// 44. Wildcard Matching
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

vector<int> Solution::findSubstring(string s, vector<string>& words){
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

vector<int> Solution::inShuffle(vector<int>& sorted){
	// time: O(n), space: O(n)
	size_t n = sorted.size();
	size_t n2 = n >> 1;
	for (size_t i = n2; i < n - ((n + 1) >> 2); ++i)
		if (i != n - i % n2 - 1)
			swap(sorted[i], sorted[n - i % n2 - 1]);
	vector<int> output(sorted);
	for (int i = 0; i < n2; ++i)
		output[i * 2 + 1] = sorted[i];
	for (int i = n2; i < n; ++i)
		output[(i - n2) * 2] = sorted[i];
	return output;
}

void Solution::solveSudoku(vector<vector<char>>& board) {
	const int maxn = 10009;
	int head;
	int nc; // 节点数目（node count：头节点 + 总列数）
	int U[maxn], D[maxn], L[maxn], R[maxn];
	int V[maxn], ROW[maxn], C[maxn], S[maxn], O[maxn];// O: 记录有效解中每个格子的值; C:辅助列数; S:记录该列中 1 的个数
	auto remove = [&](int c) {
		L[R[c]] = L[c];
		R[L[c]] = R[c];
		for (int i = D[c]; i != c; i = D[i])
			for (int j = R[i]; j != i; j = R[j])
			{
				U[D[j]] = U[j];
				D[U[j]] = D[j];
				--S[C[j]];
			}
	};
	auto resume = [&](int c) {
		L[R[c]] = c;
		R[L[c]] = c;
		for (int i = U[c]; i != c; i = U[i])
			for (int j = L[i]; j != i; j = L[j])
			{
				++S[C[j]];
				U[D[j]] = j;
				D[U[j]] = j;
			}
	};
	auto init = [&](int col) { // col 为总列数
		head = 0;//头指针为0  
		for (int i = 0; i <= col; i++) //建立双向十字链表
		{
			U[i] = i;
			D[i] = i;  
			L[i] = i - 1;
			R[i] = i + 1;
			S[i] = 0;
		}
		R[col] = 0;
		L[0] = col;
		nc = col + 1;
		memset(V, 0, sizeof(V));
	};
	auto insert = [&](int i, int j) { // i: 行 j:列
		if (V[i])
		{
			L[nc] = L[V[i]];
			R[nc] = V[i];
			L[R[nc]] = nc;
			R[L[nc]] = nc;
		}
		else
		{
			L[nc] = nc;
			R[nc] = nc;
			V[i] = nc;
		}
		U[nc] = U[j];
		D[nc] = j;
		U[D[nc]] = nc;
		D[U[nc]] = nc;
		C[nc] = j;
		ROW[nc] = i;
		++S[j];
		++nc;
	};
	function<bool(int,int)> dfs = [&](int k, int len) {
		if (R[head] == head) // 找到一组解
		{
			sort(O, O + len*len);
			int p = 0;
			for (int i = 0; i < len; i++)
			{
				for (int j = 0; j<len; j++)
				{
					int num = O[p++];
					num = num - (i*len + j)*len;
					board.at(i).at(j) = num + '0';
				}
			}
			return  true;
		}
		int c = R[0];
		for (int t = R[head]; t != head; t = R[t]) // 找到 1 最少的一列，减少迭代次数
			if (S[t]<S[c])
				c = t;
		remove(c);
		for (int i = D[c]; i != c; i = D[i])
		{
			O[k] = ROW[i];
			for (int j = R[i]; j != i; j = R[j])
				remove(C[j]);
			if (dfs(k + 1, len)) return  true;
			for (int j = L[i]; j != i; j = L[j])
				resume(C[j]);
		}
		resume(c);
		return  false;
	};
	auto calc = [&](int i, int j, int k, int len) {
		int r = (i*len + j)*len + k;
		int base = sqrt(len);
		//第i行有数字k  
		insert(r, i*len + k);
		//第j列有数字k  
		insert(r, len*len + j*len + k);
		//第k块有数字k  
		int block = j / base*base + i / base;
		insert(r, len*len * 2 + block*len + k);
		//第i行j列有一个数字(一个格子只填一个数)  
		insert(r, len*len * 3 + i*len + j + 1);
	};
	auto build = [&](vector<vector<char>>& s, int len) {
		int i, j, k;
		init(len*len * 4);
		for (i = 0; i<len; i++)
			for (j = 1; j <= len; j++)
			{
				if (s.at(i).at(j - 1) == '.') // 格子中没有填入数字，加入 9 * 4 行（可填入9种数字）
					for (k = 1; k <= len; k++)
						calc(i, j - 1, k, len);
				else calc(i, j - 1, s.at(i).at(j - 1) - '0', len); // 填入了数字，加入 4 行（行，列，块，格）
			}
	};
	build(board, 9);
	dfs(0, 9);
}

void Solution::solveN_Queens(int n){
	const int maxn = 4096;
	const int maxnode = 819200;
	int nc; // 节点数目（node count：头节点 + 总列数）
	int U[maxnode], D[maxnode], L[maxnode], R[maxnode];
	int V[maxn], ROW[maxnode], C[maxnode], S[maxn], O[maxn];// O: 记录有效解中每个格子的值; C:辅助列数; S:记录该列中 1 的个数
	int X[maxn], Y[maxn];
	int path[maxn];
	bool qnq[maxn];
	auto remove = [&](int c) {
		L[R[c]] = L[c];
		R[L[c]] = R[c];
		for (int i = D[c]; i != c; i = D[i])
			for (int j = R[i]; j != i; j = R[j])
			{
				U[D[j]] = U[j];
				D[U[j]] = D[j];
				--S[C[j]];
			}
	};
	auto resume = [&](int c) {
		L[R[c]] = c;
		R[L[c]] = c;
		for (int i = U[c]; i != c; i = U[i])
			for (int j = L[i]; j != i; j = L[j])
			{
				++S[C[j]];
				U[D[j]] = j;
				D[U[j]] = j;
			}
	};
	auto init = [&](int col) { // col 为总列数
		for (int i = 0; i <= col; i++) //建立双向十字链表
		{
			U[i] = i;
			D[i] = i;
			L[i] = i - 1;
			R[i] = i + 1;
			S[i] = 0;
		}
		R[col] = 0;
		L[0] = col;
		nc = col;
		memset(V, -1, sizeof(V));
	};
	auto insert = [&](int i, int j) {
		++S[C[++nc] = j];
		ROW[nc] = i;
		D[nc] = D[j];
		U[D[j]] = nc;
		U[nc] = j;
		D[j] = nc;
		if (V[i] >= 0)
		{
			R[nc] = R[V[i]];
			L[R[V[i]]] = nc;
			L[nc] = V[i];
			R[V[i]] = nc;
		}
		else
		{
			L[nc] = nc;
			R[nc] = nc;
			V[i] = nc;
		}
	};
	function<bool(int)> dfs = [&](int k) {
		if (R[0] == 0)
			return false;
		if (k >= n)
		{
			for (int i = 0; i < k; i++)
				path[X[O[i]]] = Y[O[i]];
			return true;
		}
		int c = R[0];
		for (int t = R[0]; t; t = R[t]) // 找到 1 最少的一列，减少迭代次数
			if(t <= n)
				if (S[t]<S[c]) c = t;
			else break;
		remove(c);
		for (int i = D[c]; i != c; i = D[i])
		{
			O[k] = ROW[i];
			for (int j = R[i]; j != i; j = R[j])
				remove(C[j]);
			if (dfs(k + 1))
				return true;
			for (int j = L[i]; j != i; j = L[j])
				resume(C[j]);
		}
		resume(c);
		return  false;
	};
	auto build = [&](vector<int> v) {
		memset(qnq, 0, sizeof(qnq));
		int R, F, D, rD, c = 1;
		init(n * 6);
		for (int i = 0; i < n; i++)
		{
			if (!v[i]) continue;
			R = v[i], F = n + i, D = 2 * n + i - v[i] + n, rD = 3 * n + n + i + v[i];
			qnq[R] = qnq[F] = qnq[D] = qnq[rD] = true;
			insert(c, R);
			insert(c, F);
			insert(c, D);
			insert(c, rD);
			X[c] = i, Y[c] = v[i];
			c++;
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				R = j, F = n + i, D = 2 * n + i - j + n, rD = 3 * n + n + i + j;
				if (qnq[R] || qnq[F] || qnq[D] || qnq[rD]) continue;
				insert(c, R);
				insert(c, F);
				insert(c, D);
				insert(c, rD);
				X[c] = i, Y[c] = j;
				c++;
			}
	};
	auto gen = [&](vector<int> v) {
		build(v);
		dfs(0);
		string p;
		for (int i = 0; i < n; i++)
		{
			if (path[i] <= 9 && path[i] >= 0)
				p.push_back('0' + path[i]);
			else if (path[i] > 9)
				p.push_back('A' + (path[i] - 10));
			else
				break;
		}
		return p;
	};
	vector<int> vx(n, 0);
	cout << gen(vx) << endl;
}

int Solution::solveNQueens(int n) {
	int k = 0;
	int count = 0;
	vector<int> v(n);
	auto check = [&](int k) {
		for (int i = 0; i < k; i++)
		{
			if (v[k] == v[i] || abs(k - i) == abs(v[k] - v[i]))
				return false;
		}
		return true;
	};
	// Method 1:
	v[k] = -1;
	while (k >= 0)
	{
		v[k] = v[k] + 1;
		while ((v[k] < n) && (!check(k))) v[k] = v[k] + 1;
		if (v[k] < n)
		{
			if (k < n - 1) { k = k + 1; v[k] = -1; }
			else ++count;
		}
		else k = k - 1;
	}
	return count;

	// Method 2:
	/*function<void(int)> trace = [&](int k) {
		if (k >= n)
			++count;
		else
		{
			for (int i = 0; i < n; i++)
			{
				v[k] = i;
				if (check(k)) trace(k + 1);
			}
		}
	};
	int nn = n >> 1;
	if (n % 2 == 0)
	{
		for (int i = 0; i < nn; ++i)
		{
			v[0] = i;
			trace(1);
		}
		return count << 1;
	}
	else
	{
		for (int i = 0; i < nn; ++i)
		{
			v[0] = i;
			trace(1);
		}
		count = count << 1;
		v[0] = n / 2 + 1;
		trace(1);
		return count;
	}*/

	/*auto func = [](int k, int N) {
		vector<int> v(N);
		v[0] = k;
		int count = 0;
		auto check = [&](int k) {
			for (int i = 0; i < k; i++)
			{
				if (v[k] == v[i] || abs(k - i) == abs(v[k] - v[i]))
					return false;
			}
			return true;
		};
		function<void(int)> trace = [&](int k) {
			if (k >= N)
				++count;
			else
			{
				for (int i = 0; i < N; i++)
				{
					v[k] = i;
					if (check(k)) trace(k + 1);
				}
			}
		};
		trace(1);
		return count;
	};*/
	// Method 3:
}

//Y combinator :
template <typename T, typename R>
function<R(T)> Y(function<function<R(T)>(function<R(T)>)> f)
{
	return f([=] (T x) { return Y(f)(x); });
}

typedef function<int(int)> fn_1;
typedef function<fn_1(fn_1)> fn_2;

fn_2 fact = [](fn_1 f)
{
	return [f](int n) {if (n == 0) return 1;  else return n*f(n - 1); };
};

fn_2 accum = [](fn_1 f)
{
	return [f](int n) {if (n > 0 && n <= 100) { cout << n << endl; return f(n + 1); } else return n; };
};

int main()
{
	function<function<int(int)>(function<function<int(int)>(function<int(int)>)>)> G = [&](function<function<int(int)>(function<int(int)>)> f) {return f([=](int x) {return G(f)(x); }); };
	function<int(int)> fa = [&](function<function<int(int)>(function<int(int)>)> g) {return g([=](int x) {return G(g)(x); }); }([](function<int(int)> f) {return [f](int n) { if (n == 0) return 1; else return n*f(n - 1); }; });
	cout << fa(7) << endl;

	Solution s;
	/*vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(6);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.push_back(9);
	v.push_back(10);
	int r = s.firstMissingPositive(v);
	cout << r << endl;*/

	/*fn_1 fac = Y(fact);
	int n = 10;
	cout << "factorial(" << n << ") = " << fac(n) << endl;*/

	//fn_1 acc = Y(accum);
	//int m = 1;
	//cout << "factorial(" << n << ") = " << acc(m) << endl;

	/*string str = "aaacdcd";
	string ss = "cd";
	int nn = find_last_pos(str, ss);
	cout << nn << " " << (str.substr(nn)) << endl;*/

	/*string str = "aaaaa";
	int ind_p = str.find_first_not_of('a');
	str = str.substr(ind_p);
	int ind_star = str.find_first_of('*');
	string ss = str.substr(0, ind_star);
	cout << ind_p << endl;*/

	/*string tmp1 = str.substr(0, index - 1);
	string tmp2 = str.substr(index + 1);
	cout << tmp1 + " + " + tmp2 << " " << " " << index << " " << str.find('f') << endl;*/

	//int index = str.find('f');
	//cout << index << endl;
	//const char * str = "abcde";
	//str = str + 3;
	//cout << *str << " " << *(str - 1) << " " << *str << endl;

	/*DWORD start = GetTickCount();
	cout << s.isMatch("babbba", "*bb?b*?") << endl;
	DWORD end = GetTickCount();
	cout << "running time: " << (end - start) << " ms" << endl;*/

	/*vector<string> vs;
	vs.push_back("ab");
	vs.push_back("ba");
	vs.push_back("ba");
	string ss = "ababaab";
	vector<int> x = s.findSubstring(ss, vs);
	for_each(x.begin(), x.end(), [](int elem) {cout << elem << ","; });
	cout << endl;*/

	/*auto head2back = [](vector<int> input) {
		int n = input.size();
		for (int i = 0; i < n - 1; ++i)
			swap(input.at(i), input.at(i + 1));
		return input;
	};
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v = head2back(v);
	for_each(v.begin(), v.end(), [](int elem) {cout << elem << " "; });
	cout << endl;*/

	/*size_t n = 7;
	cout << (n >> 2) << " " << (n % 2) << " " << (n << 1) << endl;*/

	/*vector<int> v;
	v.push_back(10);
	v.push_back(9);
	v.push_back(8);
	v.push_back(7);
	v.push_back(6);
	v.push_back(5);
	v.push_back(4);
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);
	vector<int> v_ = s.inShuffle(v);
	for_each(v_.begin(), v_.end(), [](int elem) {cout << elem << " "; });
	cout << endl;*/

	/*cout << ('.' - '0') << endl;*/

	/*set<char> ss;
	ss.insert('1');
	ss.insert('2');
	ss.insert('3');
	ss.insert('1');
	cout << ss.count('1') << " " << (ss.end() == ss.find('2')) << endl;*/

	/*vector<int> v;
	v.push_back(10);
	v.push_back(9);
	v.push_back(8);
	v.pop_back();
	for_each(v.begin(), v.end(), [](int elem) {cout << elem << " "; });
	cout << endl;*/

	/*vector<char> r1 = { '5','3','.','.','7','.','.','.','.' };
	vector<char> r2 = { '6','.','.','1','9','5','.','.','.' };
	vector<char> r3 = { '.','9','8','.','.','.','.','6','.' };
	vector<char> r4 = { '8','.','.','.','6','.','.','.','3' };
	vector<char> r5 = { '4','.','.','8','.','3','.','.','1' };
	vector<char> r6 = { '7','.','.','.','2','.','.','.','6' };
	vector<char> r7 = { '.','6','.','.','.','.','2','8','.' };
	vector<char> r8 = { '.','.','.','4','1','9','.','.','5' };
	vector<char> r9 = { '.','.','.','.','8','.','.','7','9' };
	vector<vector<char>> vs = { r1,r2,r3,r4,r5,r6,r7,r8,r9 };
	DWORD start = GetTickCount();
	s.solveSudoku(vs);
	DWORD end = GetTickCount();
	cout << "running time: " << (end - start) << " ms" << endl;
	for_each(vs.begin(), vs.end(), [](vector<char> v) {for_each(v.begin(), v.end(), [](char elem) {cout << elem << " "; }); cout << endl; });*/

	/*SYSTEM_INFO si;
	GetSystemInfo(&si);
	cout << si.dwNumberOfProcessors << endl;*/

	/*DWORD start = GetTickCount();
	s.solveN_Queens(8);
	DWORD end = GetTickCount();
	cout << "running time: " << (end - start) << " ms" << endl;*/

	/*vector<int> vx = { 1,0,0,0,0,0,0,0,0 };
	vector<int> vy = vx;
	cout << (vx == vy) << endl;*/

	//cout << floor(sqrt(8)) << endl;

	/*auto set_union = [&](set<string> s1, set<string> s2) {
		set<string> re;
		for_each(s1.begin(), s1.end(), [&](string s) {re.insert(s); });
		for_each(s2.begin(), s2.end(), [&](string s) {re.insert(s); });
		return re;
	};

	set<string> s1 = { "aa","bb","cc" };
	set<string> s2 = { "dd","bb","ee" };
	set<string> ss = set_union(s1, s2);
	for_each(ss.begin(), ss.end(), [](string s) {cout << s << " "; });
	cout << endl;*/
	
	/*int n = 4;
	vector<int> vs;
	for (int i = 0; i < n; i++)
	vs.push_back(i);
	for_each(vs.begin(), vs.end(), [](int s) {cout << s << " "; });
	cout << endl;*/

	auto func = [](int k, int N) {
		vector<int> v(N);
		v[0] = k;
		int count = 0;
		auto check = [&](int k) {
			for (int i = 0; i < k; i++)
			{
				if (v[k] == v[i] || abs(k - i) == abs(v[k] - v[i]))
					return false;
			}
			return true;
		};
		function<void(int)> trace = [&](int k) {
			if (k >= N)
				++count;
			else
			{
				for (int i = 0; i < N; i++)
				{
					v[k] = i;
					if (check(k)) trace(k + 1);
				}
			}
		};
		trace(1);
		return count;
	};

	int N = 10;
	DWORD start = GetTickCount();
	int nt = 0;
	vector<int> vs;
	int nn = N >> 1;
	vector<int> vv;
	for (int i = 0; i < nn; i++)
		vv.push_back(i);
	if (N % 2 == 0)
	{
		combinable<int> co([]() {return 0; });
		parallel_for_each(vv.cbegin(), vv.cend(), [&co, func, N](int k) {co.local() += func(k, N); });
		nt = co.combine(plus<int>()) << 1;
		/*for (int i = 0; i < nn; i++)
			vs.push_back(func(i, N));
		for_each(vs.begin(), vs.end(), [&](int k) {nt += k; });
		nt = nt << 1;*/
	}
	else
	{
		for (int i = 0; i < nn; i++)
			vs.push_back(func(i, N));
		for_each(vs.begin(), vs.end(), [&](int k) {nt += k; });
		nt = nt << 1;
		vs.push_back(func(nn, N));
		nt += vs.back();
	}
	cout << nt << endl;
	DWORD end = GetTickCount();
	cout << "running time: " << (end - start) << " ms" << endl;

	/*DWORD start1 = GetTickCount();
	int n = s.solveNQueens(N);
	DWORD end1 = GetTickCount();
	cout << n << endl;
	cout << "running time: " << (end1 - start1) << " ms" << endl;*/

 	system("pause");
}
