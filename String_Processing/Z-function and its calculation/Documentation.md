# Z-Function Definition
Suppose we are given a string  `s`  of length  `n` . The Z-function for this string is an array of length  `n`  where the  `i` -th element is equal to the greatest number of characters starting from the position  `i`  that coincide with the first characters of  
`s` .
In other words,  
`z[i]`  is the length of the longest string that is, at the same time, a prefix of `s`  and a prefix of the suffix of  `s`  starting at `i` .
Note. In this article, to avoid ambiguity, we assume  
`0` -based indexes; that is: the first character of  `s`  has index  `0`  and the last one has index  `n-1` .
The first element of Z-function,  
`z[0]`, is generally not well defined. In this article we will assume it is zero (although it doesn't change anything in the algorithm implementation).
This article presents an algorithm for calculating the Z-function in  
`O(n)`  time, as well as various of its applications.
# Implementation 
```cpp
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
```

# Applications
## Substring search
## Number of different substrings in a string
