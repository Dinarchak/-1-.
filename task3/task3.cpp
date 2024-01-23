#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;
const pair<int, int> ZERO = make_pair(0, 0);

void build_paths(vector<pair<int, int>> &way, vector<vector<int>> &field, vector<vector<vector<int>>> &dp, int s) {
	int curr_s = s;
	while(way.back() != ZERO) {
		pair<int, int> curr_plate = way.back();
		if (curr_plate.second > 0) {
			pair<int, int> left_plate = make_pair(curr_plate.first, curr_plate.second - 1);
			vector<int> left_plate_sums = dp[curr_plate.first][curr_plate.second - 1];
			if (find(left_plate_sums.begin(), left_plate_sums.end(), curr_s - field[curr_plate.first][curr_plate.second]) != left_plate_sums.end()) {
				way.push_back(left_plate);
				curr_s -= field[curr_plate.first][curr_plate.second];
				continue;
			}
		}

		if (curr_plate.first > 0) {
			pair<int, int> upper_plate = make_pair(curr_plate.first - 1, curr_plate.second);
			vector<int> upper_plate_sums = dp[curr_plate.first - 1][curr_plate.second];
			if (find(upper_plate_sums.begin(), upper_plate_sums.end(), curr_s - field[curr_plate.first][curr_plate.second]) != upper_plate_sums.end()) {
				way.push_back(upper_plate);
				curr_s -= field[curr_plate.first][curr_plate.second];
			}
		}
	}
}

// записать все возможные суммы при ходе из previus_plate в current_plate
void get_available_sums(vector<int> previus_plate, vector<int> &current_plate, int cost) {
	for(auto i : previus_plate) {
		current_plate.push_back(cost + i);
	}
}

// вычислить возможную сумму на каждой из клеток
void bfs(vector<vector<vector<int>>> &dp, vector<vector<int>> field, int k) {
	vector<vector<bool>> visited(k, vector<bool>(k, false));
	queue<pair<int, int>> q;
	visited[0][0] = true;
	q.push(make_pair(0, 0));
	while (!q.empty()) {
		pair<int, int> v = q.front();
		q.pop();

		// все возможные суммы при ходе сверху
		if (v.first > 0) {
			get_available_sums(
				dp[v.first - 1][v.second], 
				dp[v.first][v.second], 
				field[v.first][v.second]);
		}

		// все возможные суммы при ходе слева
		if (v.second > 0) {
			get_available_sums(
				dp[v.first][v.second - 1], 
				dp[v.first][v.second], 
				field[v.first][v.second]);
		}

		// добавление в очередь следующих клеток
		for (int i = 0; i < 2; i++) {
			if (v.first + i < k && 
				v.second + (1 + i) % 2 < k && 
				!visited[v.first + i][v.second + (1 + i) % 2]) 
			{
				q.push(make_pair(v.first + i, v.second + (1 + i) % 2));
				visited[v.first + i][v.second + (1 + i) % 2] = true;
			}
		}
	}
}

int main() {
	srand(time(0));

	int k;
	cout <<  "Enter the length of field side" << endl;
	cin >> k;

	// заполнение поля
	vector<vector<int>> field(k, vector<int>(k, 0));
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++ ) {
			field[i][j] = rand() % 10;
		}
	}

	vector<vector<vector<int>>> dp(k, vector<vector<int>>(k, vector<int>(0)));
	dp[0][0].push_back(field[0][0]);
	bfs(dp, field, k);

	sort(dp[k - 1][k - 1].begin(), dp[k - 1][k - 1].end());
	vector<int> sums_set(1, dp[k - 1][k - 1][0]);
	for (int i = 1; i < dp[k - 1][k - 1].size(); ++i) {
		if (sums_set.back() != dp[k - 1][k - 1][i]) {
			sums_set.push_back(dp[k - 1][k - 1][i]);
		}
	}

	for (auto i : field) {
		for (auto j : i) {
			cout << j << ' ';
		}
		cout << endl;
	}
	cout << "available sums in (" << k - 1 << ", " << k - 1 << ')' << endl;
	for (int i = 0; i < sums_set.size(); ++i) {
		cout << sums_set[i] << '\t';
	}
	cout << endl;

	int it = 0;
	while(it < sums_set.size()) {

		vector<pair<int, int>> way(1, make_pair(k - 1, k - 1));
		build_paths(way, field, dp, sums_set[it]);

		for (int i = way.size() - 1; i > 0; --i) {
			cout << '(' << way[i].second << ", " << way[i].first << ") -> ";
		}
		cout << '(' << way[0].second << ", " << way[0].first << ")\tsum: " << sums_set[it] << endl;

		it++;
	}

	return 0;
}