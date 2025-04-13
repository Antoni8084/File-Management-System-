#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function ya kujiandikisha (Register User)
void registerUser(const string &filename) {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;

    json users;
    ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> users;
        inFile.close();
    }

    if (users.contains(username)) {
        cout << "User already exists! Try another username.\n";
        return;
    }

    users[username] = password;

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << users.dump(4);
        outFile.close();
        cout << "User registered successfully!\n";
    } else {
        cout << "Error saving user data!\n";
    }
}

// Function ya kuingia kwenye mfumo (Login User)
bool loginUser(const string &filename) {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    json users;
    ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> users;
        inFile.close();
    }

    if (users.contains(username) && users[username] == password) {
        cout << "Login successful! Welcome " << username << "!\n";
        return true;
    } else {
        cout << "Invalid username or password!\n";
        return false;
    }
}

int main() {
    string filename = "users.json";
    int choice;

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            registerUser(filename);
        } else if (choice == 2) {
            if (loginUser(filename)) {
                cout << "Access granted!\n";
                break; // Ondoka baada ya login kufanikiwa
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}