#include <bits/stdc++.h>

using namespace std;

using ld = long double;
using ull = unsigned long long;

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

const int LOG = 42;

struct node {
  node *next[2];
  node() {
    for (int i = 0; i < 2; i++) {
      next[i] = nullptr;
    }
  }
};

node *root = new node();

void add(long long x) {
  node *v = root;
  for (int b = LOG - 1; b >= 0; b--) {
    int to = ((x >> b) & 1LL);
    if (v->next[to] == nullptr) {
      v->next[to] = new node();
    }
    v = v->next[to];
  }
  return;
}

long long query(long long x) {
  node *v = root;
  long long res = 0ll;
  for (int b = LOG - 1; b >= 0; b--) {
    int to = 1 - ((x >> b) & 1LL);
    if (v->next[to]) {
      res += (1LL << b);
      v = v->next[to];
    } else {
      if (v->next[1 - to] == nullptr) {
        return res;
      }
      v = v->next[1 - to];
    }
  }
  return res;
}

void solve() {
  int n;
  cin >> n;
  vector<long long> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<long long> pref(n, 0ll);
  for (int i = 0; i < n; i++) {
    pref[i] = a[i];
    if (i) {
      pref[i] ^= pref[i - 1];
    }
  }
  long long ans = 0ll, suf = 0ll;
  add(suf);
  for (int i = n - 1; i >= 0; i--) {
    suf ^= a[i];
    add(suf);
    ans = max(ans, query((i - 1 < 0 ? 0 : pref[i - 1])));
  }
  cout << ans << '\n';
  return;
}

signed main() {
  ios_base :: sync_with_stdio(0);
  cin.tie(0) , cout.tie(0);
  int t = 1;
  while (t-- > 0) {
    solve();
  }
  return 0;
}
