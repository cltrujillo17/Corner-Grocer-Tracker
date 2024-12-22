#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

class GroceryTracker {
private:
    map<string, int> itemFrequency;

    // Helper function to load data from input file
    void loadData(const string& fileName) {
        ifstream inputFile(fileName);
        if (inputFile.is_open()) {
            string item;
            while (inputFile >> item) {
                itemFrequency[item]++;
            }
            inputFile.close();
        } else {
            cerr << "Error: Could not open input file." << endl;
        }
    }

    // Helper function to write frequency data to a file
    void writeBackupFile(const string& backupFileName) {
        ofstream backupFile(backupFileName);
        if (backupFile.is_open()) {
            for (const auto& pair : itemFrequency) {
                backupFile << pair.first << " " << pair.second << endl;
            }
            backupFile.close();
        } else {
            cerr << "Error: Could not write to backup file." << endl;
        }
    }

public:
    GroceryTracker(const string& inputFileName, const string& backupFileName) {
        loadData(inputFileName);
        writeBackupFile(backupFileName);
    }

    // Menu option 1: Search for an item
    void searchItem(const string& item) const {
        auto it = itemFrequency.find(item);
        if (it != itemFrequency.end()) {
            cout << item << " was purchased " << it->second << " times." << endl;
        } else {
            cout << item << " was not purchased." << endl;
        }
    }

    // Menu option 2: Display all items with frequencies
    void displayAllItems() const {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Menu option 3: Display histogram
    void displayHistogram() const {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

void displayMenu() {
    cout << "\nCorner Grocer - Item Tracking Program\n";
    cout << "1. Search for an item\n";
    cout << "2. Display all items with frequencies\n";
    cout << "3. Display histogram of items\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt", "frequency.dat");
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter the item to search for: ";
                string item;
                cin >> item;
                tracker.searchItem(item);
                break;
            }
            case 2:
                tracker.displayAllItems();
                break;
            case 3:
                tracker.displayHistogram();
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
