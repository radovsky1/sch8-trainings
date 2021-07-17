#include <bits/stdc++.h>

#define MAX_LOG 20
#define N (int)1e5 + 2

using namespace std;
mt19937 rnd(time(0));

int n;
vector<vector<int> > t(MAX_LOG , vector<int>(4 * N , 0));
vector<vector<int> > add(MAX_LOG , vector<int>(4 * N , 0));
vector<vector<int> > bit(MAX_LOG , vector<int>(N , 0));

void build(int T , int v , int vl , int vr) {
  if (vl == vr) {
    t[T][v] = bit[T][vl];
    return;
  }
  int vm = vl + (vr - vl) / 2;
  build(T , 2 * v + 1 , vl , vm);
  build(T , 2 * v + 2 , vm + 1 , vr);
  t[T][v] = t[T][2 * v + 1] + t[T][2 * v + 2];
}

void push(int T , int v , int vl , int vr) {
  if (add[T][v] != 0) {
    t[T][v] = (vr - vl + 1) - t[T][v];
    if (vl != vr) {
      add[T][2 * v + 1] ^= 1;
      add[T][2 * v + 2] ^= 1;
    }
    add[T][v] = 0;
  }
}

int query(int T , int v , int vl , int vr , int l , int r) {
  push(T , v , vl , vr);
  if (r < vl || vr < l)
    return 0;
  if (l <= vl && vr <= r)
    return t[T][v];
  int vm = vl + (vr - vl) / 2;
  int ql = query(T , 2 * v + 1 , vl , vm , l , r);
  int qr = query(T , 2 * v + 2 , vm + 1 , vr , l , r);
  return (ql + qr);
}

void update(int T , int v , int vl , int vr , int l , int r) {
  push(T , v , vl , vr);
  if (r < vl || vr < l)
    return;
  if (l <= vl && vr <= r) {
    add[T][v] ^= 1;
    push(T , v , vl , vr);
    return;
  }
  int vm = vl + (vr - vl) / 2;
  update(T , 2 * v + 1 , vl , vm , l , r);
  update(T , 2 * v + 2 , vm + 1 , vr , l , r);
  t[T][v] = t[T][2 * v + 1] + t[T][2 * v + 2];
}

int64_t Sum(int l , int r) {
  int64_t answer = 0;
  for (int j = 0; j < MAX_LOG; j++) {
    int cnt = query(j , 0 , 0 , n - 1 , l - 1 , r - 1);
    answer += (cnt * int64_t(1 << j));
  }
  return answer;
}

void Xor(int l , int r , int x) {
  for (int j = 0; j < MAX_LOG; j++) {
    int cur_bit = (x >> j) & 1;
    if (cur_bit)
      update(j , 0 , 0 , n - 1 , l - 1 , r - 1);
  }
}

int32_t main() {
  ios_base :: sync_with_stdio(0);
  cin.tie(0) , cout.tie(0);
  assert(cin >> n);
  for (int i = 0; i < n; i++) {
    int x;
    assert(cin >> x);
    for (int j = 0; j < MAX_LOG; j++) {
      bit[j][i] = (x >> j) & 1;
    }
  }
  for (int i = 0; i < MAX_LOG; i++)
    build(i , 0 , 0 , n - 1);
  int q;
  assert(cin >> q);
  for (int e = 0; e < q; e++) {
    int type;
    assert(cin >> type);
    if (type == 1) {
      int l , r;
      assert(cin >> l >> r);
      cout << Sum(l , r) << '\n';
    }
    if (type == 2) {
      int l , r , x;
      assert(cin >> l >> r >> x);
      Xor(l , r , x);
    }
  }
  return 0;
}
