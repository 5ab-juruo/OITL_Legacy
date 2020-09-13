#include "../binary_indexed_tree"
#include <bits/stdc++.h>
using namespace std;

const int max_n = 1000, max_q = 100000;
int bf[max_n];

int main()
{
	default_random_engine ds;
	uniform_int_distribution<int> ug;

	int n = max_n, rp;
	long long tot = 0;
	oitl::binary_indexed_tree<max_n, long long, plus<long long> > bit;

	for (int i = 0; i < n; i++)
	{
		bf[i] = ug(ds);
		tot += bf[i];

	//	printf("%lld  ", bit.query(i));

		bit.modify(i, (long long)bf[i]);

	//	printf("%lld %lld\n", tot, bit.query(i));
	}

	for (int i = 0; i < max_q; i++)
	{
		rp = (ug(ds) % max_n + max_n) % max_n;
		long long ans = bit.query(rp), tmp = 0;

		for (int j = 0; j <= rp; j++)
			tmp += bf[j];
		
		if (ans == tmp)
		{
			if (!(i % 100))
				printf("Accepted on test #%d.\n", i);
		}
		else
			printf("Unaccepted on test #%d. In range [1, %d], Expected %lld but found %lld.\n", i, rp + 1, tmp, ans);
	}

	return 0;
}