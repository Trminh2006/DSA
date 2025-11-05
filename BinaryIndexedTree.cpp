// TASK DESCRIPTION: https://cses.fi/problemset/task/1651

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

class BIT{
private:
    int _n;
    vector <ll> _bit;

public:
    BIT(int &n, vector <int> &arr){
        _n = n;
        _bit.resize(_n + 3);

        for (int i = 1; i <= _n; ++i)
            updatePoint(i, arr[i]);
    }

    void updatePoint(int pos, int val){
        for (; pos <= _n; pos += pos & (-pos))
            _bit[pos] += 1LL * val;
    }

    void updateRange(int l, int r, int val){
        updatePoint(l, val);
        updatePoint(r + 1, -val);
    }

    ll get(int pos){
        ll ans = 0;
        for (; pos; pos -= pos & (-pos))
            ans += _bit[pos];
        return ans;
    }
};

void readData(){
    cin >> n >> q;
    arr.resize(n + 3);
    vector <int> diff(n + 3);
    arr[0] = 0;
    for (int i = 1; i <= n; ++i){
        cin >> arr[i];
        diff[i] = arr[i] - arr[i - 1];
    }
    arr = diff;
}

void solve(){
    BIT Bit = BIT(n, arr);
    int k, u, v;
    while (q--){
        cin >> k;
        if (k & 1){
            cin >> u >> v >> k;
            Bit.updateRange(u, v, k);
        } else {
            cin >> k;
            cout << Bit.get(k) << "\n";
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    readData();
    solve();

    return 0;
}