#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<algorithm>
using namespace std;

#define Min(a,b) ((a)>(b)?(b):(a))

struct Graph {
	int **cost; //路径长度
	int nodenums;//节点数量
	Graph(int n) :nodenums(n) {
		cost = new int *[n];
		for (int i = 0; i < n; i++) {
			cost[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j)
					cost[i][j] = 0;
				else
					cost[i][j] = INT_MAX;
			}
		}//初始化邻接矩阵表示有向图
	};
	Graph() {};
};
struct Graphs {
	Graph d;
	Graph p;
};
struct Edge {
	int u;
	int v;
	int e;
};
Graphs Floyd_Warshall(Graph g) {
	int n = g.nodenums;
	Graph D = g;
	Graph Pi = Graph(n);
	int a, b;
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (k == 0) {
					if (i == j || g.cost[i][j] == INT_MAX)
						Pi.cost[i][j] = INT_MAX;
					else
						Pi.cost[i][j] = i;
				}
				else {
					if (D.cost[i][k] == INT_MAX || D.cost[k][j] == INT_MAX)
						b = INT_MAX;
					if (D.cost[i][j] > b) {
						Pi.cost[i][j] = Pi.cost[k][j];
					}
					else
						Pi.cost[i][j] = Pi.cost[i][j];
				}
				if (D.cost[i][k] == INT_MAX || D.cost[k][j] == INT_MAX)
					b = INT_MAX;
				else
					b = D.cost[i][k] + D.cost[k][j];
				a = D.cost[i][j];
				D.cost[i][j] = Min(a, b);
			}
		}
	}
	Graphs res{ D,Pi };
	return res;
}
void printpath(Graph p, int i, int j) {
	if (i == j) cout << i + 1;
	else if (j<0||j>4) {
		cout << "无最短路径" << endl;
	}
	else {
		printpath(p, i, p.cost[i][j]);
		cout << "-" << j + 1;
	}
}
int main() {
	int nrows;
	ifstream bf_file("fw.in", ios::in);
	bf_file >> nrows;

	vector <int> dict;
	vector <int>::iterator it;

	Edge *edges = new Edge[nrows];
	for (int i = 0; i < nrows; i++) {
		bf_file >> edges[i].u >> edges[i].v >> edges[i].e;
		it = find(dict.begin(), dict.end(), edges[i].u);
		if (it == dict.end()) {
			dict.push_back(edges[i].u);
		}
		it = find(dict.begin(), dict.end(), edges[i].v);
		if (it == dict.end()) {
			dict.push_back(edges[i].v);
		}
	}
	sort(dict.begin(),dict.end());
	Graph graph(dict.size());
	for (int i = 0; i < nrows; i++) {
		graph.cost[edges[i].u-1][edges[i].v-1] = edges[i].e;
	}
	Graph graphd = Floyd_Warshall(graph).d;
	Graph graphp = Floyd_Warshall(graph).p;
	cout << "U201610084 黄琛" << endl;
	for (int i = 0; i < graph.nodenums; i++) {
		//cout << "从节点" << i + 1 << "其他节点的最短路径是:" << endl;
		for (int j = 0; j < graph.nodenums ; j++) {
			printpath(graphp, i, j);
			if (i == j)
				cout <<"\t"<< 0 << endl;
			else
				cout <<"\t"<<graphd.cost[i][j]<<endl;
		}
	}
}