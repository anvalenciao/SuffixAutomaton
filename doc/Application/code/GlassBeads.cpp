/**
 * $ g++ -o GlassBeads GlassBeads.cpp
 * $ ./GlassBeads < Input.in > Output.out
 */
#include<bits/stdc++.h>

using namespace std;

struct state {
    int len, link;
    map<char, int> next;
};

vector<state> st;
int sz, last;

void sa_init(int size) {
    st.clear();
    st.resize(2 * size);
    st[0].len = 0;
    st[0].link = -1;
    sz = last = 0;
    sz++;
}

void sa_extend (char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1)
        st[cur].link = 0;
    else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len)
            st[cur].link = q;
        else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

void sa(string x) {
    int xsize = x.size();
    sa_init(xsize);
    for(int i = 0; i < xsize; i++) {
        sa_extend(x[i]);
    }
}

int UVa719_GlassBeads(const string S) {
    int at = 0;
    int length = 0;
    int ssize = S.size();
    while(length != ssize) {
        for (auto it : st[at].next) {
            at = it.second;
            length++;
            break;
        }
    }
    return (st[at].len - 1) - ssize + 2LL;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while(N--) {
        string A;
        cin >> A;
        string AA = A + A;
        sa(AA);
        cout << UVa719_GlassBeads(A) << endl;
    }
    return 0;
}