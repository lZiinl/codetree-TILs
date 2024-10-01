#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

int gear_num;
int dir;
char gear[4][8];
int K;

void input() {
	for (int i = 0; i < 4; i++){
		cin >> gear[i];
	}
	cin >> K;
}

void rotate() {

	int ndir = dir;
	for (int i = gear_num-1; i >= 0; i--)
	{
		//1 = cw
		if (ndir == 1) {
			char temp = gear[i][7];
			gear[i][7] = gear[i][6];
			gear[i][6] = gear[i][5];
			gear[i][5] = gear[i][4];
			gear[i][4] = gear[i][3];
			gear[i][3] = gear[i][2];
			gear[i][2] = gear[i][1];
			gear[i][1] = gear[i][0];
			gear[i][0] = temp;

			if (i > 0 && gear[i][7] == gear[i - 1][2]) {
				break;
			}
			ndir *= -1;
			continue;
		}

		//-1 = ccw
		if (ndir == -1) {
			char temp = gear[i][0];
			gear[i][0] = gear[i][1];
			gear[i][1] = gear[i][2];
			gear[i][2] = gear[i][3];
			gear[i][3] = gear[i][4];
			gear[i][4] = gear[i][5];
			gear[i][5] = gear[i][6];
			gear[i][6] = gear[i][7];
			gear[i][7] = temp;

			if (i > 0 && gear[i][5] == gear[i - 1][2]) {
				break;
			}
			ndir *= -1;
		}
	}

	for (int i = gear_num; i < 4; i++)
	{
		//1 = cw
		if (dir == 1) {
			if ( gear[i][6] == gear[i - 1][3]) {
				break;
			}

			char temp = gear[i][0];
			gear[i][0] = gear[i][1];
			gear[i][1] = gear[i][2];
			gear[i][2] = gear[i][3];
			gear[i][3] = gear[i][4];
			gear[i][4] = gear[i][5];
			gear[i][5] = gear[i][6];
			gear[i][6] = gear[i][7];
			gear[i][7] = temp;
			dir = -1;
			continue;
		}

		//-1 = ccw
		if (dir == -1) {
			if (gear[i][6] == gear[i - 1][1]) {
				break;
			}

			char temp = gear[i][7];
			gear[i][7] = gear[i][6];
			gear[i][6] = gear[i][5];
			gear[i][5] = gear[i][4];
			gear[i][4] = gear[i][3];
			gear[i][3] = gear[i][2];
			gear[i][2] = gear[i][1];
			gear[i][1] = gear[i][0];
			gear[i][0] = temp;
			dir = 1;
		}
	}
}

int main() {

	//freopen("sample.txt", "r", stdin);
	input();
	
	for (int i = 0; i < K; i++){
		cin >> gear_num >> dir;
		rotate();
	}

	int sum = 0;
	int cnt = 1;

	for (int j = 0; j < 4; j++){
		if (gear[j][0] == '1') {
			sum = sum + cnt;
		}

		cnt = cnt * 2;
	}

	cout << sum;

	return 0;
}