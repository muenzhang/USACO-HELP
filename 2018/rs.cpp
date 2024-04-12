#include <bits/stdc++.h>

#define int long long

using namespace std;

int n, m, r;
int c[100001], b[100001];
pair<int, int> p[100001];

bool cmp(int a, int b){
    return a > b;
}

bool cmp2(const pair<int, int> &a, const pair<int, int> &b){
    return a.second > b.second;
}


signed main() {
    cin >> n >> m >> r;
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= m; i++)
        cin >> p[i].first >> p[i].second;
    for (int i = 1; i <= r; i++)
        cin >> b[i];

    sort(c + 1, c + n + 1, cmp);
    sort(p + 1, p + m + 1, cmp2);
    sort(b + 1, b + r + 1, cmp);

    int ans = 0;

    for (int i = 1; i <= n; i++)
        b[i] += b[i - 1];

    int milk = 0, t = 1, s = 0;
    for (int i = 1; i <= n; i++){
        milk += c[i];
        while (t <= m && milk >= p[t].first)
            milk -= p[t].first, s += p[t].first * p[t].second, t++;
        if (t <= m)
            p[t].first -= milk, s += milk * p[t].second, milk = 0;
        ans = max(ans, s + b[min(r, n - i)]);
    }
    cout << ans << endl;
    return 0;
}