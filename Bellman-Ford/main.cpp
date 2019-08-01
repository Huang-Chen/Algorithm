#include<iostream>
#include<climits>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace std;

struct Graph {
	int **cost; //路径长度
	int nodenums;//节点数量
	int *dis;
	int *pre;
	Graph(int n):nodenums(n){
		cost = new int *[n];
		for (int i=0; i < n; i++) {
			cost[i] = new int[n];
		}
		for (int i=0; i < n; i++) {
			for (int j=0; j < n; j++) {
				cost[i][j] = 0;
			}
		}//初始化邻接矩阵表示有向图
		dis = new int[n];
		pre = new int[n];
	};
	int edgenum() {
		int counts = 0;
		for (int i = 0; i < nodenums; i++) 
			for (int j = 0; j < nodenums; j++) {
				if (cost[i][j] != 0)
					counts++;
			}
		return counts;
	}
};
struct Edge {
	char u;
	char v;
	int  e;
};
int index(char c, vector<char> dic) {
	vector<char>::iterator it;
	it = find(dic.begin(), dic.end(), c);
	return  &*it - &dic[0];
}
bool Bellman_Ford(Graph &g,char src,vector<char> dic) {
	for (int i = 0; i < g.nodenums; i++) {
		g.dis[i] = (dic[i] == src ? 0 : INT_MAX);
	}
	for (int k = 0; k < g.nodenums - 1; k++) {
		for (int i = 0; i < g.nodenums; i++) {
			for (int j = 0; j< g.nodenums; j++) {
				if (g.cost[i][j] != 0) {
					if (g.dis[j] > g.dis[i] + g.cost[i][j]) {
						g.dis[j] = g.dis[i] + g.cost[i][j];
						g.pre[j] = i;
					}//松弛
				}
				else
					continue;
			}
		}//遍历所有边
	}
	bool flag = true;
	for (int i = 0; i < g.nodenums; i++) {
		int over = 1;
		for (int j = 0; j < g.nodenums; j++) {
			if (g.cost[i][j] != 0) {
				if (g.dis[j] > g.dis[i] + g.cost[i][j]) {
					flag = false;
					over = 0;
					break;
				}
			}
			else {
				continue;
			}
		}
		if (over) break;
	}//判断是否有负权回路
	return flag;
}
void shortest_path(Graph g,char src,char des,vector<char> dic) {
	int s = index(src, dic);
	int d = index(des, dic);
	if (s == d) {
		cout << src;
	}
	else if (g.pre[d] > dic.size()-1 || g.pre[d] < 0) {
		cout << "无路径从" << src << "到" << des << endl;
	}
	else {
		shortest_path(g, src, dic[g.pre[d]],dic);
		cout << "-"<<des;
	}
}
int main() {
	int nrows;
	char s;
	ifstream bf_file("bf.in", ios::in);
	bf_file >> nrows >> s;

	vector <char> dict{ s };
	vector <char>::iterator it;

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
	}//
	Graph graph(dict.size()); 
	for (int i = 0; i < nrows; i++) {
		vector <char>::iterator it1, it2;
		it1 = find(dict.begin(), dict.end(), edges[i].u);
		int idxi = &*it1 - &dict[0];
		it2 = find(dict.begin(), dict.end(), edges[i].v);
		int idxj = &*it2 - &dict[0];
		graph.cost[idxi][idxj] = edges[i].e;
	} //用存放节点的字典和边来初始化邻接矩阵
	cout << "U201610084 黄琛" << endl;
	for (int i = 0; i < graph.nodenums; i++) {
		if (Bellman_Ford(graph, s, dict)) {
			shortest_path(graph, s, dict[i], dict);
			cout << " "<<graph.dis[i] << endl;
		}
		else {
			cout << "存在负权节点" << endl;
		}
	}
	return 0;
}