/*
AHO CORASICK

problem:
You are given a string of length n and a dictionary containing k words. In how many ways can you create the string using the words?
Input
The first input line has a string containing n characters between a–z.
The second line has an integer k: the number of words in the dictionary.
Finally there are k lines describing the words. Each word is unique and consists of characters a–z.
Output
Print the number of ways modulo 10^9+7.
Constraints

1 \le n \le 5000
1 \le k \le 10^5
the total length of the words is at most 10^6

Example
Input:
ababc
4
ab
abab
c
cb

Output:
2

Explanation: The possible ways are ab+ab+c and abab+c.*/



#include<bits/stdc++.h>
using namespace std;

const int K = 52;
const long long MODULO = 1000000007LL;
int getIndex(char ch) {
    if ('a' <= ch && ch <= 'z') return ch - 'a';
    else return 26 + (ch - 'A');
}

struct Vertex {
    int next[K];
    vector<int> output;
    int p = -1;
    char pch;
    int link = -1;
    int go[K];
    int exit_link = -1;

    Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

vector<Vertex> t(1);

void add_string(const string &s, int id) {
    int v = 0;
    for (char ch : s) {
        int c = getIndex(ch);
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].output.push_back(id);
}

int go(int v, char ch);

int get_link(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0)
            t[v].link = 0;
        else
            t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}

int go(int v, char ch) {
    int c = getIndex(ch);
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = (v == 0) ? 0 : go(get_link(v), ch);
    }
    return t[v].go[c];
}

int get_exit_link(int v) {
    if (t[v].exit_link == -1) {
        int u = get_link(v);
        if (u == 0) {
            t[v].exit_link = 0;
        } else if (!t[u].output.empty()) {
            t[v].exit_link = u;
        } else {
            t[v].exit_link = get_exit_link(u);
        }
    }
    return t[v].exit_link;
}

vector<bool> search_in_text(const string &text, vector<bool> answers) {
    int v = 0;
    for (size_t i = 0; i < text.size(); i++) {
        v = go(v, text[i]);
        int u = v;
        while (u != 0) {
            for (int id : t[u].output) {
                answers[id] = true;
            }
            u = get_exit_link(u);
        }
    }
    return answers;
}

int main() {
    string S;
    int n ;
    cin>>S;
    cin>>n;
    vector<string> pats (n);
    int nbar = 0;
    for (int i = 0; i < n; ++i) {
        cin >> pats[i];
        add_string(pats[i], i);
    }
    vector <int> anss(S.size() +1 );
    int v = 0;
    anss [0] = 1;
    for (size_t i = 1; i < S.size()+1; i++) {
        v = go(v, S[i-1]);
        int u = v;
        while (u != 0) {
            for (int id : t[u].output) {
                anss[i] = (anss[i] + anss[i - pats[id].size()]) % MODULO;
            }
            u = get_exit_link(u);
        }
    }

    cout<<anss[S.size()];
    return 0;
}