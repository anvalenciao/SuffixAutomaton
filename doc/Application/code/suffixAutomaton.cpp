// $ g++ -o suffixAutomaton suffixAutomaton.cpp
// $ ./suffixAutomaton
#include <bits/stdc++.h>

using namespace std;

struct state {
	int len, link, firstpos;
	map<char,int> next;
};

const int MAXLEN = 10010;
state st[MAXLEN*2];
int sz, last;

void sa_init() {
	st[0].len = 0;
    st[0].link = -1;
    st[0].firstpos = -1;
    sz++;
    last = 0;
}

void sa_extend (char c) {
	int cur = sz++;
	st[cur].len = st[last].len + 1;
    st[cur].firstpos = st[cur].len - 1;
	int p;
	for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
		st[p].next[c] = cur;
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
            st[clone].firstpos = st[q].firstpos;
			for (; p!=-1 && st[p].next.count(c) && st[p].next[c]==q; p=st[p].link)
				st[p].next[c] = clone;
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}

void constructSA(string ss) {
    sa_init();
    for(int i = 0; i < ss.size(); i++) {
        sa_extend(ss[i]);
    }
}

void smallestcyclicshift(const string ss) {
    int at = 0;
    string anss;
    int length = 0;
    while(length != ss.size()) {
        for (auto it : st[at].next) {
            anss.push_back(it.first);
            at = it.second;
            length++;
            break;
        }
    }
    cout << st[at].firstpos - ss.size() + 2LL << "\n";
}

int main() {
    string s = "dontcallmebfu";
    string nw = s + s;
    constructSA(nw);
    smallestcyclicshift(s);
	return 0;
}