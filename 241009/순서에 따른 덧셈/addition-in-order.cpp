#define _CRT_SERCURE_NO_WARNINGS
#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N;
vector<int>num;

void input() {
	cin >> N;

	for (int i = 0; i < N; i++){
		int temp;
		cin >> temp;
		num.push_back(temp);
	}

	sort(num.begin(), num.end(), greater<>());
}

void solve() {

	long long int result = 0;

	for (int i = 0; i < N; i++){
		int sum = num[i] - i;

		if (sum > 0) {
			result += sum;
		}
	}

	cout << result;
}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	solve();

	return 0;
}