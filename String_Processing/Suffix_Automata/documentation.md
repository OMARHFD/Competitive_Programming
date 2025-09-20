# Suffix Automaton in C++ - Complete Guide

## What a Suffix Automaton Does

A suffix automaton is a powerful data structure that efficiently represents all suffixes of a given string. Think of it as a compressed version of a suffix tree that:

- Stores all suffixes of a string in a compact way
- Allows efficient substring queries - check if a pattern exists in the text
- Counts distinct substrings - without enumerating them all
- Finds longest common substrings between two strings
- Locates all occurrences of a pattern in the text

It's essentially a finite state automaton (like a DFA) where each state represents a set of substrings that share common ending positions.

## Complexity Analysis

- **Construction Time:** O(n) where n is the length of the input string  
- **Space Complexity:** O(n) states and transitions  
- **Query Time:**
  - Substring check: O(m) where m is pattern length  
  - Distinct substring count: O(1) after construction  
  - Longest common substring: O(m) for second string of length m  

## Complete C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class SuffixAutomaton {
public:
    struct State {
        int len;            // Length of the longest string in this state
        int link;           // Suffix link
        map<char, int> next; // Transitions
        bool isEnd;         // Marks if state is an end state
        int count;          // Count of occurrences (optional)
    };

    vector<State> st;
    int last;
    int size;  // Number of states

    SuffixAutomaton() {
        st.push_back({0, -1, {}, false, 0});
        last = 0;
        size = 1;
    }

    void extend(char c) {
        int cur = size++;
        st.push_back({st[last].len + 1, 0, {}, false, 1});
        
        int p = last;
        while (p != -1 && st[p].next.find(c) == st[p].next.end()) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = size++;
                st.push_back({st[p].len + 1, st[q].link, st[q].next, false, 0});
                
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                
                st[q].link = clone;
                st[cur].link = clone;
            }
        }
        
        last = cur;
    }

    void build(const string &s) {
        for (char c : s) {
            extend(c);
        }
        markEndStates();
    }

    void markEndStates() {
        for (int p = last; p != 0; p = st[p].link) {
            st[p].isEnd = true;
        }
        st[0].isEnd = true;
    }

    // Check if pattern is a substring
    bool isSubstring(const string &pattern) {
        int state = 0;
        for (char c : pattern) {
            if (st[state].next.find(c) == st[state].next.end()) {
                return false;
            }
            state = st[state].next[c];
        }
        return true;
    }

    // Count all distinct substrings
    long long countDistinctSubstrings() {
        long long result = 0;
        for (int i = 1; i < size; i++) {
            result += st[i].len - st[st[i].link].len;
        }
        return result;
    }

    // Find longest common substring with another string
    string longestCommonSubstring(const string &t) {
        int state = 0, length = 0;
        int bestLen = 0, bestPos = 0;
        
        for (int i = 0; i < t.size(); i++) {
            char c = t[i];
            while (state != 0 && st[state].next.find(c) == st[state].next.end()) {
                state = st[state].link;
                length = st[state].len;
            }
            
            if (st[state].next.find(c) != st[state].next.end()) {
                state = st[state].next[c];
                length++;
                if (length > bestLen) {
                    bestLen = length;
                    bestPos = i;
                }
            }
        }
        
        return t.substr(bestPos - bestLen + 1, bestLen);
    }

    // Get the number of states
    int getStateCount() {
        return size;
    }
};

int main() {
    string s = "abcbc";
    SuffixAutomaton sa;
    sa.build(s);
    
    cout << "Automaton built for: " << s << endl;
    cout << "Number of states: " << sa.getStateCount() << endl;
    cout << "Distinct substrings: " << sa.countDistinctSubstrings() << endl;
    
    // Test substring queries
    vector<string> testPatterns = {"bc", "cb", "abc", "cba", "bcbc"};
    for (const string &pattern : testPatterns) {
        cout << "Is '" << pattern << "' a substring? " 
             << (sa.isSubstring(pattern) ? "Yes" : "No") << endl;
    }
    
    // Test longest common substring
    string t = "tabc";
    cout << "Longest common substring with '" << t << "': " 
         << sa.longestCommonSubstring(t) << endl;
    
    t = "bcxy";
    cout << "Longest common substring with '" << t << "': " 
         << sa.longestCommonSubstring(t) << endl;
    
    return 0;
}
Key Features Explained
## Key Features Explained

- **Efficient Substring Checking**
  - Check if a pattern is a substring in O(m) time.
  - Much faster than naive O(n*m) checking for multiple queries.

- **Counting Distinct Substrings**
  - The formula `sum(len[state] - len[link[state]])` counts all distinct substrings.
  - No need to generate all substrings explicitly.

- **Finding Longest Common Substring**
  - Traverse the automaton with the second string.
  - Track the longest matching substring encountered.

- **Compact Representation**
  - The automaton has at most 2n states for a string of length n.
  - More space-efficient than storing all suffixes explicitly.

## When to Use in Contests

- **Multiple Substring Queries**
  - When you need to check many patterns against a fixed text.

- **Distinct Substring Counting**
  - Problems asking for the number of unique substrings.

- **Longest Common Substring Problems**
  - Finding the longest string common to two texts.

- **String Rotation Problems**
  - Finding lexicographically smallest rotation.

- **Pattern Matching**
  - When you need to find all occurrences of a pattern.

## Performance Tips

- **Preprocess Once, Query Many Times**
  - Build the automaton once for your main text.
  - Then answer multiple queries efficiently.

- **Memory Considerations**
  - For large alphabets, use `map<char, int>` for transitions.
  - For small alphabets, arrays provide better performance.

- **Trade-offs**
  - Suffix automata offer faster query times than suffix arrays for some problems.
  - They use more memory than suffix arrays but significantly less than suffix trees.
