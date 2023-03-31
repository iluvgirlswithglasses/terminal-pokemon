
// programmed by Dang Nguyen

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_SIZE = 100;  

void printArray(int arr[][MAX_SIZE], int m, int n) {
    cout << "Array contents:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << (char)arr[i][j] << " "; 
        }
        cout << endl;
    }
}

void readArrayFromTxt(string fileName, int arr[][MAX_SIZE], int& m, int& n) {
    ifstream in(fileName);
    if (!in.is_open()) {
        cout << "Cannot open input file! Error!" << endl;
        return;
    }

    in >> m >> n;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char ch;
            in >> ch;
            arr[i][j] = ch; 
        }
    }

    in.close();
}

void writeArrayToBinary(string fileName, int arr[][MAX_SIZE], int m, int n) {
    ofstream out(fileName, ios::out | ios::binary);
    if (!out.is_open()) {
        cout << "Cannot open output file! Error!" << endl;
        return;
    }

    out.write(reinterpret_cast<const char*>(&m), sizeof(m));
    out.write(reinterpret_cast<const char*>(&n), sizeof(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            out.write(reinterpret_cast<const char*>(&arr[i][j]), sizeof(arr[i][j]));
        }
    }

    out.close();
}

void readArrayFromBinary(string fileName, int arr[][MAX_SIZE], int& m, int& n) {
    ifstream in(fileName, ios::in | ios::binary);
    if (!in.is_open()) {
        cout << "Cannot open input file! Error" << endl;
        return;
    }

    in.read(reinterpret_cast<char*>(&m), sizeof(m));
    in.read(reinterpret_cast<char*>(&n), sizeof(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            in.read(reinterpret_cast<char*>(&arr[i][j]), sizeof(arr[i][j]));
        }
    }

    in.close();
}

int main(int argc, char const* argv[])
{
    int arr[MAX_SIZE][MAX_SIZE];
    int m, n;
    string inf = argv[1], ouf = argv[2];
    readArrayFromTxt(inf, arr, m, n);
    writeArrayToBinary(ouf, arr, m, n);
    return 0;
}
