// $ g++ -o suffixAutomaton suffixAutomaton.cpp
// $ ./suffixAutomaton
#include <bits/stdc++.h>

using namespace std;

struct state {
	int len, link, firstpos;
	map<char,int> next;
};

const int MAXLEN = 10010;
state st[MAXLEN*2]; // Array of states
int sz, last;

// Suffix tree initialization
void sa_init() {
	st[0].len = 0;
    st[0].link = -1;
    st[0].firstpos = -1;
    sz++;
    last = 0;
}

// Es un DAG de una sola fuente y una sola hoja
// cantidad de endpos = cantidad de apariciones = cantidad de caminos de la clase al nodo terminal
// cantidad de miembros de la clase = st[v].len-st[st[v].link].len (v>0) = caminos del inicio a la clase
// El arbol de los suffix links es el suffix tree de la cadena invertida. La string de la arista link(v)->v son los caracteres que difieren
void sa_extend (char c) {
	int cur = sz++;
	st[cur].len = st[last].len + 1;
    st[cur].firstpos = st[cur].len - 1;
	// en cur agregamos la posicion que estamos extendiendo
	//podria agregar tambien un identificador de las cadenas a las cuales pertenece (si hay varias)
	int p;
	for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link) // modificar esta linea para hacer separadores unicos entre varias cadenas (c=='$')
		st[p].next[c] = cur;
	if (p == -1)
		st[cur].link = 0;
	else {
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len)
			st[cur].link = q;
		else {
			int clone = sz++;
			// no le ponemos la posicion actual a clone sino indirectamente por el link de cur
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

string lcs (string s, string t) {
    sa_init();
    for (int i=0; i<(int)s.length(); ++i)
        sa_extend (s[i]);
   
    int v = 0,  l = 0,
        best = 0,  bestpos = 0;
    for (int i=0; i<(int)t.length(); ++i) {
        while (v && ! st[v].next.count(t[i])) {
            v = st[v].link;
            l = st[v].len;
        }
        if (st[v].next.count(t[i])) {
            v = st[v].next[t[i]];
            ++l;
        }
        if (l > best)
            best = l,  bestpos = i;
    }
    return t.substr (bestpos-best+1, best);
}

/*int main() {
	string s1 = "alsdfkjfjkdsal";
    string s2 = "fdjskalajfkdsla";

    //sa_init();
    cout << lcs(s1, s2) << endl;

	return 0;
}*/

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
    
	//cout << "Hola" << endl;
    string s = "dontcallmebfu";

    string nw = s + s;
    constructSA(nw);
    smallestcyclicshift(s);

	return 0;
}