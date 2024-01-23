#include <iostream>
#include <fstream>
#include <sstream>
#include <string>     // для std::getline
#include <cmath>
 
using namespace std;

int main()
{
    string file_name;
    string line;
    string out = "";

    cin >> file_name;

    ifstream in(file_name); // окрываем файл для чтения

    if (in.is_open()) {
        getline(in, line);

        int a = 0;
        while(a != -1) {
            a = line.find(" ");
            string num_str;
            if (a == -1){
                num_str = line.substr(0, line.length());
            } else {
                num_str = line.substr(0, a);
            }

            stringstream ss;
            ss << round(pow(stod(num_str), 2) * 100) / 100.0;
            out += ss.str() + " ";
            line = line.substr(a + 1);
        }

    } else {
        cout << "file " << file_name << " doesn't exists." << endl;
    }

    in.close();
    if (out.length() != 0) {
        ofstream f;          
        f.open(file_name);      
        if (f.is_open()) {
            f << out << endl;
        }
        f.close(); 
        cout << "File has been written" << endl;
    }

    return 0;
}