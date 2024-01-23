#include <iostream>
#include <utility>
#include <ctime>
#include <math.h>

using namespace std;

pair<double, double> random_point() {
	double x = (rand() % 10000) * 0.4 / 10000.0;
	double y = (rand() % 10000) * 0.22 / 10000.0;

	return make_pair(x, y);
}

int main() {
	srand(time(0));
	double total_s = 0.4 * 0.22;
	int measurements_count = 10000000;
	int points_in_area = 0;

	for (int i = 0; i < measurements_count; i++) {
		pair<double, double> point = random_point();

		if (!(point.first / 3 + 20 * pow(point.first, 6.0) < point.second)) {
			points_in_area++;
		}
	}

	cout << "Area is " << (total_s * points_in_area) / measurements_count << endl;

	return 0;
}