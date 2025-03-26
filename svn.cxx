#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

void deleteRecord(const std::string &filename, const std::string &keyword) {
    std::ifstream file(filename);
    std::vector<std::string> records;
    std::string line;
    bool found = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find(keyword) == std::string::npos) {
                records.push_back(line);
            } else {
                found = true;
            }
        }
        file.close();

        if (found) {
            std::ofstream outFile(filename);
            for (const auto &record : records) {
                outFile << record << std::endl;
            }
            outFile.close();
            std::cout << "Record deleted successfully!\n";
        } else {
            std::cout << "No matching record found to delete.\n";
        }
    } else {
        std::cout << "Error opening file!\n";
    }
}

void editRecord(const std::string &filename, const std::string &oldText, const std::string &newText) {
    std::ifstream file(filename);
    std::vector<std::string> records;
    std::string line;
    bool found = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find(oldText) != std::string::npos) {
                std::cout << "Editing: " << line << " → " << newText << std::endl;
                line = newText;
                found = true;
            }
            records.push_back(line);
        }
        file.close();

        if (found) {
            std::ofstream outFile(filename);
            for (const auto &record : records) {
                outFile << record << std::endl;
            }
            outFile.close();
            std::cout << "Record edited successfully!\n";
        } else {
            std::cout << "No matching record found to edit.\n";
        }
    } else {
        std::cout << "Error opening file!\n";
    }
}

int main() {
    std::string filename = "records.txt";
    std::string input, searchKey, newText;
    int choice;

    while (true) {
        std::cout << "\n1. Add Record\n2. Read Records\n3. Search Record\n4. Delete Record\n5. Edit Record\n6. Exit\nChoose: ";
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
            std::cout << "Enter keyword of record to delete: ";
            std::getline(std::cin, searchKey);
            deleteRecord(filename, searchKey);
        } else if (choice == 5) {
            std::cout << "Enter keyword of record to edit: ";
            std::getline(std::cin, searchKey);
            std::cout << "Enter new text: ";
            std::getline(std::cin, newText);
            editRecord(filename, searchKey, newText);
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}