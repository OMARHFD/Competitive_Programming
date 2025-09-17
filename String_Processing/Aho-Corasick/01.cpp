/*
Problem:
Hmmmmmm.......... strings again :) Then it must be an easy task for you. Well . . . you are given with
a string S of length not more than 100,000 (only ‘a’-‘z’ and ‘A’-‘Z’). Then follows q (q < 1000) queries
where each query contains a string T of maximum length 1,000 (also contains only ‘a’-‘z’ and ‘A’-‘Z’).
You have to determine whether or not T is a sub-string of S.
Input
First line contains an integer k (k < 10) telling the number of test cases to follow. Each test case begins
with S. It is followed by q. After this line there are q lines each of which has a string T as defined
before.
Output
For each query print ‘y’ if it is a sub-string of S or ‘n’ otherwise followed by a new line. See the sample
output below.
Sample Input
2
abcdefghABCDEFGH
2
abc
abAB
xyz
1
xyz
Sample Output
y
n
y
*/


#include<bits/stdc++.h>
using namespace std;

const int K = 52;

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
    int cases;
    cin >> cases;
    while (cases--) {
        t.clear();
        t.emplace_back();
        string text;
        cin >> text;
        int q;
        cin >> q;
        vector<bool> answers(q, false);
        vector<string> patterns(q);
        for (int i = 0; i < q; i++) {
            cin >> patterns[i];
            add_string(patterns[i], i);
        }
        answers = search_in_text(text, answers);
        for (bool ans : answers) {
            cout << (ans ? "y" : "n") << endl;
        }
    }
    return 0;
}