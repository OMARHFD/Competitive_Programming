# Prefix function definition

You are given a string  
`s`  of length  `n` . The prefix function for this string is defined as an array  `pi`  of length  `n` , 
where  `pi[i]`  is the length of the longest proper prefix of the substring  `s[0 ... i]`  which is also a suffix of this substring. 
A proper prefix of a string is a prefix that is not equal to the string itself. By definition,  `pi[0] = 0` .


# Implementation of a Prefix Function  O(n)
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
# Applications

## 1.KMP
we are searching if a string `s` appeared in a pattern `t` and where 
i build a string `s+#+t` where # is a character not appearing neither in `s` nor in `t` 
then i build the `pi array` i iterate through it if in position `i` `pi[i]=len(s)` the string is found and it finishes at position i 
so in `o(n)` time we solved the problem

## 2.number of occurences of each prefixe: `O(n)`
```cpp
vector<int> ans(n + 1);
for (int i = 0; i < n; i++)
    ans[pi[i]]++;
for (int i = n-1; i > 0; i--)
    ans[pi[i-1]] += ans[i];
for (int i = 0; i <= n; i++)
    ans[i]++;
```
## 3.number of distinct substrings: `O(n^2)`
we do it in an iterative way , lets consider `t` our test case , let's consider we know the answer for a proper prefix of `t` we denote it `s`
we can do tghat because if s is just one character (the first element in t so the number is 1
and then we consider `s* = s+c` c being the next charcter right after `s` in `t` 
we consider now that `s* =reversed(s*)` and we compute `pi` the maximal value of it means that there are max elemnts repeated so we add the added elements to the answer ` answer += len(s)+1-max(pi)` 
