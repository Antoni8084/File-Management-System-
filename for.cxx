#include <iostream>
#include <fstream>
#include <string>

void addRecord(const std::string &filename, const std::string &data) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << data << std::endl;
        file.close();
        std::cout << "Data added successfully!\n";
    } else {
        std::cout << "Error opening file!\n";
    }
}

void readRecords(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "Error reading file!\n";
    }
}

void searchRecord(const std::string &filename, const std::string &keyword) {
    std::ifstream file(filename);
    std::string line;
    bool found = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find(keyword) != std::string::npos) {
                std::cout << "Found: " << line << std::endl;
                found = true;
            }
        }
        file.close();

        if (!found) {
            std::cout << "No matching record found.\n";
        }
    } else {
        std::cout << "Error opening file!\n";
    }
}

int main() {
    std::string filename = "records.txt";
    std::string input, searchKey;
    int choice;

    while (true) {
        std::cout << "\n1. Add Record\n2. Read Records\n3. Search Record\n4. Exit\nChoose: ";
        std::cin >> choice;
        std::cin.ignore();  

        if (choice == 1) {
            std::cout << "Enter text to save: ";
            std::getline(std::cin, input);
            addRecord(filename, input);
        } else if (choice == 2) {
            std::cout << "\nSaved records:\n";
            readRecords(filename);
        } else if (choice == 3) {
            std::cout << "Enter keyword to search: ";
            std::getline(std::cin, searchKey);
            searchRecord(filename, searchKey);
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}