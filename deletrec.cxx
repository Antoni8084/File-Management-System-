#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <nlohmann/json.hpp>  // JSON Library

using json = nlohmann::json;

void addRecord(const std::string &filename, const std::string &data) {
    json records;
    std::ifstream inFile(filename);

    if (inFile.is_open()) {
        inFile >> records;
        inFile.close();
    }

    records.push_back(data);

    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << records.dump(4); // Pretty print JSON
        outFile.close();
        std::cout << "Data added successfully!\n";
    } else {
        std::cout << "Error opening file!\n";
    }
}

void readRecords(const std::string &filename) {
    json records;
    std::ifstream file(filename);

    if (file.is_open()) {
        file >> records;
        file.close();

        std::cout << "\nSaved Records (JSON Format):\n" << records.dump(4) << std::endl;
    } else {
        std::cout << "No records found!\n";
    }
}

void deleteRecord(const std::string &filename, const std::string &name) {
    json records;
    std::ifstream inFile(filename);

    if (inFile.is_open()) {
        inFile >> records;
        inFile.close();
    }

    json newRecords;
    bool found = false;

    for (const auto &record : records) {
        if (record != name) {
            newRecords.push_back(record);
        } else {
            found = true;
        }
    }

    if (found) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << newRecords.dump(4);
            outFile.close();
            std::cout << "Record deleted successfully!\n";
        } else {
            std::cout << "Error opening file!\n";
        }
    } else {
        std::cout << "Record not found!\n";
    }
}

int main() {
    std::string filename = "records.json";
    std::string input;
    int choice;

    while (true) {
        std::cout << "\n1. Add Record\n2. Read Records\n3. Delete Record\n4. Exit\nChoose: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::cout << "Enter text to save: ";
            std::getline(std::cin, input);
            addRecord(filename, input);
        } else if (choice == 2) {
            readRecords(filename);
        } else if (choice == 3) {
            std::cout << "Enter record name to delete: ";
            std::getline(std::cin, input);
            deleteRecord(filename, input);
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}