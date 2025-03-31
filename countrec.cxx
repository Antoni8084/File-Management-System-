#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
    std::vector<std::string> records;

    if (file.is_open()) {
        while (getline(file, line)) {
            records.push_back(line);
        }
        file.close();

        // Panga kwa alfabeti
        std::sort(records.begin(), records.end());

        std::cout << "\nSaved records (Sorted):\n";
        for (const auto &record : records) {
            std::cout << record << std::endl;
        }
    } else {
        std::cout << "Error reading file!\n";
    }
}

void countRecords(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    int count = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            count++;
        }
        file.close();
        std::cout << "Total records: " << count << std::endl;
    } else {
        std::cout << "Error opening file!\n";
    }
}

int main() {
    std::string filename = "records.txt";
    std::string input;
    int choice;

    while (true) {
        std::cout << "\n1. Add Record\n2. Read Records (Sorted)\n3. Count Records\n4. Exit\nChoose: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::cout << "Enter text to save: ";
            std::getline(std::cin, input);
            addRecord(filename, input);
        } else if (choice == 2) {
            readRecords(filename);
        } else if (choice == 3) {
            countRecords(filename);
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}