#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    string t = s;
    reverse(t.begin(), t.end());
    int m;
    cin >> m;
    int ans = 0;
    while (m--) {
        string p;
        cin >> p;
        int L = p.size();
        if (L < 2) continue;
        vector<int> kmp(L, 0);  
        int j = 0;
        for (int i = 1; i < L; i++) {
            while (j > 0 && p[i] != p[j]) {
                j = kmp[j-1];
            }
            if (p[i] == p[j]) {
                j++;
            } else {
                j = 0;
            }
            kmp[i] = j;
        }
        vector<int> left(L+1, n+1);
        j = 0;
        for (int i = 0; i < n; i++) {
            while (j > 0 && s[i] != p[j]) {
                j = kmp[j-1];
            }
            if (s[i] == p[j]) {
                j++;
            }
            if (j > 0 && left[j] == n+1) {
                left[j] = i;
            }
        }
        string q = p;
        reverse(q.begin(), q.end());
        vector<int> kmp_q(L, 0);
        j = 0;
        for (int i = 1; i < L; i++) {
            while (j > 0 && q[i] != q[j]) {
                j = kmp_q[j-1];
            }
            if (q[i] == q[j]) {
                j++;
            } else {
                j = 0;
            }
            kmp_q[i] = j;
        }
        vector<int> right_rev(L+1, n+1);
        j = 0;
        for (int i = 0; i < n; i++) {
            while (j > 0 && t[i] != q[j]) {
                j = kmp_q[j-1];
            }
            if (t[i] == q[j]) {
                j++;
            }
            if (j > 0 && right_rev[j] == n+1) {
                right_rev[j] = i;
            }
        }
        bool found = false;
        for (int k = 1; k < L; k++) {
            if (left[k] == n+1) continue;
            if (right_rev[L-k] == n+1) continue;
            int right_start = n - 1 - right_rev[L-k];
            if (left[k] < right_start) {
                found = true;
                break;
            }
        }
        if (found) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}