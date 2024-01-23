#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <string>
#include <ctime>

using namespace std;

const int FPS = 10;
const int WIDTH = 104;
const int HEIGHT = 34;
const char APPLE_SYMBOL = '@';

void drawframe(vector<vector<char>> &frame) {
	string s = "";

	for (auto line : frame) {
 		for(auto pixel : line) {
 			s +=  pixel;
 		}
 	}
 	cout << s;
}

int mod(int a, int b) {
	// a % b
	if (a >= 0) {
		return a % b;
	}
	
	return b - ((-a) % b);
}

class Snake {
private:
	vector<pair<int, int>> body;
	pair<int, int> tail;
	int length;

	void update_tail() {
		this->tail = this->body.back();
	}
public:

	char symbol = 'O';

	Snake(int len, pair<int, int> head_pos) {
		for (int i = 0; i < len; i++) {
			// тело змеи должно помещатся в пол-экрана
			this->body.push_back(make_pair(head_pos.first - i, head_pos.second));
		}
		this->length = len;
		update_tail();
	}

	void move(pair<int, int> dir) {
		for (int i = this->body.size() - 1; i > 0; --i) {
			this->body[i] = this->body[i - 1];
		}

		this->body[0] = make_pair(mod(this->body[0].first + dir.first, WIDTH), mod(this->body[0].second + dir.second, HEIGHT));
		update_tail();
	}

	void grow() {
		pair<int, int> grow_dir;
		pair<int, int> new_block;

		grow_dir.first = this->body[this->length - 2].first - this->tail.first;
		grow_dir.second = this->body[this->length - 2].second - this->tail.second;

		new_block.first = this->tail.first + grow_dir.first;
		new_block.second = this->tail.second + grow_dir.second;

		this->body.push_back(new_block);
		update_tail();
		this->length++;
	}

	pair<int, int> at(int i) {
		return this->body[i];
	}

	bool is_dead() {
		pair<int, int> head = this->body[0];
		for (int i = 1; i < this->length; ++i) {
			if (this->body[i] == head)
				return true;
		}

		return false;
	}

	int get_length() {
		return this->length;
	}

	pair<int, int> get_tail() {
		return this->tail;
	}
};

void grow_apple(pair<int, int> &apple, Snake snake) {
	pair<int, int> a;
	bool on_snake = true;
	while(on_snake) {

		on_snake = false;
		a = make_pair(rand() % WIDTH, rand() % HEIGHT);

		for (int i = 0; i < snake.get_length(); i++) {
			on_snake = on_snake || snake.at(i) == a;
		}
	}

	apple = a;
}

int main() {

	// HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);
	// COORD bufferSize = {100, 40};
	// SetConsoleScreenBufferSize(hWnd, bufferSize);

	srand(time(0));

	HWND hWindowConsole = GetConsoleWindow();
	RECT r;
	GetWindowRect(hWindowConsole, &r); //stores the console's current dimensions
	MoveWindow(hWindowConsole, r.left, r.top, 800, 600, TRUE);

	Snake snake = Snake(2, make_pair(51, 15));
	pair<int, int> dir = make_pair(1, 0);
	bool pause = false;

	pair<int, int> apple;
	grow_apple(apple, snake);

	vector<vector<char>> frame(HEIGHT, vector<char>(WIDTH, ' '));


	while(!snake.is_dead()) {

		if (kbhit() != 0) {
			char c = getch();

			if (c == 'w' && dir.second != 1 && !pause) {
				dir = make_pair(0, -1);
			} else if (c == 'd' && dir.first != -1 && !pause) {
				dir = make_pair(1, 0);
			} else if (c == 'a' && dir.first != 1 && !pause) {
				dir = make_pair(-1, 0);
			} else if(c == 's' && dir.second != -1 && !pause) {
				dir = make_pair(0, 1);
			} else if (c == 27) {
				break;
			} else if (c == 32) {
				pause = !pause;

				for (int i = 0; i < WIDTH; ++i) {
					for (int j = 0; j < HEIGHT; ++j) {
						frame[j][i] = ' ';
					}
				}

				if (pause) {
					string pause = "PAUSE";
					for (int i = 0; i < pause.length(); ++i) {
						frame[HEIGHT / 2 - 1][WIDTH / 2 - 2 + i] = pause[i];
					}
				}
			}
		}

		if (!pause) {
			if (snake.at(0) == apple) {
				snake.grow();
				grow_apple(apple, snake);
			}

			frame[snake.get_tail().second][snake.get_tail().first] = ' ';
			snake.move(dir);

			for (int i = 0; i < snake.get_length(); i++) {
				pair<int, int> p = snake.at(i);
				frame[p.second][p.first] = snake.symbol;
			}

			frame[apple.second][apple.first] = APPLE_SYMBOL;

			Sleep(1000/FPS);
		}

		drawframe(frame);
	}

	return 0;
}