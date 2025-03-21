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

int main() {
    std::string filename = "records.txt";
    std::string input;

    std::cout << "Enter text to save (type 'exit' to stop): ";
    while (true) {
        std::getline(std::cin, input);
        if (input == "exit") break;
        addRecord(filename, input);
    }

    std::cout << "\nSaved records:\n";
    readRecords(filename);

    return 0;
}