#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <cwctype>
#include <vector>
#include <codecvt> 

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

    // Имя файла для чтения
    string filename;
    string modified_filename;

    cout << "Enter the file name to read:" << endl;
    cin >> filename;
    cout << "Enter the name of the file where the text will be written:" << endl;
    cin >> modified_filename;

    // Открываем файл в режиме чтения
    wifstream file(filename);
    wofstream modified_file(modified_filename);

    // Устанавливаем локаль для корректной обработки UTF-8
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    modified_file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    // Проверяем, успешно ли открыт файл
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return 1; // Завершаем программу с ошибкой
    }

    // Чтение строк из файла
    wstring line;
    while (getline(file, line)) {
    	wstring word;
    	vector<wstring> words;
    	for (int i = 0; i < line.length(); i++) {
    		if ((char)line[i] == ' ') {
    			words.push_back(word);
    			word = L"";
    		} else {
    			word[0] = towupper(word[0]);
    			word += line[i];
    		}
    	}
    	if (word.length() > 0){
    		word[0] = towupper(word[0]);
    		words.push_back(word);
    	}

    	for (auto i : words) {
    		modified_file << i << ' ';
    	}
    	modified_file << endl;
    }

    // Закрываем файл после использования
    file.close();
    modified_file.close();

    return 0;
}
