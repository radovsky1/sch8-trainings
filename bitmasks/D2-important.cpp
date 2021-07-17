#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int N = 2e5 + 5;

vector<int> cnt , light(N , 0);
vector<pair<int , int> > seg(N , {0 , 0});
vector<vector<int> > g(N , vector<int>());
vector<int> t(4 * N , 0) , add(4 * N , 0);

void dfs(int v , int p = -1) {
   cnt.push_back(v);
   seg[v].first = (int)cnt.size() - 1;
   for (auto to : g[v]) {
      if (to != p) {
         dfs(to , v);
      }
   }
   seg[v].second = (int)cnt.size() - 1;
}

void build(int v , int vl , int vr) {
   if (vl == vr) {
      t[v] = light[cnt[vl]];
      return;
   }
   int vm = vl + (vr - vl) / 2;
   build(2 * v + 1 , vl , vm);
   build(2 * v + 2 , vm + 1 , vr);
   t[v] = t[2 * v + 1] + t[2 * v + 2];
}

void push(int v , int vl , int vr) {
   if (add[v] != 0) {
      t[v] = (vr - vl + 1) - t[v];
      if (vl != vr) {
         add[2 * v + 1] ^= 1;
         add[2 * v + 2] ^= 1;
      }
      add[v] = 0;
   }
}

void update(int v , int vl , int vr , int l , int r) {
   push(v , vl , vr);
   if (r < vl || vr < l)
      return;
   if (l <= vl && vr <= r) {
      add[v] ^= 1;
      push(v , vl , vr);
      return;
   }
   int vm = vl + (vr - vl) / 2;
   update(2 * v + 1 , vl , vm , l , r);
   update(2 * v + 2 , vm + 1 , vr , l , r);
   t[v] = t[2 * v + 1] + t[2 * v + 2];
}

int query(int v , int vl , int vr , int l , int r) {
   push(v , vl , vr);
   if (r < vl || vr < l)
      return 0;
   if (l <= vl && vr <= r)
      return t[v];
   int vm = vl + (vr - vl) / 2;
   int ql = query(2 * v + 1 , vl , vm , l , r);
   int qr = query(2 * v + 2 , vm + 1 , vr , l , r);
   return (ql + qr);
}

int main() {
   #ifdef _DEBUG
      ifstream cin("input.txt");
   #endif
   ios_base :: sync_with_stdio(0);
   cin.tie(0) , cout.tie(0);
   int n;
   cin >> n;
   for (int i = 1; i < n; i++) {
      int p;
      cin >> p;
      p--;
      g[p].push_back(i);
   }
   for (int i = 0; i < n; i++) {
      cin >> light[i];
   }
   dfs(0);
   build(0 , 0 , n - 1);
   int q;
   cin >> q;
   while (q-- > 0) {
      string cmd;
      int c;
      cin >> cmd >> c;
      c--;
      if (cmd == "get") {
         cout << query(0 , 0 , n - 1 , seg[c].first , seg[c].second) << '\n';
      }
      if (cmd == "pow") {
         update(0 , 0 , n - 1 , seg[c].first , seg[c].second);
      }
   }
   return 0;
}
