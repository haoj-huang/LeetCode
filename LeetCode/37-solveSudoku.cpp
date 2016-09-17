void solveSudoku(vector<vector<char>>& board) {
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