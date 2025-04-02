#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

// Function ya kuonyesha majina ya files kwenye folder
void listFiles(const string &folderPath) {
    try {
        cout << "Files in '" << folderPath << "':\n";
        for (const auto &entry : fs::directory_iterator(folderPath)) {
            if (fs::is_regular_file(entry.path())) {
                cout << "- " << entry.path().filename() << endl;
            }
        }
    } catch (const fs::filesystem_error &e) {
        cout << "Error: " << e.what() << endl;
    }
}

int main() {
    string folderPath;
    cout << "Enter folder path: ";
    cin >> folderPath;

    listFiles(folderPath);

    return 0;
}