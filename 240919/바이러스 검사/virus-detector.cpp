#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

vector<int> store;
int N;

int man, ser;

long long result;

void input() {

	cin >> N;

	for (int i = 0; i < N; i++){
		int num;
		cin >> num;
		store.push_back(num);
	}

	cin >> man >> ser;

}

void solve() {

	for (int i = 0; i < N; i++){

		int now = store[i] - man;
		int res = 1;

		if (now > 0) {
			res = res + now / ser;

			if (now % ser != 0) {
				res += 1;
			}
		}

		result += res;
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	//freopen("sample.txt", "r", stdin);

	input();
	solve();

	cout << result;

	return 0;
}