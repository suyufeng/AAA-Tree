#include <bits/stdc++.h>

const int MAXN = 100001;
const int MAXM = 200001;

struct Edge{
	int node, next;
}e[MAXM];

int n, m, t, left, right, s[MAXN], h[MAXN], f[MAXN], d[MAXN], fa[MAXN], w[MAXN], q[MAXN], p[MAXN];

void addEdge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
	t++; e[t] = (Edge){x, h[y]}; h[y] = t;
}

int bfs(int x) {
	static bool v[MAXN];
	std::fill(h + 1, h + n + 1, t = 0);
	for (int i = 1; i <= n; i++) {
		if (f[i]) addEdge(i, f[i]);
	}
	std::fill(v + 1, v + n + 1, false);
	left = right = 0;
	q[++right] = x;
	d[x] = w[x];
	v[x] = true;
	p[x] = 0;
	while (left < right) {
		left++;
		for (int i = h[q[left]]; i; i = e[i].next) {
			if (!v[e[i].node]) {
				v[q[++right] = e[i].node] = true;
				d[q[right]] = d[q[left]] + w[e[i].node];
				p[q[right]] = q[left];
			}
		}
	}
	return q[rand() % (right - left + 1) + left];
}

void dfs(int x) {
	s[x] = w[x];
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == fa[x]) continue;
		fa[e[i].node] = x;
		dfs(e[i].node);
		s[x] += s[e[i].node];
	}
}

void modify(int x, int value) {
	w[x] += value;
	for (int i = h[x]; i; i = e[i].next) {
		if (e[i].node == fa[x]) continue;
		modify(e[i].node, value);
	}
}

int main() {
	long reed;
	srand(reed = time(NULL));
	std::cerr << "Reed = " << reed << std::endl;
	n = 1000, m = 200000;
	FILE *outdat = fopen("forest.input", "w");
	FILE *outans = fopen("forest.answer", "w");
	fprintf(outdat, "%d\n", n);
	for (int i = 1; i <= n; i++) {
		fprintf(outdat, "%d%c", w[i] = rand() % 100, " \n"[i == n]);
	}
	for (int i = 1; i <= m; i++) {
		int op = rand() % 5;
		if (op == 3) {
			i --;
			continue;
		}
		if (op == 4) {
			int x = rand() % (n - 1) + 2;
			int y = rand() % (x - 1) + 1;
			if (f[x]) fprintf(outdat, "cut %d %d\n", x, f[x]);
			fprintf(outdat, "link %d %d\n", x, f[x] = y);
		} else if (op == 2) {
			int x = rand() % n + 1, y;
			fprintf(outdat, "queryChain %d %d\n", x, y = bfs(x));
			fprintf(outans, "%d\n", d[y]);
		} else if (op == 1) {
			int x = rand() % n + 1, y;
			fprintf(outdat, "querySubtree %d %d\n", x, y = bfs(x));
			fa[x] = 0;
			dfs(x);
			fprintf(outans, "%d\n", s[y]);
		} else if (op == 0) {
			int x = rand() % n + 1, y, value;
			fprintf(outdat, "modifyChain %d %d %d\n", x, y = bfs(x), value = rand() % 100);
			for (int j = y; j; j = p[j]) {
				w[j] += value;
			}
		} 
	}
	return 0;
}
