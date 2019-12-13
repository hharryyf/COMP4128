#include <bits/stdc++.h>
#define INF 2000000000001
using namespace std;
typedef long long ll;
struct dogs {
	ll x;
	int c;
};

dogs a[1011];

vector<ll> g[1011];

ll dp[1011][2];

int n, k;

int T;

static bool cmp(const dogs &a, const dogs &b) {
	return a.x < b.x;
}

void init() {
	int i;
	for (i = 0 ; i < 1011; i++) {
		g[i].clear();
		dp[i][0] = dp[i][1] = INF;
		a[i].x = a[i].c = 0;
	}
}

int main() {
	int i, j, l, r;
	scanf("%d", &T);
	for (i = 1; i <= T; i++) {
		scanf("%d%d", &n, &k);
		init();
		//cout << "k= " << k << endl;
		for (j = 1; j <= n; j++) {
			scanf("%lld", &a[j].x);
		}
		
		for (j = 1; j <= n; j++) {
			scanf("%d", &a[j].c);
		}
		
		sort(a+1, a+n+1, cmp);
		
		for (j = 1; j <= n; j++) {
			g[a[j].c].push_back(a[j].x);
		}
		
		dp[0][0] = 0;
		dp[0][1] = 0;
		for (l = 1; l <= 10; l++) {
			for (j = k; j >= 0; j--) {
				for (r = 0; r < (int) g[l].size(); r++) {
					if (j >= r + 1) {
						dp[j][0] = min(dp[j][0], dp[j - r - 1][0] + 2 * g[l][r]);
						dp[j][1] = min(dp[j][1], dp[j-r-1][1] + 2 * g[l][r]);
						dp[j][1] = min(dp[j][1], dp[j-r-1][0] + g[l][r]);
					}
				}
				/*for(int x = 0; x < 2; ++x)
				if(dp[j][x] < INF)printf("dp[%d][%d][%d] = %lld\n" , l , j , x , dp[j][x]);*/
				// cout << l << ": " << "dp[" << j << "] " << dp[j][0] << " " << dp[j][1] << endl;
			}
			 
		}
		
		cout << "Case #" << i << ": " << dp[k][1] << endl;
	}
	
	return 0;
}
