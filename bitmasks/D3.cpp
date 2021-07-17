#include <bits/stdc++.h>

using namespace std;

const int K = 100 + 1;

int main() {
  ios_base :: sync_with_stdio(0);
  cin.tie(0) , cout.tie(0);
  int n , m , q;
  cin >> n >> m >> q;
  vector<int> costs(n , 0);
  for (int i = 0; i < n; i++) {
    cin >> costs[i];
  }
  vector<int> masks((1 << n) , 0);
  for (int i = 0; i < m; i++) {
    int cur = 0;
    for (int j = 0; j < n; j++) {
      char x;
      cin >> x;
      cur += ((1 << j) * (x == '1' ? 1 : 0));
    }
    masks[cur]++;
  }
  vector<vector<int> > ans((1 << n) , vector<int>(K + 1 , 0));
  for (int mask = 0; mask < (1 << n); mask++) {
    for (int submask = 0; submask < (1 << n); submask++) {
      if (masks[submask] > 0) {
        int tot = 0;
        for (int i = 0; i < n; i++) {
          bool bit = (((mask >> i) & 1) == ((submask >> i) & 1));
          tot += (costs[i] * bit);
        }
        if (tot <= K) {
          ans[mask][tot] += masks[submask];
        }
      }
    }
  }
  while (q-- > 0) {
    int mask = 0;
    for (int i = 0; i < n; i++) {
      char x;
      cin >> x;
      mask += ((1 << i) * (x == '1' ? 1 : 0));
    }
    int k;
    cin >> k;
    int res = 0;
    for (int i = 0; i <= k; i++) {
      res += ans[mask][i];
    }
    cout << res << '\n';
  }
  return 0;
}
