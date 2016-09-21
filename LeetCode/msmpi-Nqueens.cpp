#include <vector>
#include <functional>
#include <iostream>
#include "mpi.h"
#include "windows.h"

using namespace std;

int main(int argc, char* argv[])
{
	int nt = 0;
	DWORD start = GetTickCount();
	MPI_Init(&argc, &argv);

	int rank;
	int num;
	int N = 12;
	int nn = N >> 1;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num);
	
	auto func = [](int args[]) {
		int k = args[0];
		int N = args[1];
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

	if (rank != 0)
	{
		int o = 0;
		for (int i = rank; i < nn; i += num)
		{
			int p[2] = { i, N };
			o += func(p);
		}
		MPI_Send(&o, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else
	{
		int n0 = 0;
		for (int i = 0; i < nn; i += num)
		{
			int p[2] = { i, N };
			n0 += func(p);
		}
		for (int i = 1; i < num; i++)
		{
			int o;
			MPI_Recv(&o, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			nt += o;
		}
		nt = (nt + n0) << 1;
		if (N % 2 == 1)
		{
			int p[2] = { nn, N };
			nt += func(p);
		}
		cout << nt << endl;
		DWORD end = GetTickCount();
		cout << (end - start) << " ms" << endl;
	}

	MPI_Finalize();
	
	return 0;
}