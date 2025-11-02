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

int n, q;
vector <int> arr;

struct Node{
    int l, r, minn;
};

class SegmentTree{
private:
    int _n;
    vector <Node> _st;

    int objectiveFunction(int &x, int &y){
        return min(x, y);
    }

    void build(int id, int l, int r, vector <int>& arr){
        if (l == r){
            _st[id] = Node{l, r, arr[l]};
            return;
        }

        int mid = (l + r) >> 1;
        build(id << 1, l, mid, arr);
        build((id << 1) + 1, mid + 1, r, arr);

        _st[id] = Node{
            .l = l,
            .r = r,
            .minn = objectiveFunction(_st[id << 1].minn, _st[(id << 1) + 1].minn)
        };
    }

public:
    SegmentTree(int n, vector <int>& arr) {
        _n = n;
        _st.resize(n << 2);
        build(1, 0, n - 1, arr);
    }

    void update(int id, int l, int r, int &val, int &pos){
        if (pos < l || pos > r)
            return;

        if (l == r){
            _st[id] = Node{l, r, val};
            return;
        }

        int mid = (l + r) >> 1;
        update(id << 1, l, mid, val, pos);
        update((id << 1) + 1, mid + 1, r, val, pos);

        _st[id] = Node{
            .l = l,
            .r = r,
            .minn = objectiveFunction(_st[id << 1].minn, _st[(id << 1) + 1].minn)
        };
    }

    int get(int id, int l, int r, int &u, int &v){
        if (v < l || u > r)
            return INT32_MAX;

        // [l, r] in [u, v]
        if (l >= u && r <= v)
            return _st[id].minn;

        int mid = (l + r) >> 1;
        int get1 = get(id << 1, l, mid, u, v);
        int get2 = get((id << 1) + 1, mid + 1, r, u, v);

        return objectiveFunction(get1, get2);
    }
};

void readData(){
    cin >> n >> q;
    int k;
    for (int i = 0; i < n; ++i){
        cin >> k;
        arr.pb(k);
    }
}

void solve(){
    SegmentTree segTree(n, arr);

    int k, u, v;
    while (q--){
        cin >> k >> u >> v;
        if (k & 1){
            --u;
            segTree.update(1, 0, n - 1, v, u);
        }else{
            --u, --v;
            cout << segTree.get(1, 0, n - 1, u, v) << "\n";
        }
    }

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    readData();
    solve();
    return 0;
}
