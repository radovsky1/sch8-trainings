/*
  link to algo: #
*/
#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

/*
#pragma comment(linker, "/STACK:256000000")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("-O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
*/

template <class T> inline T gcd(T a , T b) { return !a ? b : gcd(b % a , a); }
template <class T> inline T lcm(T a , T b) { return (a * b) / gcd(a , b) ; }

mt19937 rnd(time(0));

#define all(x) x.begin(), x.end()
#define debug(x) { cerr << #x << " = " << x << endl; }

const int LOG = 21;
const int N = 1e5 + 2;
const int MOD = 1e9 + 7;

ll binpow(ll base, int n) {
  ll res = 1;
  while (n) {
    if (n & 1) {
      res *= base;
      res %= MOD;
    }
    base *= base;
    base %= MOD;
    n >>= 1;
  }
  return res;
}

ll basis[LOG], sz;

void insertToBasis(int mask) {
  for (int bt = 0; bt < LOG; bt++) {
    if ((mask & (1 << bt)) == 0) {
      continue;
    }
    if (!basis[bt]) {
      basis[bt] = mask;
      sz++;
      return;
    }
    mask ^= basis[bt];
  }
  return;
}

bool insideBasis(int mask) {
  for (int bt = 0; bt < LOG; bt++) {
    if ((mask & (1 << bt)) == 0) {
      continue;
    }
    if (!basis[bt]) {
      return false;
    }
    mask ^= basis[bt];
  }
  return true;
}

ll powers[N];

void precalc() {
  powers[0] = 1;
  for (int i = 1; i < N; i++) {
    powers[i] = (powers[i - 1] * 2LL) % MOD;
  }
  return;
}

void solve() {
  int n, q;
  cin >> n >> q;
  precalc();
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<int> val(q, 0);
  vector<vector<int>> queries(n, vector<int>());
  for (int i = 0; i < q; i++) {
    int pos;
    cin >> pos >> val[i];
    pos--;
    queries[pos].push_back(i);
  }
  vector<int> ans(q, 0);
  for (int i = 0; i < n; i++) {
    insertToBasis(a[i]);
    for (int it : queries[i]) {
      if (insideBasis(val[it])) {
        ans[it] = powers[i + 1 - sz];
      }
    }
  }
  for (int i = 0; i < q; i++) {
    cout << ans[i] << '\n';
  }
  return;
}

signed main() {
  ios_base :: sync_with_stdio(0);
  cin.tie(0) , cout.tie(0);
  int t = 1;
  while (t--) {
    solve();
  }
  return 0;
}
