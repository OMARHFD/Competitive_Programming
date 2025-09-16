# Suffix Array:
Let  `s`  be a string of length  `n` . The  `i` -th suffix of  `s`  is the substring  
`s[i ... n - 1]` .

A suffix array will contain integers that represent the starting indexes of the all the suffixes of a given string, after the aforementioned suffixes are sorted.

# Implementation `O(nlog(n))` :
```cpp
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
```

# Applications
## 1.Finding the smallest cyclic shift : => trivial
## 2.Finding a substring in a string :
  finding `s` in `t` in `O(|s|log(|t|))` by binary search
## 3.Comparing two substrings of a string :
  We just compare the classes with k the largest number possible but less than the lenght of substrings 
  if they have the same class we do the thing for the next 2^k elements that finish in the endpoints of the substrings 
## 4.Longest common prefix of two substrings:
  i and j here are th suffixes first endpoints
  ```cpp
  int lcp(int i, int j) {
    int ans = 0;
    for (int k = log_n; k >= 0; k--) {
        if (c[k][i % n] == c[k][j % n]) {
            ans += 1 << k;
            i += 1 << k;
            j += 1 << k;
        }
    }
    return ans;
  }
  ```
## 5.Number of different substrings
We preprocess the string  
`s`  by computing the suffix array and the LCP array. Using this information we can compute the number of different substrings in the string.
To do this, we will think about which new substrings begin at position  
`p[0]` , then at  `p[1]` , etc. In fact we take the suffixes in sorted order and see what prefixes give new substrings. Thus we will not overlook any by accident.
Because the suffixes are sorted, it is clear that the current suffix  `p[i]`  will give new substrings for all its prefixes, 
except for the prefixes that coincide with the suffix  `p[i-1]` . 
Thus, all its prefixes except the first  `lcp[i-1]`  one. 
Since the length of the current suffix is  `n - p[i]` ,  `n - p[i] - lcp[i-1]`  new prefixes start at  `p[i]` . 
Summing over all the suffixes, we get the final answer:
