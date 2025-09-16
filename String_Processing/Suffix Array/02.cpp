// link : https://www.codechef.com/problems/TANGLED
#include <bits/stdc++.h>
using namespace std;





vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
        vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int> suffix_array_construction(string s) {
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}



int main ()
    {
        int t ;
         cin >>t;
         while(t--)
            {
                int l; 
                string s1,s2;
                cin >> s1 >>s2>>l;
                int n1=s1.size();
                int n2=s2.size();
                vector <int > p1=suffix_array_construction(s1);
                vector <int > p2=suffix_array_construction(s2);
                for (int i =1; i<l+1;i++)
                    {
                        int answer=0;
                        int indx1 = 0;
                        int indx2 = 0;

                        while (indx1 < n1 && indx2 < n2) {
                        // Check if substrings of length l exist starting at these positions
                        if (p1[indx1] + l <= n1 && p2[indx2] + l <= n2) {
                        if (s1.compare(p1[indx1], l, s2, p2[indx2], l) == 0)
                        answer++;
                        // Move one of the indices forward to check next pair
                        if (p1[indx1] <= p2[indx2])
                        indx1++;
                        else
                            indx2++;
                         }
                        else {
                        // If one substring is too short, increment its index
                        if (p1[indx1] + l > n1)
                        indx1++;
                        if (p2[indx2] + l > n2)
                        indx2++;
                        }
    }

                            cout << answer << " ";
                    }

                cout <<endl;

            }





        return 0;
    }