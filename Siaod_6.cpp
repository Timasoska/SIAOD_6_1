#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Структура для представления рёбер
struct edge {
	int a, b, len;
	bool operator<(const edge& other) {
		return len < other.len;
	}
};

vector<int> p, rk;  //Система непересекающихся множеств (DSU)

void init_dsu(int n) { //Эта функция инициализирует DSU для n элементов, задавая начальные значения массивов p и rk.
	p.resize(n);
	rk.resize(n);
	for (int i = 0; i < n; i++) {
		p[i] = i;
		rk[i] = 1;
	}
}

int get_root(int v) { //Эта функция используется для нахождения корня множества, которому принадлежит элемент v. Она реализует операцию поиска с оптимизацией путей.
	if (p[v] == v) {
		return v;
	}
	else {
		return p[v] = get_root(p[v]); // На выходе из рекурсии переподвешиваем v
	}
}

bool merge(int a, int b) { //функция объединяет два множества, к которым принадлежат элементы a и b.
	int ra = get_root(a), rb = get_root(b);
	if (ra == rb) {
		return false;
	}
	else {
		if (rk[ra] < rk[rb]) {
			p[ra] = rb;
		}
		else if (rk[rb] < rk[ra]) {
			p[rb] = ra;
		}
		else {
			p[ra] = rb;
			rk[rb]++;
		}
		return true;
	}
}

void printMST(const vector<edge>& minimumSpanningTree) { //выводит на экран рёбра минимального остовного дерева (результат алгоритма Крускала) вместе с их весами.
	cout << "Minimum Spanning Tree Edges:\n";
	for (const edge& e : minimumSpanningTree) {
		cout << e.a << " - " << e.b << " (Weight: " << e.len << ")\n";
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	vector<edge> edges;
	int n, m; // Изменение переменных n и m

	cout << "Enter the number of vertices and edges: ";
	cin >> n >> m;

	init_dsu(n);

	for (int i = 0; i < m; i++) {
		int u, v, weight;
		cout << "Enter edge " << i + 1 << " (u v weight): ";
		cin >> u >> v >> weight;
		edges.push_back({ u, v, weight });
	}

	sort(edges.begin(), edges.end());

	vector<edge> minimumSpanningTree;
	int totalWeight = 0;

	for (const edge& e : edges) {
		if (merge(e.a, e.b)) {
			minimumSpanningTree.push_back(e);
			totalWeight += e.len;
		}
	}

	cout << "Total weight of Minimum Spanning Tree: " << totalWeight << endl;

	printMST(minimumSpanningTree);
}