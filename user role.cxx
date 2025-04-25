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
    string username, password, role;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;
    
    cout << "Enter role (admin/user): ";
    cin >> role;
    
    if (role != "admin" && role != "user") {
        cout << "Invalid role! Defaulting to 'user'.\n";
        role = "user";
    }

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

    users[username] = {{"password", sha256(password)}, {"role", role}};

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
string loginUser(const string &filename) {
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

    if (users.contains(username) && users[username]["password"] == hashedPassword) {
        cout << "Login successful! Welcome " << username << "!\n";
        return users[username]["role"];
    } else {
        cout << "Invalid username or password!\n";
        return "";
    }
}

// Function ya kuonyesha watumiaji (Admin Only)
void viewUsers(const string &filename) {
    json users;
    ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> users;
        inFile.close();
    }

    cout << "\nRegistered Users:\n";
    for (auto &user : users.items()) {
        cout << "Username: " << user.key() << ", Role: " << user.value()["role"] << "\n";
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
            string role = loginUser(filename);
            if (role == "admin") {
                cout << "Admin Access Granted!\n";
                viewUsers(filename);
            } else if (role == "user") {
                cout << "User Access Granted!\n";
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}