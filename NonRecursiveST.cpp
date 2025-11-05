// TASK DESCRIPTION: https://cses.fi/problemset/task/1648

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
    ll val;
};

class SegmentTree{
private:
    int _n;
    vector <Node> _st;

    Node objective(Node &x, Node &y){
        Node node = Node();
        node.val = x.val + y.val;
        return node;
    }

    void build(vector <int> &arr){
        for (int i = 0; i < n; ++i)
            _st[i + n].val = 1LL * arr[i];

        for (int id = n - 1; id > 0; --id)
            _st[id] = objective(_st[id << 1], _st[id << 1 | 1]);
    }

public:
    SegmentTree(int &n, vector <int> &arr){
        _n = n;
        _st.resize(n << 1 | 1);
        build(arr);
    }

    void update(int pos, int val){
        // Caution
        // indices start from 0, but queries start from 1 -> pos -= 1

        --pos;
        for (_st[pos += n].val = 1LL * val; pos; pos >>= 1)
            _st[pos >> 1] = objective(_st[pos], _st[pos ^ 1]);
    }

    ll get(int l, int r){
        // Caution
        // 1) get [l, r) -> start from l += n and r += n + 1
        // 2) indices start from 0, but queries start from 1 -> l -= 1, r -= 1
        ll ans = 0;

        --l, --r;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1){
            if (l & 1) ans += _st[l++].val;
            if (r & 1) ans += _st[--r].val;
        }

        return ans;
    }
};

void readData(){
    int k, u, v;
    cin >> n >> q;
    for (int i = 0; i < n; ++i){
        cin >> k;
        arr.pb(k);
    }
}

void solve(){
    SegmentTree segTree = SegmentTree(n, arr);

    int k, u, v;
    while (q--){
        cin >> k >> u >> v;
        if (k & 1)
            segTree.update(u, v);
        else
            cout << segTree.get(u, v) << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    readData();

    solve();

    return 0;
}