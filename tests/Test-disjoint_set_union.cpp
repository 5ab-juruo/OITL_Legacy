#include "../disjoint_set_union"
#include <bits/stdc++.h>

using namespace std;

const int max_n = 100000, mod = 998244353;
int ans = 0;

void addans(bool res)
{
	ans = (2 * ans + res) % mod;
}

int main()
{
	freopen("1.in", "r", stdin);

	oitl::disjoint_set_union dsu;

	int n, m, opt, u, v;

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		dsu.add_element();
	
	while (m--)
	{
		scanf("%d%d%d", &opt, &u, &v);

		if (opt)
			addans(dsu.same_set(u, v));
		else
			dsu.unite_sets(u, v);
		
		if (!(m % 100000))
			printf("%d\n", m);
	}

	printf("%d\n", ans);

	return 0;
}
