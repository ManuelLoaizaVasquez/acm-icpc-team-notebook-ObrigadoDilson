const int N = 1e5;
struct SegmentTree {
  vector<int> tree[4 * N];
  int n;
  SegmentTree(int new_n) { n = new_n; }
  vector<int> Merge(const vector<int>& left, vector<int>& right) {
    int l = 0;
    int r = 0;
    vector<int> ans;
    int size = left.size() + right.size();
    for (int i = 0; i < size; i++) {
      if (l == left.size()) {
        ans.push_back(right[r++]);
      } else if (r == right.size()) {
        ans.push_back(left[l++]);
      } else if (left[l] < right[r]) {
        ans.push_back(left[l++]);
      } else {
        ans.push_back(right[r++]);
      }
    }
    return ans;
  }
  // O(nlgn)
  void Build(const vector<int>& a, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = {a[tl]};
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  // O(n). Con actualizaciones es mejor utilizar multiset u ost de nodos
  void Update(int pos, int val, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = {val};
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm) {
        Update(pos, val, 2 * id, tl, tm);
      } else {
        Update(pos, val, 2 * id + 1, tm + 1, tr);
      }
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  // O(lg^2(n))
  int Query(int l, int r, int x, int id, int tl, int tr) {
    if (l <= tl && tr <= r) {
      auto it = upper_bound(tree[id].begin(), tree[id].end(), x);
      if (it == tree[id].end()) return 0;
      int pos = it - tree[id].begin();
      return tree[id].size() - pos;
    }
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, x, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, x, 2 * id + 1, tm + 1, tr);
    return Query(l, r, x, 2 * id, tl, tm) + Query(l, r, x, 2 * id + 1, tm + 1, tr);
  }
  int Query(int l, int r, int x) { return Query(l, r, x, 1, 0, n - 1); }
} st;
