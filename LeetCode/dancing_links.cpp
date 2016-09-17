#pragma comment(linker, "/STACK:1024000000,1024000000")  
#include<iostream>  
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
#include<map>  
#include<queue>  
#include<set>  
#include<cmath>  
#include<bitset>  
#define mem(a,b) memset(a,b,sizeof(a))  
#define lson i<<1,l,mid  
#define rson i<<1|1,mid+1,r  
#define llson j<<1,l,mid  
#define rrson j<<1|1,mid+1,r  
#define INF 0x7fffffff  
#define maxn 1000005  
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int head, sz;
int U[maxn], D[maxn], L[maxn], R[maxn];//������������ָ��  
int H[maxn], ROW[maxn], C[maxn], S[maxn], O[maxn];
void remove(int c)
{
	L[R[c]] = L[c];
	R[L[c]] = R[c];
	for (int i = D[c]; i != c; i = D[i])
		for (int j = R[i]; j != i; j = R[j])
		{
			U[D[j]] = U[j];
			D[U[j]] = D[j];
			--S[C[j]];
		}
}
void resume(int c)
{
	for (int i = U[c]; i != c; i = U[i])
	{
		for (int j = L[i]; j != i; j = L[j])
		{
			++S[C[j]];
			U[D[j]] = j;
			D[U[j]] = j;
		}
	}
	L[R[c]] = c;
	R[L[c]] = c;
}
void init(int m)//m����  
{
	head = 0;//ͷָ��Ϊ0  
	for (int i = 0; i <= m; i++)
	{
		U[i] = i;
		D[i] = i;//����˫��ʮ������  
		L[i] = i - 1;
		R[i] = i + 1;
		S[i] = 0;
	}
	R[m] = 0;
	L[0] = m;
	S[0] = INF + 1;
	sz = m + 1;
	memset(H, 0, sizeof(H));
}
void insert(int i, int j)
{
	if (H[i])
	{
		L[sz] = L[H[i]];
		R[sz] = H[i];
		L[R[sz]] = sz;
		R[L[sz]] = sz;
	}
	else
	{
		L[sz] = sz;
		R[sz] = sz;
		H[i] = sz;
	}
	U[sz] = U[j];
	D[sz] = j;
	U[D[sz]] = sz;
	D[U[sz]] = sz;
	C[sz] = j;
	ROW[sz] = i;
	++S[j];
	++sz;
}
bool dfs(int k, int len)
{
	if (R[head] == head)
	{
		sort(O, O + len*len);
		int p = 0;
		for (int i = 0; i<len; i++)
			for (int j = 0; j<len; j++)
			{
				int num = O[p++];
				num = num - (i*len + j)*len;
				printf("%d", num);
			}
		puts("");
		return  true;
	}
	int s = INF, c;
	for (int t = R[head]; t != head; t = R[t])
		if (S[t]<s) s = S[t], c = t;
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
}
void calc(int i, int j, int k, int len)
{
	int r = (i*len + j - 1)*len + k;
	int base = sqrt(len);
	//��i��������k  
	insert(r, i*len + k);
	//��j��������k  
	insert(r, len*len + (j - 1)*len + k);
	//��k��������k  
	int block = (j - 1) / base*base + i / base;
	insert(r, len*len * 2 + block*len + k);
	//��i��j����һ������(����һ��������ֻ��һ����)  
	insert(r, len*len * 3 + i*len + j);
}
void build(char *s, int len)//len��ʾ�Ǽ�������  
{
	int i, j, k, p = 0;
	init(len*len * 4);
	for (i = 0; i<len; i++)
		for (j = 1; j <= len; j++, p++)
		{
			if (s[p] == '.')
				for (k = 1; k <= len; k++)
					calc(i, j, k, len);
			else calc(i, j, s[p] - '0', len);
		}
}
int main()
{
	//freopen("1.txt","r",stdin);  
	char s[84];
	while (scanf_s("%s", s) && strcmp(s, "end"))
	{
		build(s, 9);
		dfs(0, 9);//�Ӹ���ʼ��  
	}
	return 0;
}