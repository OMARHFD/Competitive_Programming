## Prefix function definition

You are given a string  
`s`  of length  `n` . The prefix function for this string is defined as an array  `pi`  of length  `n` , 
where  `pi[i]`  is the length of the longest proper prefix of the substring  `s[0 ... i]`  which is also a suffix of this substring. 
A proper prefix of a string is a prefix that is not equal to the string itself. By definition,  `pi[0] = 0` .


## Implementation of a Prefix Function  O(n)
```cpp
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
```
## Applications

