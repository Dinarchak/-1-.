#include <iostream>
#include <string>
using namespace std;

string get_addendum_str(string &s) {
	string var;
	int next_sign_pos;
	int first_minus = s.find("+", 1), first_plus = s.find("-", 1);
	if (first_minus != -1 && first_plus != -1)
		next_sign_pos = min(first_minus, first_plus);
	else if (first_minus == -1 && first_plus == -1) {
		next_sign_pos = s.length();
	} else {
		next_sign_pos = max(first_minus, first_plus);
	}

	var = s.substr(0, next_sign_pos);
	s = s.substr(next_sign_pos, string::npos);

	return var;
}

int main() {
	while (true) {
		string command;
		int s = 0;
		bool correct_input = true;
		cin >> command;

		if (command[0] != '-' && command[0] != '+') {
			command = "+" + command;
		}

		while (command.length() > 1 && correct_input) {
			string addenum_str = get_addendum_str(command);
			try {
				if (addenum_str[0] == '-')
					s -= stoi(addenum_str.substr(1, string::npos));
				else
					s += stoi(addenum_str.substr(1, string::npos));
			} catch(std::exception) {
				cout << "Incorrect input" << endl; 
				correct_input = false;
			}
		}

		if (correct_input) {
			cout << "result equal " << s << endl;
			break;
		}
	}

	return 0;
}