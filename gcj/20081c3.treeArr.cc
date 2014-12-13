#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int MOD = 1000000007;
const int N = 500007;

int sum[N];
int tmp[N];
int num[N];
int dp[N];

void init(int x, int y, int z, int n, int m)
{
	for(int i = 0; i < n; i++)
	{
		int a = i % m;
		num[i + 1] = tmp[a];
		tmp[a] = ((LL)tmp[a] * x + (LL)(i + 1) * y) % z;
	}
	memset(sum, 0, sizeof(sum));
	for(int i = 1; i <= n; i++)
		tmp[i] = num[i];
}

int qcf(int n)
{
	sort(num + 1, num + 1 + n);
	int ans = 1;
	for(int i = 2; i <= n; i++)
		if(num[i] != num[i - 1])
			num[++ans] = num[i];
	return ans;
}

inline int lb(int x)
{
	return x & (-x);
}

int bf(int l, int r, int a)
{
	while(l <= r)
	{
		int m = (l + r) >> 1;
		if(num[m] == a)
			return m;
		if(num[m] > a)
			r = m - 1;
		else
			l = m + 1;
	}
	return -1;
}

void add(int x, int v, int n)
{
	while(x <= n)
	{
		sum[x] += v;
		if(sum[x] >= MOD)
			sum[x] -= MOD;
		x += lb(x);
	}
}

int que(int x)
{
	int ans = 0;
	while(x > 0)
	{
		ans += sum[x];
		if(ans >= MOD)
			ans -= MOD;
		x -= lb(x);
	}
	return ans;
}

int main()
{
	int T, C = 1;
	scanf("%d", &T);
	while(T--)
	{
		int n, m, x, y, z;
		scanf("%d%d%d%d%d", &n, &m, &x, &y, &z);
		for(int i = 0; i < m; i++)
			scanf("%d", tmp + i);
		init(x, y, z, n, m);
		m = qcf(n);
		dp[1] = 1;
		x = bf(0, m + 1, tmp[1]);
		add(x + 1, 1, m);
		for(int i = 2; i <= n; i++)
		{
			x = bf(0, m + 1, tmp[i]);
			dp[i] = 1 + que(x);
			if(dp[i] >= MOD)
				dp[i] -= MOD;
			add(x + 1, dp[i], m);
		}
		int ans = 0;
		for(int i = 1; i <= n; i++)
		{
			ans += dp[i];
			if(ans >= MOD)
				ans -= MOD;
		}
		printf("Case #%d: %d\n", C++, ans);
	}
	return 0;
}

