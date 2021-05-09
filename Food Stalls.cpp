// In the name of God

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <deque>
#include <assert.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <stdio.h>
#include <string.h>
#include <utility>
#include <math.h>
#include <bitset>
#include <iomanip>
#include <complex>

using namespace std;

#define rep(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template<typename T> inline bool smin(T &a, const T &b)   { return a > b ? a = b : a;    }
template<typename T> inline bool smax(T &a, const T &b)   { return a < b ? a = b : a;    }

typedef long long LL;
#define int long long
const int N = (int) 1e6 + 6, mod = (int) 0;
int a[N], c[N], o[N];
int cmp(int x, int y) { return a[x] < a[y]; }
int32_t main() {
	int tc;
	cin >> tc;
	for (int tt = 1; tt <= tc; ++tt) {
		cout << "Case #" << tt << ": ";
		int k, n;
		cin >> k >> n;		
		for (int j = 0; j < n; ++j) {
			cin >> a[j];
		}
		for (int j = 0; j < n; ++j) {
			cin >> c[j];
			o[j] = j;
		}
		sort(o, o + n, cmp);
		set<pair<int, int>> al, ar;
		set<pair<int, int>, greater<pair<int, int>>> bl, br;
		for (int j = 0; j < n; ++j) {
			ar.insert(mp(a[j] + c[j], j));
		}
		long long cur_res = 0, res = 1e18;
		for (int j = 0; j < n; ++j) {
			int nx = o[j];
			if (br.find(mp(a[nx] + c[nx], nx)) != br.end()) {
				cur_res -= a[nx] + c[nx];	
				br.erase(mp(a[nx] + c[nx], nx));
			} else {
				ar.erase(mp(a[nx] + c[nx], nx));
			}
			int pos = o[j];
			while ((int) bl.size() + (int) br.size() < k) {
				if (!al.size()) {
					int p = (*ar.begin()).second;
					cur_res += a[p] + c[p];
					br.insert(*(ar.begin()));
					ar.erase(ar.begin());
				} else if (!ar.size()) {
					int p = (*al.begin()).second;
					cur_res += -a[p] + c[p];
					bl.insert(*(al.begin()));
					al.erase(al.begin());
				} else {
					int pl = (*al.begin()).second, pr = (*ar.begin()).second;
					if (abs(a[pos] - a[pl]) + c[pl] < abs(a[pos] - a[pr]) + c[pr]) {
						cur_res += -a[pl] + c[pl];
						bl.insert(*(al.begin()));
						al.erase(al.begin());
					} else {		
						cur_res += a[pr] + c[pr];
						br.insert(*(ar.begin()));
						ar.erase(ar.begin());
					}
				}
			}
			while (true) {
				if ((int) al.size() && (int) br.size()) {
					int pl = (*al.begin()).second;
					int pr = (*br.begin()).second;
					if (abs(a[pos] - a[pl]) + c[pl] < abs(a[pos] - a[pr]) + c[pr]) {
						ar.insert(*br.begin());
						cur_res -= a[pr] + c[pr];
						br.erase(br.begin());
						cur_res += -a[pl] + c[pl];
						bl.insert(*al.begin());
						al.erase(al.begin());
						continue;
					}
				}
				if ((int) ar.size() && (int) bl.size()) {
					int pl = (*bl.begin()).second;
					int pr = (*ar.begin()).second;
					if (abs(a[pos] - a[pl]) + c[pl] > abs(a[pos] - a[pr]) + c[pr]) {
						br.insert(*ar.begin());
						cur_res += a[pr] + c[pr];
						ar.erase(ar.begin());
						cur_res -= -a[pl] + c[pl];
						al.insert(*bl.begin());
						bl.erase(bl.begin());
						continue;
					}
				}
				break;
			}
			res = min(res, c[pos] + cur_res + ((int) bl.size() - (int) br.size()) * a[pos]);
			al.insert(mp(-a[pos] + c[pos], pos));
		}
		cout << res << '\n';
			
	}
}

















