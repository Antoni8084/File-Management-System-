#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <openssl/sha.h>  // Library ya SHA-256 hashing

using json = nlohmann::json;
using namespace std;

// Function ya kubadilisha password kuwa hash (SHA-256)
string sha256(const string &password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password.c_str(), password.length(), hash);
    
    string hashedPassword;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", hash[i]);
        hashedPassword += buffer;
    }
    
    return hashedPassword;
}

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

    users[username] = sha256(password);  // Hash password

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

    string hashedPassword = sha256(password);

    if (users.contains(username) && users[username] == hashedPassword) {
        cout << "Login successful! Welcome " << username << "!\n";
        return true;
    } else {
        cout << "Invalid username or password!\n";
        return false;
    }
}

// Function ya kubadilisha nenosiri
void resetPassword(const string &filename) {
    string username, newPassword;
    cout << "Enter your username: ";
    cin >> username;

    json users;
    ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> users;
        inFile.close();
    }

    if (!users.contains(username)) {
        cout << "User not found! Please register first.\n";
        return;
    }

    cout << "Enter new password: ";
    cin >> newPassword;
    users[username] = sha256(newPassword);  // Hash nenosiri jipya

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << users.dump(4);
        outFile.close();
        cout << "Password reset successfully!\n";
    } else {
        cout << "Error updating password!\n";
    }
}

int main() {
    string filename = "users.json";
    int choice;

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Reset Password\n4. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            registerUser(filename);
        } else if (choice == 2) {
            if (loginUser(filename)) {
                cout << "Access granted!\n";
                break; // Ondoka baada ya login kufanikiwa
            }
        } else if (choice == 3) {
            resetPassword(filename);
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}