#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void createFile(const string &filename) {
    ofstream file(filename);
    if (file.is_open()) {
        cout << "File created successfully." << endl;
        file.close();
    } else {
        cout << "Error creating file." << endl;
    }
}

void readFile(const string &filename) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Error reading file." << endl;
    }
}

void writeFile(const string &filename, const string &data) {
    ofstream file(filename, ios::app); // append mode
    if (file.is_open()) {
        file << data << endl;
        cout << "Data written to file successfully." << endl;
        file.close();
    } else {
        cout << "Error writing to file." << endl;
    }
}