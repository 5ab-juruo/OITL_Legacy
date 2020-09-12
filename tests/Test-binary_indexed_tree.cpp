#include "../binary_indexed_tree"
#include <bits/stdc++.h>
using namespace std;

const int max_n = 1000, max_q = 100;
int bf[max_n];

int main()
{
	default_random_engine ds;
	uniform_int_distribution<int> ug;

	int n = max_n, rp;
	oitl::binary_indexed_tree<max_n, long long, plus<long long> > bit;

	for (int i = 0; i < n; i++)
	{
		bf[i] = ug(ds);
		bit.modify(i, bf[i]);
	}

	for (int i = 0; i < max_q; i++)
	{
		rp = (ug(ds) % max_n + max_n) % max_n;
		int ans = bit.query(rp);

		for (int j = 0; j <= rp; j++)
			ans -= bf[j];
		
		if (ans == 0)
			printf("Accepted on test #%d.\n", i);
		else
			printf("Unaccepted on test #%d.\n", i);
	}

	return 0;
}