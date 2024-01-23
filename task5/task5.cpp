#include <iostream>
#include <string>

using namespace std;

int main() {
	int k;
	cout <<  "Enter the length of field side" << endl;
	cin >> k;

	int **field = new int* [k];
	for (int i = 0; i < k; i++) {
		int *a = new int[k];
		for (int j = 0; j < k; j++) {
			a[j] = 1;
		}
		field[i] = a;
	}

	for (int i = 1; i < k; i++) {
		for (int j = 1; j < k; j++) {
			field[i][j] = field[i - 1][j] + field[i][j - 1];
		}
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			cout << field[i][j] << '\t';
		}
		cout << endl;
	}
}