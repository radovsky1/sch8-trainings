#include <bits/stdc++.h>

using namespace std;

using ld = long double;
using ull = unsigned long long;
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

const int LOG = 30;

struct node {
  node *next[2];
  int down, ends;
  node() {
    for (int i = 0; i < 2; i++) {
      next[i] = nullptr;
    }
    down = ends = 0;
  }
};

node *root = new node();

void add(int x) {
  node *v = root;
  for (int i = LOG - 1; i >= 0; i--) {
    int to = ((x >> i) & 1);
    if (v->next[to] == nullptr) {
      v->next[to] = new node();
    }
    v = v->next[to];
    v->down++;
  }
  return;
}

void del(int x) {
  node *v = root;
  for (int i = LOG - 1; i >= 0; i--) {
    int to = ((x >> i) & 1);
    node *go = v->next[to];
    if (go->down <= 1) {
      v->next[to] = nullptr;
    }
    v = go;
    v->down--;
  }
  return;
}

long long ask(int x) {
  node *v = root;
  long long res = 0ll;
  for (int i = LOG - 1; i >= 0; i--) {
    int to = 1 - ((x >> i) & 1);
    if (v->next[to] != nullptr) {
      res += (1LL << i);
    } else {
      to = 1 - to;
    }
    if (v->next[to] == nullptr) {
      break;
    }
    v = v->next[to];
  }
  return res;
}


void solve() {
  int q;
  cin >> q;
  add(0);
  while (q-- > 0) {
    char type;
    int x;
    cin >> type >> x;
    if (type == '+') {
      add(x);
    }
    if (type == '-') {
      del(x);
    }
    if (type == '?') {
      cout << ask(x) << '\n';
    }
  }
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
