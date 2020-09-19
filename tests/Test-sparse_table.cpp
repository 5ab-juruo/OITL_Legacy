#include <bits/stdc++.h>
#include "../sparse_table"
using namespace std;

const int max_n = 1000, max_q = 100;
int arr[max_n], mn[max_n];

struct get_min
{
	int operator()(int a, int b) const { return (a < b)? a:b; }
};

int main()
{
	oitl::sparse_table<max_n, int, get_min> st;
	default_random_engine ds;
	uniform_int_distribution<int> ug;
	get_min calc;

	for (int i = 0; i < max_n; i++)
	{
		arr[i] = ug(ds);

		if (i > 0)
			mn[i] = calc(arr[i], mn[i-1]);
		else
			mn[i] = arr[i];
	}
	
	st.refill(arr);

	for (int i = 1; i <= max_q; i++)
	{
		if (mn[i] != st.query(0, i + 1))
			printf("Unaccepted on Test #%02d. In range [1,%d]. Expected %d but found %d.\n", i, i, mn[i], st.query(0, i + 1));
		else
			printf("Accepted on Test #%02d.            ok the answer is %d\n", i, mn[i]);
	}

	return 0;
}