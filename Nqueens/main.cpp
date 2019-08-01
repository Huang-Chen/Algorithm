#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<iomanip>
using namespace std;
struct Ans {
	int n;//解的大小
	int *ele;//解元素
	Ans(int m) :n(m), ele(new int[m]) {};
};//解向量的数据结构

bool place(int k,int *x) {
	int i = 0;
	while (i < k) {
		if (x[i] == x[k] || abs(x[i] - x[k]) == abs(i - k)) {
			return false;
		}
		i = i + 1;
	}
	return true;
}//判断皇后k是否可以放在第k行第x(k)列

vector<Ans> nqueen(int n) {
	int *x = new int[n];
	int k = 0;
	x[0] = 0;
	vector<Ans> ans;
	while (k >= 0) {
		x[k] = x[k] + 1;
		while (x[k] <= n && !place(k,x)) {
			x[k] = x[k] + 1;
		}
		if (x[k] <= n) {
			if (k == n-1) {
				Ans a(n);
				for (int i = 0; i < n; i++) {
					a.ele[i] = x[i];
				}
				ans.push_back(a);
			}
			else {
				k = k + 1;
				x[k] = 0;
			}
		}
		else {
			k = k - 1;
		}
	}
	return ans;
}
int main() {
	int q_sum;//测试用例个数
	ifstream file("queen.in", ios::in); //读取输入文件
	file >> q_sum;
	int *queens = new int[q_sum];
	ofstream outfile("queen_U201610084.out",ios::trunc);
	for (int i = 0; i < q_sum; i++) {
		file >> queens[i];
		vector<Ans> answer=nqueen(queens[i]);
		outfile << std::left << setw(2) << queens[i]
			<< answer.size() << endl;
		for (auto e : answer) {
			for (int i = 0; i < e.n; i++) {
				outfile <<std::left<<setw(2)<< e.ele[i] << "  ";
			}
			outfile << endl;
		}
	}
}