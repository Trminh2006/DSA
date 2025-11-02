// TASK DESCRIPTION: https://oj.vnoi.info/problem/segtree_itlazy

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <cmath>
#include <stack>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define ll long long

const ll inf = 1e18 + 7;

int n, q;
vector <int> arr;

struct Node{
    int l, r;
    ll lazy, maxx;
};

class LazySegmentTree{
private:
    int _n;
    vector <Node> _st;

    ll objective(ll &x, ll &y){
        return max(x, y);
    }

    void build(int id, int l, int r, vector <int> &arr){
        if (l == r){
            _st[id] = Node{
                .l = l,
                .r = r,
                .lazy = 0,
                .maxx = 1LL * arr[l]
            };
            return;
        }

        int mid = (l + r) >> 1;
        build(id << 1, l, mid, arr);
        build((id << 1) + 1, mid + 1, r, arr);

        _st[id] = Node{
            .l = l,
            .r = r,
            .lazy = 0,
            .maxx = objective(_st[id << 1].maxx, _st[(id << 1) + 1].maxx)
        };
    }

    void fix(int id, int l, int r){
        if (!_st[id].lazy)
            return;

        _st[id].maxx += _st[id].lazy;

        if (l != r){
            _st[id << 1].lazy += _st[id].lazy;
            _st[(id << 1) + 1].lazy += _st[id].lazy;
        }

        _st[id].lazy = 0;
    }

public:
    LazySegmentTree(int n, vector <int> &arr){
        _n = n;
        _st.resize(n << 2);
        build(1, 0, n - 1, arr);
    }

    void update(int id, int l, int r, int &u, int &v, int &val){
        fix(id, l, r);
        if (u > r || v < l)
            return;

        // [l, r] in [u, v]
        if (l >= u && r <= v){
            _st[id].lazy += 1LL * val;
            fix(id, l, r);
            return;
        }

        int mid = (l + r) >> 1;
        update(id << 1, l, mid, u, v, val);
        update((id << 1) + 1, mid + 1, r, u, v, val);

        _st[id].maxx = objective(_st[id << 1].maxx, _st[(id << 1) + 1].maxx);
    }

    ll get(int id, int l, int r, int &u, int &v){
        fix(id, l, r);
        if (r < u || l > v)
            return -inf;

        // [l, r] in [u, v]
        if (l >= u && r <= v)
            return _st[id].maxx;

        int mid = (l + r) >> 1;
        ll get1 = get(id << 1, l, mid, u, v);
        ll get2 = get((id << 1) + 1, mid + 1, r, u, v);

        return objective(get1, get2);
    }

    void out(){
        cout << "\n============LAZY============\n";
        for (int i = 0; i <= (n << 2); ++i)
            cout << _st[i].lazy << " ";
        cout << "\n============================\n";

        cout << "============MAXX============\n";
        for (int i = 0; i <= (n << 2); ++i)
            cout << _st[i].maxx << " ";
        cout << "\n============================\n";
    }
};


void readData(){
    cin >> n;
    int k;
    for (int i = 0; i < n; ++i){
        cin >> k;
        arr.pb(k);
    }
    cin >> q;
}

void solve(){
    LazySegmentTree segTree(n, arr);
    // cout << "\n BEFORE queries: \n";
    // segTree.out();
    // cout << "\n";
    int k, u, v;
    while (q--){
        cin >> k;
        if (k & 1){
            cin >> u >> v >> k;
            --u, --v;
            segTree.update(1, 0, n - 1, u, v, k);
        } else {
            cin >> u >> v;
            --u, --v;
            cout << segTree.get(1, 0, n - 1, u, v) << "\n";
        }
        // segTree.out();
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    readData();
    solve();
    return 0;
}
