#include <bits/stdc++.h>

const int MAXN = 100001;
const int MAXM = 200001;

int n, m, t, h[MAXN], f[MAXN], d[MAXN], w[MAXN], s[MAXN], p[MAXN];
std::vector<int> g[MAXN];

int bfs(int x) {
	static bool v[MAXN];
	static int q[MAXN];
	int left = 0, right = 0, ret = 0;
	d[x] = w[x];
	p[x] = 0;
	std::fill(v + 1, v + n + 1, false);
	v[q[++right] = x] = true;
	while (left < right) {
		left++;
		ret += w[q[left]];
		for (auto son : g[q[left]]) {
			if (!v[son]) {
				v[q[++right] = son] = true;
				d[q[right]] = d[q[left]] + w[son];
				p[q[right]] = q[left];
			}
		}
	}
	return ret;
}

void dfs(int x, int fa) {
	s[x] = w[x];
	for (auto son : g[x]) {
		if (son == fa) continue;
		f[son] = x;
		dfs(son, x);
		s[x] += s[son];
	}
}

void modify(int x, int value) {
	w[x] += value;
	for (auto son : g[x]) {
		if (son == f[x]) continue;
		modify(son, value);
	}
}

int main() {
	srand(time(NULL));
	freopen("forest.input", "r", stdin);
	freopen("forest.standard", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", w + i);
	}
	int cnt = 0;
	while (true) {
		char op[20];
		if (scanf("%s", op) != 1) {
			break;
		}
		if (!strcmp(op, "link")) {
			int x, y;
			scanf("%d%d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		} else if (!strcmp(op, "cut")) {
			int x, y;
			scanf("%d%d", &x, &y);
			for (auto it = g[x].begin(); it != g[x].end(); ++it) {
				if (*it == y) {
					g[x].erase(it);
					break;
				}
			}
			for (auto it = g[y].begin(); it != g[y].end(); ++it) {
				if (*it == x) {
					g[y].erase(it);
					break;
				}
			}
		} else if (!strcmp(op, "queryChain")) {
			int x, y;
			scanf("%d%d", &x, &y);
			bfs(x);
			printf("%d\n", d[y]);
		} else if (!strcmp(op, "querySubtree")) {
			int x, y;
			scanf("%d%d", &x, &y);
			dfs(x, 0);
			printf("%d\n", s[y]);
		} else if (!strcmp(op, "modifyChain")) {
			int x, y, v;
			scanf("%d%d%d", &x, &y, &v);
			bfs(x);
			for (int j = y; j; j = p[j]) {
				w[j] += v;
			}
		} else if (!strcmp(op, "modifySubtree")) {
			int x, y, v;
			scanf("%d%d%d", &x, &y, &v);
			f[x] = 0;
			dfs(x, 0);
			modify(y, v);
		}
	}
	return 0;
}
